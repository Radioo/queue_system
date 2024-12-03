#include <boost/math/special_functions/factorials.hpp>
#include <boost/math/special_functions/binomial.hpp>
#include <boost/math/special_functions/gamma.hpp>

#include "queue_system/calc/objective_general.hpp"

queue_system::calc::objective_general::objective_general(
    const std::uint64_t max_requests,
    const double cost_1,
    const double cost_2,
    const double relative_service_intensity
):
    max_requests(max_requests),
    cost_1(cost_1),
    cost_2(cost_2),
    relative_service_intensity(relative_service_intensity) {}

QuantLib::Real queue_system::calc::objective_general::value(const QuantLib::Array& x) const {
    const auto m = static_cast<std::uint64_t>(x[0]);
    const auto m_fact = boost::math::factorial<double>(m);

    const auto first_part = cost_1 * static_cast<double>(m);

    double first_sum = 0;
    for(auto i = m + 1; i <= max_requests; i++) {
        first_sum +=
            boost::math::binomial_coefficient<double>(max_requests, i) *
            (
                (
                    boost::math::factorial<double>(i) *
                    boost::math::tgamma<double>(relative_service_intensity + 1)
                ) /
                (
                    m_fact *
                    std::pow(m, i - m)
                )
            );
    }

    double second_sum = 0;
    for(auto i = 1; i <= m - 1; i++) {
        second_sum +=
            boost::math::binomial_coefficient<double>(max_requests, i) *
            std::pow(relative_service_intensity, i);
    }

    double third_sum = 0;
    for(auto i = m; i <= max_requests; i++) {
        third_sum +=
            boost::math::binomial_coefficient<double>(max_requests, i) *
            (
                (
                    boost::math::factorial<double>(i) *
                    boost::math::tgamma<double>(relative_service_intensity + 1)
                ) /
                (
                    m_fact *
                    std::pow(m, i - m)
                )
            );
    }

    const auto second_part =
        (
            cost_2 / (1 + relative_service_intensity)
        ) *
        (
            (relative_service_intensity * max_requests) +
            (
                (m * first_sum) /
                (second_sum + third_sum)
            )
        );

    return first_part + second_part;
}

QuantLib::Array queue_system::calc::objective_general::values(const QuantLib::Array& x) const {
    return  x;
}
