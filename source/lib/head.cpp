#include "head.hpp"

#include <com/variant.hpp>
#include <iostream>

namespace miu::com {

using log::head;
using log::severity;

template<>
void
variant::set<head>(head const& val) {
    new (_value) com::datetime { val.time() };
    *(severity*)(_value + 1) = val.severity();
}

template<>
std::optional<head>
variant::get<head>() const {
    auto time = *(com::datetime const*)_value;
    auto sev = *(log::severity const*)(_value + 1);
    return std::make_optional<head>(time, sev);
}

}    // namespace miu::com
