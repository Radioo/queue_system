#pragma once

#include <vector>

namespace queue_system::calc {
    class queue {
    public:
        queue(float stream_intensity, float average_service_intensity, float service_channels, float max_requests);

        void set_stream_intensity(float value);
        void set_average_service_intensity(float value);
        void set_service_channels(float value);
        void set_max_requests(float value);

        void calculate();
        [[nodiscard]] float get_load_factor() const;
        [[nodiscard]] const std::vector<float>& get_probabilities() const;

    private:
        float stream_intensity;
        float average_service_intensity;
        float service_channels;
        float max_requests;

        std::vector<float> probabilities;
        float load_factor = 0;
    };
}