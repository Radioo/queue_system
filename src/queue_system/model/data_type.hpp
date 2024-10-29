#pragma once

#include <cstdint>

namespace queue_system::model {
    enum class data_type : std::uint8_t {
        RELATIVE_SERVICE_INTENSITY = 0,
        PROBABILITY_P0 = 1,
        PROBABILITY_P1 = 2,
        PROBABILITY_P2 = 3,
        PROBABILITY_P3 = 4,
        PROBABILITY_P4 = 5,
        PROBABILITY_P5 = 6,
        AVERAGE_QUEUE_LENGTH = 7,
        AVERAGE_OCCUPIED_SERVICE_CHANNELS = 8,
        ABSOLUTE_ABILITY_TO_OPERATE = 9,
        AVERAGE_APPLICATIONS = 10,
        AVERAGE_APPLICATION_TIME_IN_SYSTEM = 11,
        AVERAGE_APPLICATION_TIME_IN_QUEUE = 12,
    };
};