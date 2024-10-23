#pragma once

#include <cstdint>

namespace queue_system::model {
    enum class data_type : std::uint8_t {
        PROBABILITY_P0 = 0,
        PROBABILITY_P1 = 1,
        PROBABILITY_P2 = 2,
        PROBABILITY_P3 = 3,
        PROBABILITY_P4 = 4,
        PROBABILITY_P5 = 5,
        AVERAGE_QUEUE_LENGTH = 6,
    };
};