#pragma once

#include <com/variant.hpp>

namespace miu::log {

class tail {};

}    // namespace miu::log

DEF_VARIANT(miu::log::tail, CUSTOM_TYPE_ID + 2);
