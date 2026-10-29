#pragma once
#include <cstdint>
#include <array>
#include <string>

class Cfg
{
public:
    // TrueSINR
    int ttiCount = 30000;
    double mu = 8;        // это сценарий A - Stationary statistics и значения в dB
    double rho = 0.95; // доля того сколько мы берём от старого значения флактуации
    double sigmaC = 3;    // dB
    std::uint64_t seedOne = 1;   // Сид для генератора исходного канала
    // TransmissionGenerator
    std::uint64_t seedTwo = 12; // Сид для генератора вероятности передачи
    double p_ul = 0.25;
    // MCS таблица
    std::array<double, 6> mcsThreshold = {-6, -2, 2, 6, 10, 14};
    std::array<double, 6> mcsSpeed     = {0.25, 0.50, 1.00, 1.50, 2.25, 3.00};
    //MeasureSinr
    std::uint64_t seedThree = 123; // Сид для генератора шума при измерении
    double sigma_m = 1; // Дисперсия для модели измерения канала (по умолчанию 1)
    //LinkAdapt
    double i_0 = mu; //По умолчанию initialIlla равно начальному среднему
    double o_0 = 0; // По умолчанию initialOlla равно нулю
    double alpha = 0.2;
    double delta = 0.4;
    //Reception
    std::uint64_t seedFour = 1234;
    double k = 1; //По умолчанию 1dB^-1
    bool ollaEnable = true;
    double b = 0.10; // цель по bler 10% (на 16% получается самая эффективеная передача)


};
