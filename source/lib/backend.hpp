#pragma once

#include "observer.hpp"
#include "rings.hpp"

namespace miu::log {

class backend {
  public:
    backend(rings*, observer*);

    void watch(observer*);
    void dump();

  private:
    rings* _rings;
    observer* _observer { nullptr };
};

}    // namespace miu::log
