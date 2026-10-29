#pragma once
#include <random>
#include <cstdint>

class Sinr
{
public:
    Sinr(double mu, double rho_, double sigmaC, std::uint64_t seed);

    double truChannel(int tti);

private:
    double mu_;                                       // среднее SINR в стардартном случае 8 дб
    double rho_;                                      // корреляция за один TTI, 0,95
    double kick_;                                     // пинок/толчок на который умножается случайная Z
    double x_ = 0.0;                                  // x - флуктуация
    double actual_ = 0.0;                             // храним СНР в поле
    std::mt19937_64 rng_;                             // свой генератор
    std::normal_distribution<double> norm_{0.0, 1.0}; // свой объект распределения
};
