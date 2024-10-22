#include "queue_system/calc/queue.hpp"

queue_system::calc::queue::queue(const float stream_intensity, const float average_service_intensity, const float service_channels, const float max_requests):
    stream_intensity(stream_intensity), average_service_intensity(average_service_intensity), service_channels(service_channels), max_requests(max_requests) {}

void queue_system::calc::queue::set_stream_intensity(const float value) {
    stream_intensity = value;
}

void queue_system::calc::queue::set_average_service_intensity(const float value) {
    average_service_intensity = value;
}

void queue_system::calc::queue::set_service_channels(const float value) {
    service_channels = value;
}

void queue_system::calc::queue::set_max_requests(const float value) {
    max_requests = value;
}

void queue_system::calc::queue::calculate() {

}

float queue_system::calc::queue::get_load_factor() const {
    return load_factor;
}

const std::vector<float>& queue_system::calc::queue::get_probabilities() const {
    return probabilities;
}

