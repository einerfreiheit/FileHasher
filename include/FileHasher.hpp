#pragma once

#include <memory>
#include <string>

namespace file_hasher {

struct Configuration;

class IReader;
class IHasher;
class IWriter;

class FileHasher {
public:
    FileHasher(const Configuration& configuration);
    ~FileHasher();

    FileHasher(const FileHasher&) = delete;
    FileHasher operator=(const FileHasher&) const = delete;

    void makeHash();

private:
    std::unique_ptr<IReader> reader_;
    std::unique_ptr<IHasher> hasher_;
    std::unique_ptr<IWriter> writer_;
};

} // namespace file_hasher
