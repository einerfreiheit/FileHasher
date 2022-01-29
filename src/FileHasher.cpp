#include "FileHasher.hpp"
#include "Configuration.hpp"
#include "Runner.hpp"

#include "hasher/MD5Hasher.hpp"
#include "reader/MemoryReader.hpp"
#include "types/BufferedChunk.hpp"
#include "writer/MemoryWriter.hpp"

#include <boost/algorithm/hex.hpp>

namespace file_hasher {
namespace {

size_t encodedHashSize(size_t hash_size) {
    // 2 * N bytes in hex representation
    return 2 * hash_size;
}

std::shared_ptr<IChunk> encode(const std::shared_ptr<IChunk>& hash) {
    std::vector<char> result;
    result.reserve(encodedHashSize(hash->size()));
    boost::algorithm::hex(hash->data(), hash->data() + hash->size(), std::back_inserter(result));
    return std::make_shared<BufferedChunk>(hash->id(), std::move(result));
}

} // namespace

FileHasher::FileHasher(const Configuration& configuration) {
    // Memory mapped file has lower overhead than read for larger-than-page-sized (4 KiB) reads:
    // there is no extra copy from kernel to user space and less system calls.
    // Boost library provides a portable way to mmap files.
    reader_ = std::make_unique<MemoryReader>(configuration.input_path, configuration.chunk_size);
    hasher_ = std::make_unique<MD5Hasher>();
    size_t output_size = reader_->totalChunks() * encodedHashSize(hasher_->hashSizeBytes());
    writer_ = std::make_unique<MemoryWriter>(configuration.output_path, output_size);
}

void FileHasher::makeHash() {
    // Because MemoryReader does not actually read data but splits it into chunks
    // we read in single thread and process chunks asynchronously.
    // Runner is a task queue with a thread-pool.
    Runner runner;
    while (std::shared_ptr<IChunk> chunk = reader_->read()) {
        std::function<void()> func = [this, chunk]() {
            std::shared_ptr<IChunk> hash = hasher_->hash(chunk);
            std::shared_ptr<IChunk> encoded_hash = encode(hash);
            writer_->write(encoded_hash);
        };
        runner.pushTask(std::move(func));
    }
}

// for unique_ptr
FileHasher::~FileHasher() = default;

} // namespace file_hasher
