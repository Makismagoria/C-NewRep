#include <array>
#include <random>
#include <cstdint>
#include <cmath>

class Reception
{
public:
    Reception(double k, std::uint64_t seed, const std::array<double, 6> &thresholds)
        : k_(k), rng_(seed), thresholds_(thresholds)
    {
    }

    int ackNumb = 0;
    int nackNumb = 0;

    bool ackNack(double trueSinr, int mcs)
    {
        double p_er = 1 / (1 + 9 * std::exp(k_ * (trueSinr - thresholds_[mcs])));
        double u = dist(rng_);
        bool resBlock = u >= p_er; // Получается, что true - это Ack, а false это NACK

        if (resBlock)
        {
            ++ackNumb;
        }
        else
        {
            ++nackNumb;
        }

        return resBlock;
    }

private:
    double k_;
    std::mt19937_64 rng_;
    std::uniform_real_distribution<double> dist{0.0, 1.0};
    std::array<double, 6> thresholds_;
};