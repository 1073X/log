#pragma once

#include "observer.hpp"
#include "rings.hpp"

namespace miu::log {

class backend {
  public:
    backend(rings*);

    void watch(observer*);
    void dump();

  private:
    std::vector<observer*> _obs;
    rings* _rings;
};

}    // namespace miu::log
