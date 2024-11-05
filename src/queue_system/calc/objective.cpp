#include <boost/math/special_functions/factorials.hpp>
#include <boost/math/special_functions/binomial.hpp>

#include "queue_system/calc/objective.hpp"

queue_system::calc::objective::objective(
    const std::uint64_t max_requests,
    const double cost_1,
    const double cost_2,
    const double relative_service_intensity
):
    max_requests(max_requests),
    cost_1(cost_1),
    cost_2(cost_2),
    relative_service_intensity(relative_service_intensity) {}

QuantLib::Real queue_system::calc::objective::value(const QuantLib::Array& x) const {
    const auto m = static_cast<std::uint64_t>(x[0]);
    const auto m_fact = boost::math::factorial<double>(m);

    const auto first_part = cost_1 * static_cast<double>(m);

    double first_sum = 0;
    for(auto i = 0; i <= m; i++) {
        first_sum +=
                i *
                boost::math::binomial_coefficient<double>(max_requests, i) *
                std::pow(relative_service_intensity, i);
    }

    double second_sum = 0;
    for(auto j = m + 1; j <= max_requests; j++) {
        second_sum +=
                static_cast<double>(j) *
                boost::math::binomial_coefficient<double>(max_requests, j) *
                (
                        (boost::math::factorial<double>(j) * std::pow(relative_service_intensity, j)) /
                        (m_fact * std::pow(m, j - m))
                );
    }


    double third_sum = 0;
    for(auto i = 0; i <= m; i++) {
        third_sum +=
                boost::math::binomial_coefficient<double>(max_requests, i) *
                std::pow(relative_service_intensity, i);
    }

    double fourth_sum = 0;
    for(auto j = m + 1; j <= max_requests; j++) {
        fourth_sum +=
                boost::math::binomial_coefficient<double>(max_requests, j) *
                (
                        (boost::math::factorial<double>(j) * std::pow(relative_service_intensity, j)) /
                        (m_fact * std::pow(m, j - m))
                );
    }

    const auto second_part = cost_2 * ((first_sum + second_sum) / (third_sum + fourth_sum));

    return first_part + second_part;
}

QuantLib::Array queue_system::calc::objective::values(const QuantLib::Array& x) const {
    return x;
}
