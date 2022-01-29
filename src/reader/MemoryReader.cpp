#include "reader/MemoryReader.hpp"
#include "types/MemoryChunk.hpp"

#include <sstream>

namespace file_hasher {

MemoryReader::MemoryReader(const std::string& fname, size_t chunk_size) :
    current_chunk_(0), offset_(0), chunk_size_(chunk_size) {
    file_ = boost::iostreams::mapped_file(fname, boost::iostreams::mapped_file::readonly);

    if (!file_.is_open()) {
        std::ostringstream os;
        os << "Failed to map file: " << fname;
        throw std::runtime_error(os.str());
    }

    total_chunks_ = file_.size() / chunk_size_;
    if (size_t last_chunk_size = file_.size() % chunk_size_; last_chunk_size != 0) {
        ++total_chunks_;
        last_chunk_size_ = last_chunk_size;
    } else {
        last_chunk_size_ = chunk_size_;
    }
}

MemoryReader::~MemoryReader() {
    file_.close();
}

std::shared_ptr<IChunk> MemoryReader::read() {
    if (current_chunk_ >= total_chunks_) {
        return nullptr;
    }

    size_t current_chunk_size =
        (current_chunk_ + 1 == total_chunks_) ? last_chunk_size_ : chunk_size_;

    std::shared_ptr<IChunk> chunk = std::make_shared<MemoryChunk>(
        current_chunk_, file_.const_data() + offset_, current_chunk_size);

    offset_ += current_chunk_size;
    ++current_chunk_;

    return chunk;
}

uint64_t MemoryReader::totalChunks() const {
    return total_chunks_;
}

} // namespace file_hasher
