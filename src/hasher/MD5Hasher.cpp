#include "hasher/MD5Hasher.hpp"
#include "types/BufferedChunk.hpp"

#include <boost/uuid/detail/md5.hpp>

#include <iterator>

namespace file_hasher {

MD5Hasher::MD5Hasher() : size_(sizeof(boost::uuids::detail::md5::digest_type)) {}

std::shared_ptr<IChunk> MD5Hasher::hash(const std::shared_ptr<IChunk>& input) {
    using boost::uuids::detail::md5;

    md5 hash;
    hash.process_bytes(input->data(), input->size());
    md5::digest_type digest;
    hash.get_digest(digest);
    std::vector<char> result;
    result.reserve(size_);
    const char* begin = reinterpret_cast<const char*>(&digest);
    std::copy(begin, begin + size_, std::back_inserter(result));
    return std::make_shared<BufferedChunk>(input->id(), std::move(result));
}

size_t MD5Hasher::hashSizeBytes() const {
    return size_;
}

} // namespace file_hasher
