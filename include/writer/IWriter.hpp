#pragma once

#include <memory>

namespace file_hasher {

class IChunk;

class IWriter {
public:
    IWriter(const IWriter&) = delete;
    IWriter& operator=(const IWriter&) = delete;

    IWriter() = default;
    virtual ~IWriter() = default;

    virtual void write(std::shared_ptr<IChunk> data) = 0;
};

} // namespace file_hasher
