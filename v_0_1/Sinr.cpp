#include "Sinr.hpp"
#include <cmath>

Sinr::Sinr(double mu, double rho, double sigmaC, std::uint64_t seed)
    : mu_(mu), rho_(rho), 
      kick_(sigmaC * std::sqrt(1.0 - rho * rho)), // Названия полей временные, это толчок - σc·√(1-ρ²)
      rng_(seed) 

{
    x_ = sigmaC * norm_(rng_); // x0 ~ N(0, σc²)
    actual_ = mu_ + x_;        // γ до первого шага - по сути у нас сейчас есть канал на "нулевом шаге"
}

double Sinr::truChannel(int tti) // Пока что передача tti ни на что не влияет, тк авторегрессии в целом всё равно на это
{
    // тут мы начинаем шагатб

    double fPart = rho_ * x_;
    double z = norm_(rng_);
    double sPart = kick_ * z;

    x_ = fPart + sPart;
    actual_ = mu_ + x_;

    return actual_;
}

// double a = std::pow(x, 2);      // x в квадрате
// double b = std::sqrt(x);        // корень из x
// double c = std::pow(x, 1.0/3);  // кубический корень (или std::cbrt(x))
// double d = std::abs(x);         // модуль (для double: std::fabs)