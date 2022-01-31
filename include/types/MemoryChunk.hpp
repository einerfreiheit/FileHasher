#pragma once

#include "BaseChunk.hpp"

namespace file_hasher {

// MemoryChunk class implements interface for a memory mapped data.
// MemoryChunk does not own or store data.

class MemoryChunk : public BaseChunk {
public:
    MemoryChunk(uint64_t id, const char* data, size_t size) :
        BaseChunk(id), data_(data), size_(size) {}
    const char* data() const override {
        return data_;
    }
    size_t size() const override {
        return size_;
    }

private:
    const char* data_;
    const size_t size_;
};

} // namespace file_hasher
