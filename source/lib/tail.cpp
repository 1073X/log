
#include "log/tail.hpp"

namespace miu::log {

tail::tail(bool is_intact)
    : _is_intact { is_intact } {}

}    // namespace miu::log

namespace miu::com {

template<>
void
variant::set<log::tail>(log::tail const& v) {
    new (_value) bool { v.is_intact() };
}

template<>
std::optional<log::tail>
variant::get<log::tail>() const {
    auto is_intact = *(bool const*)_value;
    return std::make_optional<log::tail>(is_intact);
}

}    // namespace miu::com
