#pragma once

#include <cstdint>

namespace queue_system::model {
    enum class data_type : std::uint8_t {
        LOAD_FACTOR = 0,
        PROBABILITY_P0 = 1,
        PROBABILITY_P1 = 1,
        PROBABILITY_P2 = 1,
    };
};