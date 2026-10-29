simulaTron - UL Link Adaptation Simulator (C++17)

Симулятор адаптации линка в uplink


ФАЙЛЫ

Cfg.hpp                        Все параметры симуляции и сиды
Sinr.hpp/.cpp                  Реальный SINR: канал AR(1) в dB
TransmissionGenerator.hpp/.cpp Есть ли передача в TTI (Bernoulli, p_UL)
MeasureSinr.hpp/.cpp           Измеренный SINR = реальный + шум N(0, sigma_m^2)
LinkAdapt.hpp/.cpp             ILLA, OLLA и выбор MCS по I + O
Reception.cpp                  P_err по сигмоиде и розыгрыш ACK/NACK
main.cpp                       Цикл по TTI и итоговые метрики
CMakeLists.txt                 Сборка


СБОРКА И ЗАПУСК

cmake -S . -B build -G Ninja
cmake --build build
.\build\simulaTron.exe
