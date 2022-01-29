#pragma once

#include "IChunk.hpp"

namespace file_hasher {

class BaseChunk : public IChunk {
public:
    BaseChunk(uint64_t id) : id_(id) {}
    uint64_t id() const override {
        return id_;
    }

protected:
    uint64_t id_;
};

} // namespace file_hasher
