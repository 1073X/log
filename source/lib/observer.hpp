#pragma once

#include "log/line.hpp"

namespace miu::log {

class observer {
  public:
    explicit observer(std::string_view type)
        : _type(type) {}

    virtual ~observer() = default;

    auto type() const { return _type; }

    virtual void write(line const&) = 0;

  private:
    std::string _type;
};

}    // namespace miu::log
