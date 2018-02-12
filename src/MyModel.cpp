#include "MyModel.h"
#include "DNest4.h"

namespace GPDemo
{

// Data
Eigen::VectorXd MyModel::xs(10);
Eigen::VectorXd MyModel::ys(10);

void MyModel::set_data()
{
    xs << 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0;
    ys << 1.0, 3.8, 3.7, 3.8, 2.9, 2.4, 2.0, 1.3, 0.4, -0.2;
}

MyModel::MyModel()
:C  (xs.size(), xs.size())
,mus(xs.size())
,ns (xs.size())
{

}

void MyModel::from_prior(DNest4::RNG& rng)
{
    // Dumb priors
    A = 10.0*rng.rand();
    L = 100.0*rng.rand();
    B = -10.0 + 20.0*rng.rand();

    // Note int i instead of size_t i, because eigen reports sizes with an
    // int, whereas stl vectors use a size_t
    for(int i=0; i<ns.size(); ++i)
        ns[i] = rng.randn();

    compute_C();
    compute_mus();
}

double MyModel::perturb(DNest4::RNG& rng)
{
    double logH = 0.0;

    int which = rng.rand_int(4);
    if(which == 0)
    {
        A += 10.0*rng.randh();
        DNest4::wrap(A, 0.0, 10.0);
        compute_C();
    }
    else if(which == 1)
    {
        L += 100.0*rng.randh();
        DNest4::wrap(L, 0.0, 100.0);
        compute_C();
    }
    else if(which == 2)
    {
        B += 20.0*rng.randh();
        DNest4::wrap(B, -10.0, 10.0);
    }
    else
    {
        int k = rng.rand_int(ns.size());
        logH -= -0.5*pow(ns[k], 2);
        ns[k] += rng.randh();
        logH += -0.5*pow(ns[k], 2);
    }
    compute_mus();

    return logH;
}

void MyModel::compute_mus()
{
    // Multiply ns by lower triangular matrix
    mus = cholesky.matrixL()*ns;

    // Add mean function
    for(int i=0; i<mus.size(); ++i)
        mus[i] += B;
}

void MyModel::compute_C()
{
    // For speed
    double inv_L = 1.0/L;

    // Outer loop is over j, since Eigen matrices are in column-major order
    // by default.
    for(int j=0; j<xs.size(); ++j)
    {
        // Don't loop i from zero, use symmetry to cheapen computation
        for(int i=j; i<xs.size(); ++i)
        {
            C(i, j) = A*exp(-pow((xs[i] - xs[j])*inv_L, 2));

            // Since it's symmetric
            if(i != j)
                C(j, i) = C(i, j);
        }
    }

    // Compute cholesky decomposition
    cholesky = C.llt();
}

double MyModel::log_likelihood() const
{
    double logL = 0.0;

    // Just a silly normal likelihood. Note, if this were actually our model,
    // we could have explicitly marginalised over the ns, reducing the
    // dimensionality of the problem down to two (the hyperparameters)!


    // SD of noise in data
    double sigma = 0.05;
    logL += -0.5*log(2*M_PI*sigma*sigma)*ys.size();
    double tau = pow(sigma, -2); 

    for(int i=0; i<ys.size(); ++i)
        logL += -0.5*pow(ys[i] - mus[i], 2)*tau;

    return logL;
}

void MyModel::print(std::ostream& out) const
{
    out << A << ' ' << L << ' ';
    for(int i=0; i<mus.size(); ++i)
        out << mus[i] << ' ';
}

std::string MyModel::description() const
{
    return std::string("");
}

} // namespace GPDemo

