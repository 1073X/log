#pragma once

#include <com/variant.hpp>

namespace miu::log {

class tail {
  public:
    tail(bool is_intact)
        : _is_intact { is_intact } {}

    auto is_intact() const { return _is_intact; }

  private:
    bool _is_intact;
};

}    // namespace miu::log

DEF_VARIANT(miu::log::tail, CUSTOM_TYPE_ID + 2);
