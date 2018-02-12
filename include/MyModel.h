#ifndef GPDemo_MyModel_h
#define GPDemo_MyModel_h

#include "DNest4.h"
#include <Eigen/Dense>
#include <ostream>
#include <vector>

namespace GPDemo
{

class MyModel
{
    private:
        // Some data. See MyModel.cpp for values
        static Eigen::VectorXd xs;
        static Eigen::VectorXd ys;
    public:
        static void set_data();

    private:
        // GP hyperparameters - assuming squared exponential
        double A, L;

        // Covariance matrix and its cholesky decomposition
        Eigen::MatrixXd C;
        Eigen::LLT<Eigen::MatrixXd> cholesky;        

        // GP function values and latent N(0,1) variables
        Eigen::VectorXd mus;
        Eigen::VectorXd ns;

        // Compute mus and covariance matrix
        void compute_mus();
        void compute_C();

    public:
        // Constructor only gives size of params
        MyModel();

        // Generate the point from the prior
        void from_prior(DNest4::RNG& rng);

        // Metropolis-Hastings proposals
        double perturb(DNest4::RNG& rng);

        // Likelihood function
        double log_likelihood() const;

        // Print to stream
        void print(std::ostream& out) const;

        // Return string with column information
        std::string description() const;
};

} // namespace GPDemo

#endif

