#include "MeasureSinr.hpp"

MeasureSinr::MeasureSinr(double sigma_m, std::uint64_t seed)
    : sigma_m_(sigma_m),
      measRng_(seed) 

{
}

double MeasureSinr::measChannel(double trSinr)
{
    double eps = sigma_m_ * measNorm_(measRng_);
    return trSinr+eps;
}