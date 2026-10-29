#include "TransmissionGenerator.hpp"

TransmissionGenerator::TransmissionGenerator(std::uint64_t seed, double p_ul)
    : rng_(seed), coin_(p_ul) 
{
    
}
bool TransmissionGenerator::transmission ()
{
    return coin_(rng_);
}