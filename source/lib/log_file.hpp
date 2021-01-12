#pragma once

#include <com/date.hpp>
#include <filesystem>
#include <fstream>

#include "observer.hpp"

namespace miu::log {

class log_file : public observer {
  private:
    static auto make_pathname(std::string_view path, std::string_view name, com::date date) {
        char filename[128];
        std::snprintf(
            filename, sizeof(filename), "%s_%s.log", name.data(), std::to_string(date).c_str());

        auto pathname = std::filesystem::path { path };
        std::filesystem::create_directories(pathname);
        return pathname / filename;
    }

  public:
    log_file(std::string_view path, std::string_view name, com::date date)
        : _pathname(make_pathname(path, name, date))
        , _ss(_pathname, std::ios_base::out | std::ios_base::app) {}

    auto pathname() const { return _pathname; }

    void write(line const& l) override { _ss << std::to_string(l) << std::endl; }

  private:
    std::filesystem::path _pathname;
    std::ofstream _ss;
};

}    // namespace miu::log
