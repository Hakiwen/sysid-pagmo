//
// Created by jbm on 5/28/20.
//

#ifndef SYSID_PAGMO_PARAMETERS_H
#define SYSID_PAGMO_PARAMETERS_H

#import <vector>
#import <cmath>

struct SysIdParameters{
//  Start time
    double t0;
//    End time
    double tf;
//    Integration time step
    double dt;
//    Bounds
    std::vector<double> lb;
    std::vector<double> ub;
//    size_t num_dynamics_decision_vars;
//    size_t num_initial_decision_vars;
    std::vector<double> static_decision_params;

};


#endif //SYSID_PAGMO_PARAMETERS_H
