#pragma once

#include "IReader.hpp"

#include <boost/iostreams/device/mapped_file.hpp>

namespace file_hasher {

class MemoryReader : public IReader {
public:
    MemoryReader(const std::string& fname, size_t chunk_size);
    ~MemoryReader() override;

    std::shared_ptr<file_hasher::IChunk> read() override;
    uint64_t totalChunks() const override;

private:
    uint64_t current_chunk_;
    uint64_t total_chunks_;
    uint64_t offset_;

    size_t chunk_size_;
    size_t last_chunk_size_;

    boost::iostreams::mapped_file file_;
};

} // namespace file_hasher
