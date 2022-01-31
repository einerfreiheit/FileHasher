#pragma once

#include "IHasher.hpp"

namespace file_hasher {

class MD5Hasher : public IHasher {
public:
    MD5Hasher();
    std::shared_ptr<IChunk> hash(const std::shared_ptr<IChunk>& input) override;
    size_t hashSizeBytes() const override;

private:
    size_t size_;
};

} // namespace file_hasher
