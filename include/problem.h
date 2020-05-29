//
// Created by jbm on 5/27/20.
//

#ifndef SYSID_PAGMO_PROBLEM_H
#define SYSID_PAGMO_PROBLEM_H

#include <functional>
#include <vector>
#include <boost/numeric/odeint.hpp>
#include <iostream>
#include <utility>
//#include "dynamics.h"
#include "dataset.h"
//#include "constraints.h"
#include "parameters.h"
#include "pagmo/types.hpp"


//TODO Rule of 3/5/0


struct push_back_state
{
    std::vector< std::vector<double> >& m_states;

    explicit push_back_state( std::vector< std::vector<double> > &states)
            : m_states( states )  { }

    void operator()( const std::vector<double> &x , const double t )
    {
        m_states.push_back( x );
    }
};


using ti_underlying_dynamics = std::function< std::vector<double> (const std::vector<double>&, const std::vector<double> &) > ;
using tv_underlying_dynamics = std::function< std::vector<double> (const std::vector<double>&, const std::vector<double> &, double) > ;
using cost_function = std::function< double (const std::vector<double>&, const std::vector<double>&)> ;
using initial_decision_map = std::function< std::vector<double > (std::vector<double>, std::vector<double>) >;

//TODO: Look into making first two args a std::pair
//TODO: Work on making dynamics parent class again
class Dynamics{
public:
    static std::vector<double> catvec(const std::vector<double>& a, const std::vector<double>& b);

    ~Dynamics() = default;

protected:
    std::vector<double> params;
    ti_underlying_dynamics ti;
    tv_underlying_dynamics tv;

};

//class TimeVaryingDynamics : public Dynamics{
class TimeVaryingDynamics{
public:
    TimeVaryingDynamics() = default;
    TimeVaryingDynamics(const std::vector<double>& static_decision_params, const std::vector<double>& decision_params,
            const tv_underlying_dynamics&);
    TimeVaryingDynamics(const TimeVaryingDynamics& rhs);

    void dynamics(const std::vector<double>&, std::vector<double>&, double) const;
    void update_params(const std::vector<double> &);

protected:
    std::vector<double> params;
    tv_underlying_dynamics tv;
};

class TimeInvariantDynamics : public Dynamics {
public:
    TimeInvariantDynamics() = default;
    TimeInvariantDynamics(const std::vector<double>&,const std::vector<double>&, const ti_underlying_dynamics&) ;
    TimeInvariantDynamics(const TimeInvariantDynamics& rhs);

    void dynamics(const std::vector<double>&, std::vector<double>&, double) const;
    void update_params(const std::vector<double> &);

protected:
    std::vector<double> params;
    ti_underlying_dynamics ti;
};


//This class is constructed in order to
class SysIdProblem{
public:
    SysIdProblem() = default;
    SysIdProblem(tv_underlying_dynamics, initial_decision_map, const Dataset&, const SysIdParameters&, cost_function);
    SysIdProblem(ti_underlying_dynamics, initial_decision_map, const Dataset&, const SysIdParameters&, cost_function);


//    This functions takes in suggest params, computes the system at problem parameterized times to compute the cost
    pagmo::vector_double fitness(const pagmo::vector_double &);
//    Function to return bounds on variables
    std::pair<pagmo::vector_double, pagmo::vector_double> get_bounds() const;
//TODO: Add in constraint function


protected:
////    Internal variables like those computed from integrate go here
    Dataset dataset;
    TimeVaryingDynamics tv_dynamics;
    TimeInvariantDynamics ti_dynamics;

//  Function that computes the integration with the equivalent spacing to the time data from dataset
    void integrate(const std::vector<double> &times, std::vector<double> &x0, std::vector<std::vector<double> > &x);

    double built_in_cost(const std::vector<double> &state, const std::vector<double> &data);


    SysIdParameters problem_parameters;
    std::vector<std::vector<double> > data_states;
    std::vector<double> data_times;
    std::vector<double> decision_vars;
    std::vector<double> dynamics_params;
    tv_underlying_dynamics tv;
    ti_underlying_dynamics ti;
    initial_decision_map idp;
    cost_function ccf;
    bool is_tv;
    bool is_custom_cost;
};
#endif //SYSID_PAGMO_PROBLEM_H
