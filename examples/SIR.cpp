//
// Created by jbm on 5/28/20.
//


#include <pagmo/problem.hpp>
#include <pagmo/types.hpp>

#include <pagmo/algorithm.hpp>
#include <pagmo/algorithms/cmaes.hpp>
#include <pagmo/population.hpp>
#include "problem.h"

struct COVID_data
{
#define NaN -1
    int N = 330362587;
    double positive_tests[127] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,9,18,44,84,126,259,357,455,613,789,1042,1371,1813,2390,3320,4110,5188,6650,8863,11582,15967,21809,28306,37215,48143,58370,70648,87903,106545,125743,145077,166410,190884,216029,244152,276048,309386,335112,363911,394394,424544,458869,493291,524257,552123,577244,603258,633590,664672,696563,724542,751966,777275,803283,831925,863726,897971,933896,961030,982177,1007288,1034474,1063842,1097064,1126902,1152895,1174534,1196655,1221754,1249260,1276957,1302106,1323905,1341250,1362733,1383224,1410175,1434663,1459695,1480473,1500312,1521252,1542594,1568497,1592656,1614954,1635760,1654829,1671035,1689630};
    int deaths[127] = {NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,2,2,4,5,8,11,14,16,20,26,27,31,35,37,43,51,55,63,77,98,120,145,189,253,306,437,521,725,953,1231,1604,2038,2527,3060,3877,4823,5924,7112,8487,9714,10937,12841,14737,16659,18751,20686,22237,23754,26066,28628,30789,32854,34641,36300,37999,40554,42595,44409,46251,48069,49164,50354,52482,55182,57320,59059,60710,61868,62780,65310,67256,70002,71762,73291,74270,75107,76650,78343,80251,81729,83015,83854,84640,86070,87472,88916,90196,91287,91941,92464,93093,94352};
    int hospitalized[127] = {NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,325,416,617,1042,1436,2155,2770,3828,4971,7617,10789,12179,13833,15574,17856,19982,21833,24564,29095,30905,34663,42294,44063,49826,51745,54757,54749,55295,58719,59260,58625,57808,56591,55570,55677,58579,58130,57889,56075,56344,55050,54971,54940,54930,53793,52370,51734,50312,50062,50906,50227,49130,47718,46637,44943,44191,45199,44514,44075,42854,42896,41108,40933,41174,40884,39915,38802,37873,36706,36668,36609,37253};
    double times[127] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126};
    int SD_offset = 21;
    double SD_unscaled[143] = {3.088187e-01,5.073273e-01,5.566787e-01,3.621484e-01,2.626180e-01,6.339250e-01,6.776369e-01,6.957528e-01,7.255672e-01,7.403892e-01,3.872041e-01,3.036252e-01,7.157543e-01,7.427166e-01,7.503146e-01,7.674222e-01,7.440590e-01,4.426569e-01,3.785258e-01,5.066959e-01,7.834854e-01,8.273828e-01,8.065097e-01,8.082386e-01,4.660729e-01,3.607833e-01,7.719885e-01,7.806001e-01,7.804133e-01,7.947734e-01,8.334978e-01,4.143098e-01,3.100599e-01,6.846225e-01,7.164029e-01,6.823785e-01,7.154522e-01,7.247524e-01,4.904692e-01,3.382395e-01,7.416836e-01,7.503105e-01,7.710146e-01,7.365514e-01,8.467995e-01,5.704936e-01,4.878540e-01,6.338831e-01,7.963948e-01,7.894516e-01,8.297836e-01,8.417594e-01,5.728613e-01,4.148998e-01,7.846796e-01,5.482800e-01,8.283005e-01,8.367210e-01,8.684804e-01,5.785986e-01,3.253988e-01,7.116520e-01,9.483391e-01,9.124209e-01,9.782235e-01,1,7.770012e-01,6.225172e-01,9.359211e-01,8.456078e-01,8.393104e-01,8.077433e-01,8.264349e-01,5.071299e-01,4.368694e-01,5.893498e-01,5.009972e-01,4.930227e-01,4.892498e-01,4.584539e-01,3.100611e-01,2.690391e-01,4.085911e-01,3.735949e-01,4.454511e-01,3.847882e-01,3.463028e-01,2.468874e-01,2.433250e-01,3.594526e-01,3.464212e-01,1.657108e-01,1.928216e-01,1.973917e-01,1.387686e-01,1.129648e-01,1.765325e-01,1.908069e-01,2.072379e-01,2.078977e-01,2.076790e-01,1.682227e-01,1.127852e-01,1.859691e-01,1.994930e-01,2.068616e-01,2.258245e-01,2.442180e-01,1.854983e-01,1.463622e-01,2.166250e-01,2.586571e-01,2.738440e-01,2.835170e-01,2.948589e-01,2.341952e-01,1.866829e-01,2.899567e-01,3.120172e-01,3.046137e-01,3.472073e-01,2.128682e-01,1.712790e-01,9.016633e-02,1.891276e-01,2.037144e-01,2.286645e-01,2.613236e-01,2.468461e-01,2.153577e-01,1.719605e-01,2.341056e-01,2.676215e-01,2.897523e-01,2.928213e-01,3.311842e-01,2.590726e-01,1.515010e-01,2.725226e-01,2.707111e-01,3.061052e-01,3.424335e-01,3.948724e-01};
};

double gamma_val = 0.2;
double K = 5;
double t0 = 50;
double tend = 100;

double beta_lb = 0.05;
double beta_ub = 0.5;
double i0_lb = 0.5;
double i0_ub = 1;

double dt = 0.1;

struct sir_vars{
    double N;
    double K;
    double gamma;
    std::vector<double> beta_vec;
    double I0_ratio;
};


sir_vars parse_params(std::vector<double> a){
    return {.N = a[0],
            .K = a[1],
            .gamma = a[2],
            .beta_vec = std::vector<double>(a.begin() + 3, a.end() - 1),
            .I0_ratio = *(a.end() - 1)};
}



std::vector<double> sir_idp(const std::vector<double> &params, const std::vector<double> &initial_data){
    sir_vars vars = parse_params(params);
    double I0 = vars.I0_ratio*initial_data[0];
    double R0 = (1 - vars.I0_ratio)*initial_data[0];
    double S0 = vars.N - I0 - R0;
    return {S0, I0, R0};
}
//Pass in entire decision variable params
std::vector<double> sir_dyn(const std::vector<double> &x, const std::vector<double> &params, const double  t){
    double beta;
    double N = params[0];
    double K = params[1];
    double gamma = params[2];
    std::vector<double> beta_vec(params.begin() + 3, params.end() - 1);
    if (K == 0){
        beta = beta_vec[0];
    }
    else{
        size_t index = int(t/(double) K);
        beta = beta_vec[index];
    }
    double S = x[0];
    double I = x[1];
    std::vector<double> dxdt(3);
    dxdt[0] = -beta*S*I/N;
    dxdt[1] = beta*S*I/N - gamma*I;
    dxdt[2] = gamma*I;
    return dxdt;
}

double sir_cost(const std::vector<double>&x, const std::vector<double>&d){
    return pow(x[1] + x[2] - d[0], 2)/pow(d[0], 2);
}


SysIdProblem sir_prob;

struct problem_v0 {

    pagmo::vector_double fitness(const pagmo::vector_double &dv) const
    {
        return sir_prob.fitness(dv);
    }
    // Implementation of the box bounds.
    std::pair<pagmo::vector_double, pagmo::vector_double> get_bounds() const

    {
        return sir_prob.get_bounds();
    }
};

int main(){
//    Our parameters

    int len_beta_vec;
    if (K == 0){
        len_beta_vec = 1;
    }
    else {
        len_beta_vec = (int) ((tend - t0) / (double) K) + 1;
    }
    std::vector<double> lb(len_beta_vec, beta_lb);
    lb.push_back(i0_lb);
    std::vector<double> ub(len_beta_vec, beta_ub);
    ub.push_back(i0_ub);


//    Conversions
    COVID_data cd;
    Dataset sir_data = {.num_points = 127,
                        .times = std::vector<double>(),
                        .states = std::vector<std::vector<double> >()};
    sir_data.times.insert(sir_data.times.begin(),
            std::begin(cd.times),
            std::end(cd.times));

    for(int i=0; i<sir_data.num_points;i++){
        sir_data.states.push_back(std::vector<double>({cd.positive_tests[i]}));
    }

    SysIdParameters sir_params = {
            .t0=t0,
            .tf=tend,
            .dt=dt,
            .lb=lb,
            .ub=ub,
            .static_decision_params = std::vector<double>(3)
    };
    sir_params.static_decision_params = {(double)cd.N, K, gamma_val};

    sir_prob = SysIdProblem(sir_dyn, sir_idp, sir_data, sir_params, sir_cost);


    pagmo::problem p{problem_v0{}};
    pagmo::algorithm algo{pagmo::cmaes(100)};
    pagmo::population pop{p, 100};
    pop = algo.evolve(pop);
    std::cout << "The population: \n" << pop;
}