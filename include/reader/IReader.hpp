#pragma once

#include <memory>

namespace file_hasher {

class IChunk;

class IReader {
public:
    IReader() = default;
    virtual ~IReader() = default;
    IReader(const IReader&) = delete;
    IReader& operator=(const IReader&) = delete;

    virtual std::shared_ptr<IChunk> read() = 0;
    virtual uint64_t totalChunks() const = 0;
};

} // namespace file_hasher
