#ifndef GPDemo_MyModel_h
#define GPDemo_MyModel_h

#include "DNest4.h"
#include <ostream>

namespace GPDemo
{

class MyModel
{
    private:


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

