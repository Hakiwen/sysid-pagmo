//
// Created by jbm on 5/28/20.
//

#include "problem.h"

////Implements problem.h

TimeInvariantDynamics::TimeInvariantDynamics(const std::vector<double>& static_params,const std::vector<double> &decision_params, const ti_underlying_dynamics& dynamics) {
    this->params = Dynamics::catvec(static_params, decision_params);
    this->ti = dynamics;
}

TimeInvariantDynamics::TimeInvariantDynamics(const TimeInvariantDynamics &rhs) {
    this->ti = rhs.ti;
    this->params = rhs.params;
}


TimeVaryingDynamics::TimeVaryingDynamics(const std::vector<double> &static_params, const std::vector<double> &decision_params, const tv_underlying_dynamics& dynamics) {
    this->params = Dynamics::catvec(static_params, decision_params);
    this->tv = dynamics;
}

TimeVaryingDynamics::TimeVaryingDynamics(const TimeVaryingDynamics &rhs) {
    this->tv = rhs.tv;
    this->params = rhs.params;
}


void TimeVaryingDynamics::dynamics(const std::vector<double> &x, std::vector<double> &dxdt, const double t) const {
    dxdt = this->tv(x, this->params, t);
}

void TimeInvariantDynamics::dynamics(const std::vector<double> &x, std::vector<double> &dxdt, const double t) const {
    dxdt = this->ti(x,this->params);
}

void TimeVaryingDynamics::update_params(const std::vector<double> & dv){
    this->params = std::vector<double>(dv.size());
    for(int i = 0; i<dv.size();++i){
        this->params[i] = dv[i];
    }
}

void TimeInvariantDynamics::update_params(const std::vector<double> & dv){
    this->params = std::vector<double>(dv.size());
    for(int i = 0; i<dv.size();++i){
        this->params[i] = dv[i];
    }
}
std::vector<double> Dynamics::catvec(const std::vector<double> &a, const std::vector<double> &b) {
    std::vector<double> c = a;
    c.insert(c.end(), b.begin(), b.end());
    return c;

}

SysIdProblem::SysIdProblem(tv_underlying_dynamics u_dyn, initial_decision_map idp, const Dataset & dataset, const SysIdParameters & parameters, cost_function ccf=nullptr) {
    this->problem_parameters = parameters;
    this->dataset = dataset;
    this->tv = u_dyn;
    this->idp = idp;
//    Initialize decisions_vars to lower bound
    this->decision_vars = this->problem_parameters.lb;
    this->data_states = dataset.states;
    this->data_times = dataset.times;
    this->is_tv = true;

    if (ccf != nullptr){
        this->is_custom_cost = (ccf != nullptr);
        this->ccf = ccf;
    }

    if(this->tv)
        this->tv_dynamics =  TimeVaryingDynamics(this->problem_parameters.static_decision_params, problem_parameters.lb, this->tv);
    else
        this->ti_dynamics = TimeInvariantDynamics(this->problem_parameters.static_decision_params, problem_parameters.lb, this->ti);

}

SysIdProblem::SysIdProblem(ti_underlying_dynamics u_dyn, initial_decision_map idp, const Dataset & dataset, const SysIdParameters & parameters, cost_function ccf=nullptr) {
    this->problem_parameters = parameters;
    this->dataset = dataset;
    this->ti = u_dyn;
    this->idp = idp;
//    Initialize decisions_vars to lower bound
    this->decision_vars = this->problem_parameters.lb;
    this->data_states = dataset.states;
    this->data_times = dataset.times;
    this->is_tv = false;

    if (ccf != nullptr){
        this->is_custom_cost = (ccf != nullptr);
        this->ccf = ccf;
    }
    if(this->tv)
        this->tv_dynamics =  TimeVaryingDynamics(this->problem_parameters.static_decision_params, problem_parameters.lb, this->tv);
    else
        this->ti_dynamics = TimeInvariantDynamics(this->problem_parameters.static_decision_params, problem_parameters.lb, this->ti);


}

double SysIdProblem::built_in_cost(const std::vector<double> &state, const std::vector<double> &data){
    size_t num_states = state.size();
    double cost = 0;
    for(int i = 0; i<num_states;++i){
        cost += pow(state[i] - data[i], 2);
    }
    cost = sqrt(cost);
    return cost;
}


pagmo::vector_double SysIdProblem::fitness(const pagmo::vector_double & pagmo_decision_vars) {
    std::vector<double> un_pagmo_decision_vars;
    for(int i =0;i<pagmo_decision_vars.size();++i){
        un_pagmo_decision_vars.push_back(pagmo_decision_vars[i]);
    }
//    this->tv_dynamics.update_params(un_pagmo_decision_vars);
    std::vector<double> combined_vector =Dynamics::catvec(this->problem_parameters.static_decision_params, un_pagmo_decision_vars);
    this->tv_dynamics.update_params(combined_vector);
    std::vector<double> x0 = this->idp(Dynamics::catvec(this->problem_parameters.static_decision_params, pagmo_decision_vars)
            , this->data_states[this->problem_parameters.t0]);
    size_t num_states = x0.size();

//    Shouldn't these times be specified by the dataset?
    double ts = this->problem_parameters.tf - this->problem_parameters.t0;
    std::vector<double> times(ts+1);
    std::vector<std::vector<double>> x;

    for (int i = 0; i <= (ts); i++)
        times[i] = (double) i;


    integrate(times,x0,x);



//  Do we want the cost to a proportion of the data for every case?
    double cost = 0;
    for (int i = 0; i < x.size(); ++i) {
        size_t data_index = (size_t) this->problem_parameters.t0 + i;
        if(this->is_custom_cost){
            cost += ccf(x[i], this->data_states[data_index]);

        }
        else{
            cost += built_in_cost(x[i], this->data_states[i]);
        }
    }
    cost = sqrt(cost);
    std::vector<double> ret;
    ret.push_back(cost);
    return ret;
}

std::pair<std::vector<double>, std::vector<double> > SysIdProblem::get_bounds() const {
    return {this->problem_parameters.lb, this->problem_parameters.ub};
}

//TODO: Get rid of magic numbers in here
void SysIdProblem::integrate(const std::vector<double> &times, std::vector<double> &x0, std::vector<std::vector<double> > &x) {

    x.resize(0);
    if (this->is_tv){
        size_t steps = integrate_times(make_dense_output( 1.0e-6 , 1.0e-5 , boost::numeric::odeint::runge_kutta_dopri5< std::vector<double> >()),std::bind(&TimeVaryingDynamics::dynamics, this->tv_dynamics, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3),
                                       x0 , times, this->problem_parameters.dt ,
                                       push_back_state(x));
    }
    else{
        size_t steps = integrate_times(make_dense_output( 1.0e-6 , 1.0e-5 ,boost::numeric::odeint::runge_kutta_dopri5< std::vector<double> >()),std::bind(&TimeInvariantDynamics::dynamics, this->ti_dynamics, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3),
                                       x0 , times, this->problem_parameters.dt ,
                                       push_back_state(x));
    }
}


