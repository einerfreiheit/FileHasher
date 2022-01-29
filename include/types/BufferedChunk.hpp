#pragma once

#include "BaseChunk.hpp"

#include <vector>

namespace file_hasher {

// BufferedChunk stores data in its own buffer

class BufferedChunk : public BaseChunk {
public:
    BufferedChunk(uint64_t id, std::vector<char> data) : BaseChunk(id), buff_(std::move(data)) {}

    const char* data() const override {
        return buff_.data();
    }

    size_t size() const override {
        return buff_.size();
    }

private:
    std::vector<char> buff_;
};

} // namespace file_hasher
