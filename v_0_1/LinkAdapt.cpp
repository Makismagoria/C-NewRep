#include "LinkAdapt.hpp"

LinkAdapt::LinkAdapt(double i_0, double o_0, double alpha, double delta, double bler,
                     const std::array<double, 6> &thresholds)
    : i_(i_0), o_(o_0), alpha_(alpha), delta_(delta), bler_(bler), thresholds_(thresholds)

{
        multiplier_ = bler_/(1-bler_);
}

int  LinkAdapt::mcsDecision() 
{
        double gammaRoof = i_ + o_; // имеется ввиду гамма с крышечкой из формулы суммы I и O
        int currMcs = 0;

        for (std::size_t k = thresholds_.size(); k-- > 0; )
        {
                if (thresholds_[k]<=gammaRoof)
                {
                        currMcs = k;
                        break;
                }  
        }
        return currMcs;
}

double  LinkAdapt::illaNew(double mesSINR)
{
        i_=(1-alpha_)*i_+alpha_*mesSINR;

        return i_;
}

double  LinkAdapt::ollaNew(bool ac)
{
        if (ac)
        {
               o_ =  o_+(delta_ * multiplier_);//ACK - значит канал хороший, но нужно соблюдать баланс, поэтому шаг к большей mcs аккуратнее в 9 раз
        }else if (!ac)
        {
                o_ = o_- delta_; //NACK - шажок назад(вычитаем соответственно MCS будет безопаснее) на 0.4 по дефолту
        }
        
        return o_;
}