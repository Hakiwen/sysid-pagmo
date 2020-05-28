//
// Created by jbm on 5/27/20.
//

#ifndef SYSID_PAGMO_CONSTRAINTS_H
#define SYSID_PAGMO_CONSTRAINTS_H

class Constraints{
public:
    virtual ~Constraints();

    virtual size_t get_nec();
    virtual size_t get_nic();

    virtual std::vector<double> equality_constraints(const std::vector<double>&) const;
    virtual std::vector<double> inequality_constraints(const std::vector<double>&) const;
};

#endif //SYSID_PAGMO_CONSTRAINTS_H
