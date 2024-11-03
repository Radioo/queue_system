#ifndef FIREFLY_HPP
#define FIREFLY_HPP

#include <ql/experimental/math/fireflyalgorithm.hpp>
#include "queue.hpp"
#include <wx/wx.h>
#include <cmath>

namespace queue_system::firefly {

    class Firefly {
    public:
        Firefly();

        int optimize(queue_system::calc::queue& queue);

        void setPopulationSize(float populationSize);
        void setInitialAttractiveness(float initialAttractiveness);
        void setMinimumAttractiveness(float minimumAttractiveness);
        void setLightAbsorptionCoefficient(float lightAbsorptionCoefficient);
        void setStandardDeviationForTheGaussianWalk(float standardDeviationForTheGaussianWalk);
        void setMinM(int minM);
        void setMaxM(int maxM);

    private:
        double objectiveFunction(queue_system::calc::queue& queue);

        QuantLib::Size populationSize;
        QuantLib::Real initialAttractiveness;
        QuantLib::Real minimumAttractiveness;
        QuantLib::Real lightAbsorptionCoefficient;
        QuantLib::Real standardDeviationForTheGaussianWalk;
        int minM;
        int maxM;
    };

}

#endif
