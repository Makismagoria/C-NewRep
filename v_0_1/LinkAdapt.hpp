#pragma once
#include <array>

class LinkAdapt
{
public:
    LinkAdapt(double i_0, double o_0, double alpha, double delta, double bler,
              const std::array<double, 6> &thresholds);


    int mcsDecision();
    double  illaNew(double mesSINR);
    double ollaNew(bool ac);

private:
    double i_;
    double o_;
    double alpha_;
    double delta_;
    double bler_;
    std::array<double, 6> thresholds_;
    double multiplier_;
};