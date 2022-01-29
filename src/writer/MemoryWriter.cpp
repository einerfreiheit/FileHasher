#include "writer/MemoryWriter.hpp"
#include "types/IChunk.hpp"

#include <filesystem>
#include <fstream>
#include <sstream>

namespace file_hasher {

MemoryWriter::MemoryWriter(const std::string& path, size_t size) : offset_(0) {
    std::filesystem::path fpath(path);
    // Create file if does not exist.
    if (!std::filesystem::exists(fpath)) {
        std::ofstream{fpath};
    }

    // Resize file before maping.
    offset_ = std::filesystem::file_size(fpath);
    std::filesystem::resize_file(fpath, offset_ + size);

    file_ = boost::iostreams::mapped_file(path, boost::iostreams::mapped_file::readwrite);

    if (!file_.is_open()) {
        std::ostringstream os;
        os << "Failed to mmap file: " << path;
        throw std::runtime_error(os.str());
    }
}

MemoryWriter::~MemoryWriter() {
    file_.close();
}

void MemoryWriter::write(std::shared_ptr<IChunk> data) {
    size_t chunk_offset = offset_ + data->id() * data->size();
    std::memcpy(file_.data() + chunk_offset, data->data(), data->size());
}

} // namespace file_hasher
