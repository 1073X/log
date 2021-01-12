#pragma once

#include "observer.hpp"
#include "rings.hpp"

namespace miu::log {

class backend {
  public:
    backend(rings*);

    void dump(observer*);

  private:
    rings* _rings;
};

}    // namespace miu::log
