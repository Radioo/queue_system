#include <boost/math/special_functions/factorials.hpp>
#include <cmath>

#include "queue_system/calc/queue.hpp"

queue_system::calc::queue::queue(const float stream_intensity, const float average_service_intensity,
                                 const std::uint64_t service_channels, const std::uint64_t max_requests):
    stream_intensity(stream_intensity), average_service_intensity(average_service_intensity),
    service_channels(service_channels), max_requests(max_requests) {}

void queue_system::calc::queue::set_stream_intensity(const float value) {
    stream_intensity = value;
}

void queue_system::calc::queue::set_average_service_intensity(const float value) {
    average_service_intensity = value;
}

void queue_system::calc::queue::set_service_channels(const std::uint64_t value) {
    service_channels = value;
}

void queue_system::calc::queue::set_max_requests(const std::uint64_t value) {
    max_requests = value;
}

void queue_system::calc::queue::calculate() {
    p = stream_intensity / average_service_intensity;

    calculate_probabilities();
}

float queue_system::calc::queue::get_load_factor() const {
    return load_factor;
}

const std::array<double, queue_system::calc::queue::PROBABILITY_COUNT>& queue_system::calc::queue::get_probabilities() const {
    return probabilities;
}

void queue_system::calc::queue::calculate_probabilities() {
    calculate_p0_probability();

    for(auto i = 1; i < PROBABILITY_COUNT; i++) {}
}

void queue_system::calc::queue::calculate_p0_probability() {
    const auto N_fact = boost::math::factorial<double>(max_requests);
    const auto m_fact = boost::math::factorial<double>(service_channels);

    double first_sum = 0;
    for(auto i = 0; i <= service_channels; i++) {
        const auto i_fact = boost::math::factorial<double>(i);
        const auto N_minus_i_fact = boost::math::factorial<double>(max_requests - i);
        const auto p_to_i = std::pow(p, i);

        first_sum += N_fact / (i_fact * N_minus_i_fact) * p_to_i;
    }

    double second_sum = 0;
    for(auto j = service_channels + 1; j <= max_requests; j++) {
        const auto N_minus_j_fact = boost::math::factorial<double>(max_requests - j);
        const auto m_to_j_minus_m = std::pow(service_channels, j - service_channels);
        const auto p_to_j = std::pow(p, j);

        second_sum += N_fact / (m_fact * N_minus_j_fact * m_to_j_minus_m) * p_to_j;
    }

    probabilities[0] = std::pow(first_sum + second_sum, -1);
}
