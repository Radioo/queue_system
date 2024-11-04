#pragma once

#include <array>
#include <cstdint>

namespace queue_system::calc {
    class queue {

    public:
        queue(
            float stream_intensity,
            float average_service_intensity,
            std::uint64_t service_channels,
            std::uint64_t max_requests,
            double cost_1,
            double cost_2
        );

        void set_stream_intensity(float value);
        void set_average_service_intensity(float value);
        void set_service_channels(std::uint64_t value);
        void set_max_requests(std::uint64_t value);
        void set_cost_1(double value);
        void set_cost_2(double value);
        void set_max_iterations(std::uint64_t value);
        void set_firefly_count(std::uint64_t value);

        void calculate();
        void optimize();
        [[nodiscard]] double get_relative_service_intensity() const;
        [[nodiscard]] const std::vector<double>& get_probabilities() const;
        [[nodiscard]] double get_average_queue_length() const;
        [[nodiscard]] double get_average_occupied_service_channels() const;
        [[nodiscard]] double get_absolute_ability_to_operate() const;
        [[nodiscard]] double get_average_applications() const;
        [[nodiscard]] double get_average_application_time_in_system() const;
        [[nodiscard]] double get_average_application_time_in_queue() const;
        [[nodiscard]] double get_objective_function_value() const;
        [[nodiscard]] double get_exact_optimized_m() const;
        [[nodiscard]] double get_rounded_optimized_m() const;
        [[nodiscard]] double get_exact_optimized_m_value() const;
        [[nodiscard]] double get_rounded_optimized_m_value() const;

    private:
        /// [λ] Intensywność strumienia zgłoszeń
        double stream_intensity;
        /// [μ] Średnia intensywność obsługi
        double average_service_intensity;
        /// [m] Liczba kanałów obsługi
        std::uint64_t service_channels;
        /// [N] Maksymalna liczba zgłoszeń w systemie
        std::uint64_t max_requests;
        double cost_1 = 0;
        double cost_2 = 0;
        std::uint64_t max_iterations = 0;
        std::uint64_t firefly_count = 0;

        std::vector<double> probabilities;
        /// [𝑝] Względna intensywność obsługi
        double relative_service_intensity = 0;
        double average_queue_length = 0;
        double average_occupied_service_channels = 0;
        double absolute_ability_to_operate = 0;
        /// [n kreska] Średnia ilość zgłoszeń
        double average_applications = 0;
        /// Średni czas przebywania zgłoszeń w systemie
        double average_application_time_in_system = 0;
        double average_application_time_in_queue = 0;
        double objective_function_value = 0;
        double exact_optimized_m = 0;
        double rounded_optimized_m = 0;
        double exact_optimized_m_value = 0;
        double rounded_optimized_m_value = 0;

        void calculate_probabilities();
        void calculate_p0_probability(double N_fact);
        [[nodiscard]] double calculate_less_or_equal_m_probability(std::uint64_t i, double N_fact) const;
        [[nodiscard]] double calculate_more_than_m_probability(std::uint64_t i, double N_fact) const;
        void calculate_average_queue_length();
        void calculate_average_occupied_service_channels();
        void calculate_absolute_ability_to_operate();
        void calculate_average_applications();
        void calculate_average_application_time_in_system();
        void calculate_average_application_time_in_queue();
        void calculate_objective_function_value();
    };
}