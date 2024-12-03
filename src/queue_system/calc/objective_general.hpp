#pragma once

#include <cstdint>
#include <ql/math/optimization/costfunction.hpp>

namespace queue_system::calc {
    class objective_general : public QuantLib::CostFunction {
    public:
        explicit objective_general(
            std::uint64_t max_requests,
            double cost_1,
            double cost_2,
            double relative_service_intensity
        );
        ~objective_general() override = default;

        [[nodiscard]] QuantLib::Real value(const QuantLib::Array& x) const override;
        [[nodiscard]] QuantLib::Array values(const QuantLib::Array& x) const override;

    private:
        std::uint64_t max_requests;
        double cost_1;
        double cost_2;
        double relative_service_intensity;
    };
}