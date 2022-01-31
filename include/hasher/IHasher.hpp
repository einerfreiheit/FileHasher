#pragma once

#include "types/IChunk.hpp"

#include <memory>

namespace file_hasher {

class IHasher {
public:
    virtual ~IHasher() = default;

    virtual std::shared_ptr<IChunk> hash(const std::shared_ptr<IChunk>& input) = 0;
    virtual size_t hashSizeBytes() const = 0;
};

} // namespace file_hasher
