//
// Created by jbm on 5/27/20.
//

#ifndef SYSID_PAGMO_DATASET_H
#define SYSID_PAGMO_DATASET_H


//// Alernative would to be to have a vector of structs or pairs of time type and vector that represents each datapoint
class Dataset{
public:
    virtual ~Dataset();

//    Return total number of points in dataset
    virtual size_t get_num_points() const;

//    Return times of dataset points
    virtual std::vector<double> get_times() const;

//    Return states of dataset points
    virtual std::vector<std::vector<double> > get_states() const;
};

#endif //SYSID_PAGMO_DATASET_H
