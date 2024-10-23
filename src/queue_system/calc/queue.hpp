#pragma once

#include <array>
#include <cstdint>

namespace queue_system::calc {
    class queue {

    public:
        queue(float stream_intensity, float average_service_intensity, std::uint64_t service_channels, std::uint64_t max_requests);

        static constexpr std::uint8_t PROBABILITY_COUNT = 3;

        void set_stream_intensity(float value);
        void set_average_service_intensity(float value);
        void set_service_channels(std::uint64_t value);
        void set_max_requests(std::uint64_t value);

        void calculate();
        [[nodiscard]] float get_load_factor() const;
        [[nodiscard]] const std::array<double, PROBABILITY_COUNT>& get_probabilities() const;

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

        void calculate_probabilities();
        void calculate_p0_probability();
    };
}