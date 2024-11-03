#include "firefly.hpp"

namespace queue_system::firefly {

    Firefly::Firefly()
        : populationSize(0),
          initialAttractiveness(0),
          minimumAttractiveness(0),
          lightAbsorptionCoefficient(0),
          standardDeviationForTheGaussianWalk(0),
          minM(0),
          maxM(1) {}

    void Firefly::setPopulationSize(float value) {
        populationSize = static_cast<QuantLib::Size>(value);
    }

    void Firefly::setInitialAttractiveness(float value) {
        initialAttractiveness = static_cast<QuantLib::Real>(value);
    }

    void Firefly::setMinimumAttractiveness(float value) {
        minimumAttractiveness = static_cast<QuantLib::Real>(value);
    }

    void Firefly::setLightAbsorptionCoefficient(float value) {
        lightAbsorptionCoefficient = static_cast<QuantLib::Real>(value);
    }

    void Firefly::setStandardDeviationForTheGaussianWalk(float value) {
        standardDeviationForTheGaussianWalk = static_cast<QuantLib::Real>(value);
    }

    void Firefly::setMinM(int value) {
        minM = value;
    }

    void Firefly::setMaxM(int value) {
        maxM = value;
    }

    double Firefly::objectiveFunction(queue_system::calc::queue& queue) {
        queue.calculate();
        return queue.get_average_application_time_in_queue();
    }

    int Firefly::optimize(queue_system::calc::queue& queue) {
        auto intensity = QuantLib::ext::make_shared<QuantLib::ExponentialIntensity>(initialAttractiveness, minimumAttractiveness, lightAbsorptionCoefficient);
        auto randomWalk = QuantLib::ext::make_shared<QuantLib::GaussianWalk>(standardDeviationForTheGaussianWalk);
        QuantLib::FireflyAlgorithm firefly(populationSize, intensity, randomWalk);

        auto func = [&](int m) {
            queue.set_service_channels(static_cast<std::uint64_t>(m));
            return objectiveFunction(queue);
        };

        int optimalM = minM;
        double bestObjectiveValue = func(optimalM);

        for (int m = minM + 1; m <= maxM; ++m) {
            double currentObjectiveValue = func(m);
            if (currentObjectiveValue < bestObjectiveValue) {
                bestObjectiveValue = currentObjectiveValue;
                optimalM = m;
            }
        }

        std::cout << "Optimal number of servers (m): " << optimalM << std::endl;
        return optimalM;
    }
}
