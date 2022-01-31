#pragma once

#include <cstddef>
#include <cstdint>

namespace file_hasher {

// Interface for a data chunk.

class IChunk {
public:
    virtual ~IChunk() = default;
    virtual const char* data() const = 0;
    virtual size_t size() const = 0;
    virtual uint64_t id() const = 0;
};

} // namespace file_hasher
