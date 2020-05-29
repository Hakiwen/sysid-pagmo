//
// Created by jbm on 5/27/20.
//

#ifndef SYSID_PAGMO_DATASET_H
#define SYSID_PAGMO_DATASET_H


//// Alernative would to be to have a vector of structs or pairs of time type and vector that represents each datapoint
struct Dataset{
//    Return total number of points in dataset
    size_t num_points;

//    Return times of dataset points
    std::vector<double> times;

//    Return states of dataset points
    std::vector<std::vector<double> > states;
};

#endif //SYSID_PAGMO_DATASET_H
