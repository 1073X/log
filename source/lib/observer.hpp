#pragma once

namespace miu::log {

class line;

class observer {
  public:
    virtual ~observer() = default;
    virtual void write(line const&) = 0;
};

}    // namespace miu::log
