//
// Created by jbm on 5/27/20.
//

#ifndef SYSID_PAGMO_PROBLEM_H
#define SYSID_PAGMO_PROBLEM_H

#include "dynamics.h"
#include "dataset.h"
#include "constraints.h"
#include "pagmo/types.hpp"

//This class is constructed in order to
class Problem{
public:
    Dynamics dynamics;
    Dataset dataset;
    Constraints constraints;

    Problem(Dynamics, Dataset, Constraints);

//    fitness function whose handle is passed to the solver. Will compute cost as well as constraint values
//    Assuming this function gets called repeatedly by pagmo, it is not const, every call will update dynamics
    vector_double fitness(const vector_double &);

//    Function to return bounds on variables
//    Updates dynamics
//    Integrates to desired timesteps
//    Computes cost
//    Computes inequalities (do these need to be evaluated over the integrated states?)
//    Computes equalities
//    concatenates last three and returns
    std::pair<vector_double, vector_double> get_bounds() const;

//    These functions return the number of inequality and equality constraints
    vector_double::size_type get_nec() const;
    vector_double::size_type get_nic() const;

protected:
////    Internal variables like those computed from integrate go here

//  Function that computes the integration with the equivalent spacing to the time data from dataset
    void integrate();

// Function that computes the summation of the difference between the dataset and the integration results
    double cost();
};
#endif //SYSID_PAGMO_PROBLEM_H
