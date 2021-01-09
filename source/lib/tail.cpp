
#include "tail.hpp"

namespace miu::com {

template<>
void
variant::set<log::tail>(log::tail const&) {}

template<>
std::optional<log::tail>
variant::get<log::tail>() const {
    return std::make_optional<log::tail>();
}

}    // namespace miu::com
