#pragma once

#include "log/line.hpp"

namespace miu::log {

class observer {
  public:
    virtual ~observer()             = default;
    virtual void write(line const&) = 0;
};

}    // namespace miu::log
