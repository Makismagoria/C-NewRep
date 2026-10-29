#include <iostream>
#include <string>

#include <fstream>     // CSV: std::ofstream
#include <iomanip>     // CSV: std::setprecision

#include "Cfg.hpp"
#include "Sinr.hpp"
#include "TransmissionGenerator.hpp"
#include "MeasureSinr.hpp"
#include "LinkAdapt.hpp"
#include "Reception.cpp"

int main()
{
    Cfg conf; // Временно храню конфигурацию проекта в классе с модификатором public - будет переделано в будущем

    Sinr truSinr(conf.mu, conf.rho, conf.sigmaC, conf.seedOne);
    TransmissionGenerator probabilityOf(conf.seedTwo, conf.p_ul);
    MeasureSinr measure(conf.sigma_m, conf.seedThree);
    LinkAdapt linkAd(conf.i_0, conf.o_0, conf.alpha, conf.delta, conf.b, conf.mcsThreshold);
    Reception recep(conf.k, conf.seedFour, conf.mcsThreshold);


    //  std::ofstream csv("channel.csv");                                           // CSV: создать файл
    //  if (!csv) { std::cerr << "cannot create channel.csv\n"; return 1; }         // CSV: проверить, что открылся
    //  csv << "tti,actual_sinr_db, mes\n";                                              // CSV: заголовок
    //  csv << std::setprecision(10);                                               // CSV: точность

    int j =0;
    double measuredSinr = 0;
    int mcs = 0;
    double i = 8;
    double o = 0;
    bool ack;
    double sumEta = 0;

    std::string acNac; 
    

    std::cout << "We pick MCS - index: " << linkAd.mcsDecision() << std::endl;

    // double w = conf.mcs[0].threshold;
    // double f = conf.mcs[0].speed;
    // std::cout << "MCS 0 -- Threshold: " << w << " Speed: " << f << std::endl;

    for (int tti = 0; tti < conf.ttiCount; ++tti) // цикл for по TTI, 1 TTI = 1 мс, длительность настраиваемая
    {
        double actSinr = truSinr.truChannel(tti);

        std::cout << tti << "ms SINR: " << actSinr << std::endl;

        if(probabilityOf.transmission()){
            //auto before = linkAdaptation.state();
            j++;
            std::cout << "We have transmission! # " << j << " for tti # " << tti << std::endl;
            
            mcs = linkAd.mcsDecision();
            std::cout << " We pick mcs: "<< mcs << " last ILLA = " << i << " last measured SINR: " << measuredSinr << std::endl;

            ack = recep.ackNack(actSinr,mcs);
            acNac = ack ? "ACK" : "NACK";
            if (ack) sumEta += conf.mcsSpeed[mcs];

            std::cout << "Data transmission: " << acNac << std::endl;

            measuredSinr = measure.measChannel(actSinr);
            
            i = linkAd.illaNew(measuredSinr);
            std::cout << "New measured SINR: " << measuredSinr << " New ILLA: " << i << std::endl;

            if (conf.ollaEnable)
            {
                o = linkAd.ollaNew(ack);
            }
            std::cout << " New OLLA: " << o << std::endl;
            //sv << tti << ',' << actSinr << ',' << measuredSinr << '\n';
        }
        
    }

    double akSumm = recep.ackNumb;
    double nakSumm = recep.nackNumb;

    std::cout << "ACK summ :" << akSumm << " NACK summ: " << nakSumm << std::endl;
    std::cout << "BLER = " << (nakSumm/(akSumm+nakSumm))*100 << "%" << std::endl;
    std::cout << "Sum eta (ACK) = " << sumEta
          << "  T_norm = "      << sumEta / conf.ttiCount
          << "  eta per tx = "  << sumEta / j << std::endl;

    return 0;
}





            // mcs = linkAd.mcsDecision();
            // measuredSinr = measure.measChannel(actSinr);
            // ack = recep.ackNack(actSinr,mcs);
            // linkAd.illaNew(measuredSinr);
