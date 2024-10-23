#pragma once

#include <array>
#include <cstdint>

namespace queue_system::calc {
    class queue {

    public:
        queue(float stream_intensity, float average_service_intensity, std::uint64_t service_channels, std::uint64_t max_requests);

        static constexpr std::uint8_t PROBABILITY_COUNT = 6;

        void set_stream_intensity(float value);
        void set_average_service_intensity(float value);
        void set_service_channels(std::uint64_t value);
        void set_max_requests(std::uint64_t value);

        void calculate();
        [[nodiscard]] float get_load_factor() const;
        [[nodiscard]] const std::array<double, PROBABILITY_COUNT>& get_probabilities() const;
        [[nodiscard]] double get_average_queue_length() const;

    private:
        /// [λ] Intensywność strumienia zgłoszeń
        float stream_intensity;
        /// [μ] Średnia intensywność obsługi
        float average_service_intensity;
        /// [m] Liczba kanałów obsługi
        std::uint64_t service_channels;
        /// [N] Maksymalna liczba zgłoszeń w systemie
        std::uint64_t max_requests;

        std::array<double, PROBABILITY_COUNT> probabilities = {0.0, 0.0, 0.0};
        float load_factor = 0;
        /// [𝑝] ???
        float p = 0;
        double average_queue_length = 0;

        void calculate_probabilities();
        void calculate_p0_probability(double N_fact);
        [[nodiscard]] double calculate_less_or_equal_m_probability(std::uint64_t i, double N_fact) const;
        [[nodiscard]] double calculate_more_than_m_probability(std::uint64_t i, double N_fact) const;
        void calculate_average_queue_length();
    };
}