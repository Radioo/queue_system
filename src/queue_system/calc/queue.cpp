#include <boost/math/special_functions/binomial.hpp>
#include <cmath>
#include <ql/math/optimization/constraint.hpp>
#include <ql/experimental/math/fireflyalgorithm.hpp>

#include "queue_system/calc/queue.hpp"
#include "queue_system/calc/objective.hpp"

queue_system::calc::queue::queue(
    const float stream_intensity,
    const float average_service_intensity,
    const std::uint64_t service_channels,
    const std::uint64_t max_requests,
    const double cost_1,
    const double cost_2
):
    stream_intensity(stream_intensity),
    average_service_intensity(average_service_intensity),
    service_channels(service_channels),
    max_requests(max_requests),
    cost_1(cost_1),
    cost_2(cost_2) {}

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

void queue_system::calc::queue::set_cost_1(const double value) {
    cost_1 = value;
}

void queue_system::calc::queue::set_cost_2(const double value) {
    cost_2 = value;
}

void queue_system::calc::queue::set_max_iterations(const std::uint64_t value) {
    max_iterations = value;
}

void queue_system::calc::queue::set_firefly_count(const std::uint64_t value) {
    firefly_count = value;
}

void queue_system::calc::queue::calculate() {
    relative_service_intensity = stream_intensity / average_service_intensity;

    calculate_probabilities();
    calculate_average_queue_length();
    calculate_average_occupied_service_channels();
    calculate_absolute_ability_to_operate();
    calculate_average_applications();
    calculate_average_application_time_in_system();
    calculate_average_application_time_in_queue();
    calculate_objective_function_value();
}

void queue_system::calc::queue::optimize() {
    QuantLib::BoundaryConstraint constraint(
        1,
        static_cast<double>(max_requests)
    );

    const QuantLib::Array start(1, 1);
    QuantLib::Real vola = 1.5;
    QuantLib::Real intense = 1.0;
    auto seed = 127;
    const auto intensity = QuantLib::ext::make_shared<QuantLib::ExponentialIntensity>(10.0, 1e-8, intense);
    const auto walk = QuantLib::ext::make_shared<QuantLib::LevyFlightWalk>(vola, 0.1, 1.0, seed);
    objective objective_function(
        max_requests,
        cost_1,
        cost_2,
        relative_service_intensity
    );

    QuantLib::FireflyAlgorithm algorithm(
        firefly_count,
        intensity,
        walk,
        40
    );

    const QuantLib::EndCriteria end_criteria(
        max_iterations,
        1000,
        1.0e-8,
        1.0e-8,
        1.0e-8
    );

    QuantLib::Problem problem(objective_function, constraint, start);

    algorithm.minimize(problem, end_criteria);

    auto result = problem.currentValue();
    auto value = result[0];

    exact_optimized_m = value;
    exact_optimized_m_value = objective_function.value(result);

    if(const auto low_value = std::floor(value); value != low_value) {
        const auto high_value = std::ceil(value);
        const auto low_result = QuantLib::Array(1, low_value);

        if(const auto high_result = QuantLib::Array(1, high_value); objective_function.value(low_result) > objective_function.value(high_result)) {
            result = high_result;
            value = high_value;
        }
        else {
            result = low_result;
            value = low_value;
        }
    }

    rounded_optimized_m = value;
    rounded_optimized_m_value = objective_function.value(result);
}

const std::vector<double>& queue_system::calc::queue::get_probabilities() const {
    return probabilities;
}

double queue_system::calc::queue::get_average_queue_length() const {
    return average_queue_length;
}

void queue_system::calc::queue::calculate_probabilities() {
    const auto N_fact = boost::math::factorial<double>(max_requests);
    auto probability_count = max_requests + 2;
    if (probability_count < 6) {
        probability_count = 6;
    }
    probabilities.resize(probability_count);
    calculate_p0_probability(N_fact);

    for(auto i = 1; i < max_requests + 2; i++) {
        if(i >= 1 && i <= service_channels) {
            probabilities[i] = calculate_less_or_equal_m_probability(i, N_fact);
        }
        else if(i >= service_channels + 1 && i <= max_requests) {
            probabilities[i] = calculate_more_than_m_probability(i, N_fact);
        }
        else {
            probabilities[i] = 0;
        }
    }
}

void queue_system::calc::queue::calculate_p0_probability(const double N_fact) {
    const auto m_fact = boost::math::factorial<double>(service_channels);

    double first_sum = 0;
    for(auto i = 0; i <= service_channels; i++) {
        const auto i_fact = boost::math::factorial<double>(i);
        const auto N_minus_i_fact = boost::math::factorial<double>(max_requests - i);
        const auto p_to_i = std::pow(relative_service_intensity, i);

        first_sum += N_fact / (i_fact * N_minus_i_fact) * p_to_i;
    }

    double second_sum = 0;
    for(auto j = service_channels + 1; j <= max_requests; j++) {
        const auto N_minus_j_fact = boost::math::factorial<double>(max_requests - j);
        const auto m_to_j_minus_m = std::pow(service_channels, j - service_channels);
        const auto p_to_j = std::pow(relative_service_intensity, j);

        second_sum += N_fact / (m_fact * N_minus_j_fact * m_to_j_minus_m) * p_to_j;
    }

    probabilities[0] = std::pow(first_sum + second_sum, -1);
}

double queue_system::calc::queue::calculate_less_or_equal_m_probability(const std::uint64_t i, const double N_fact) const {
    const auto i_fact = boost::math::factorial<double>(i);
    const auto N_minus_i_fact = boost::math::factorial<double>(max_requests - i);
    const auto p_to_i_fact = std::pow(relative_service_intensity, i);

    return N_fact / (i_fact * N_minus_i_fact) * p_to_i_fact * probabilities[0];
}

double queue_system::calc::queue::calculate_more_than_m_probability(const std::uint64_t i, const double N_fact) const {
    const auto m_fact = boost::math::factorial<double>(service_channels);
    const auto m_to_i_minus_m = std::pow(service_channels, i - service_channels);
    const auto N_minus_i_fact = boost::math::factorial<double>(max_requests - i);
    const auto p_to_i = std::pow(relative_service_intensity, i);

    return N_fact / (m_fact * m_to_i_minus_m * N_minus_i_fact) * p_to_i * probabilities[0];
}

void queue_system::calc::queue::calculate_average_queue_length() {
    double sum = 0;
    for(auto i = 0; i <= max_requests - service_channels; i++) {
        sum += i * probabilities[2 + i];
    }

    average_queue_length = sum;
}

void queue_system::calc::queue::calculate_average_occupied_service_channels() {
    double first_sum = 0;
    for(auto r = 0; r <= service_channels - 1; r++) {
        first_sum += r * probabilities[r];
    }

    double second_sum = 0;
    for(auto k = service_channels; k <= max_requests; k++) {
        second_sum += probabilities[k];
    }

    average_occupied_service_channels = first_sum + (static_cast<double>(service_channels) * second_sum);
}

double queue_system::calc::queue::get_average_occupied_service_channels() const {
    return average_occupied_service_channels;
}

void queue_system::calc::queue::calculate_absolute_ability_to_operate() {
    absolute_ability_to_operate = average_occupied_service_channels * stream_intensity;
}

double queue_system::calc::queue::get_absolute_ability_to_operate() const {
    return absolute_ability_to_operate;
}

void queue_system::calc::queue::calculate_average_applications() {
    average_applications = static_cast<double>(max_requests) - (average_occupied_service_channels / relative_service_intensity);
}

double queue_system::calc::queue::get_average_applications() const {
    return average_applications;
}

void queue_system::calc::queue::calculate_average_application_time_in_system() {
    average_application_time_in_system = average_applications / (stream_intensity * (static_cast<double>(max_requests) - average_applications));
}

double queue_system::calc::queue::get_average_application_time_in_system() const {
    return average_application_time_in_system;
}

void queue_system::calc::queue::calculate_average_application_time_in_queue() {
    average_application_time_in_queue = average_application_time_in_system - (1 / average_service_intensity);
}

void queue_system::calc::queue::calculate_objective_function_value() {
    objective_function_value = cost_1 * static_cast<double>(service_channels) + cost_2 * average_applications;
}

double queue_system::calc::queue::get_average_application_time_in_queue() const {
    return average_application_time_in_queue;
}

double queue_system::calc::queue::get_objective_function_value() const {
    return objective_function_value;
}

double queue_system::calc::queue::get_exact_optimized_m() const {
    return exact_optimized_m;
}

double queue_system::calc::queue::get_rounded_optimized_m() const {
    return rounded_optimized_m;
}

double queue_system::calc::queue::get_exact_optimized_m_value() const {
    return exact_optimized_m_value;
}

double queue_system::calc::queue::get_rounded_optimized_m_value() const {
    return rounded_optimized_m_value;
}

double queue_system::calc::queue::get_relative_service_intensity() const {
    return relative_service_intensity;
}
