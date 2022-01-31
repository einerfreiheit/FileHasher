#pragma once

#include "IWriter.hpp"

#include <boost/iostreams/device/mapped_file.hpp>

namespace file_hasher {

class IChunk;

class MemoryWriter : public IWriter {
public:
    MemoryWriter(const std::string& path, size_t size);
    ~MemoryWriter() override;

    void write(std::shared_ptr<IChunk> data);

private:
    boost::iostreams::mapped_file file_;
    size_t offset_;
};

} // namespace file_hasher
