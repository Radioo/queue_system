#pragma once

#include <cstdint>

namespace queue_system::model {
    enum class data_type_col : std::uint8_t {
        NAME = 0,
        VALUE = 1,
    };
}