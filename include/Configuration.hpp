#pragma once

#include <string>

namespace file_hasher {

struct Configuration {
    std::string input_path;
    std::string output_path;
    size_t chunk_size;
};

} // namespace file_hasher
