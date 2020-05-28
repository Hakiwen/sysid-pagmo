//
// Created by jbm on 5/28/20.
//

////Workflow is as follows

//User defines custom classes that inherit from dynamics, dataset, and constraints
//User classes override the virtual methods in dynamics, dataset, and constraints
//User instantiates these classes for the problem at hand and constructs a problem class object from it
//User passes this object to the pagmo problem construct
//blamo, results