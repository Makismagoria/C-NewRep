#pragma once
#include <random>
#include <cstdint>

class TransmissionGenerator
{
public:
    TransmissionGenerator(std::uint64_t seed, double p_ul);

    bool transmission();

private:
    std::mt19937_64 rng_; //Генератор псевдослучайных чисел ниже сохранил себе немного ручных заметок о синтексисе :)
    
    //mt — Mersenne Twister (вихрь Мерсенна), алгоритм генератора.
    //19937 — его период $2^{19937} - 1$: последовательность настолько длинная, что за любую симуляцию не повторится.
    //_64 — выдаёт 64-битные целые числа.
    
    std::bernoulli_distribution coin_;  // удобное расспределение тк возвращает не число, а bool: true с вероятностью p_ul
};
