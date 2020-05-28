//
// Created by jbm on 5/27/20.
//

#ifndef SYSID_PAGMO_DYNAMICS_H
#define SYSID_PAGMO_DYNAMICS_H

class Dynamics{
public:
    virtual ~Dynamics();

//    Constructed with intial parameters
    virtual Dynamics(const std::vector<double>&);

//    Set params from external. Alternative would be to have immutable params constructed in, with the object destroyed at every iteration
    virtual void set_params(const std::vector<double>&);
    virtual std::vector<double> get_params();

    virtual void dynamics(const std::vector<double>&, std::vector<double>&&, const double) const;

//// Should have private members for the params
};

#endif //SYSID_PAGMO_DYNAMICS_H
