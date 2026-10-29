#pragma once
#include <random>
#include <cstdint>

class MeasureSinr
{
public:
    MeasureSinr(double sigma_m, std::uint64_t seed);

    double measChannel(double trSinr);
private:
    double sigma_m_;
    std::mt19937_64 measRng_;                             // свой генератор
    std::normal_distribution<double> measNorm_{0.0, 1.0}; // свой объект распределения
};
