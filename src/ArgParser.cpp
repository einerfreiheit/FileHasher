#include "ArgParser.hpp"

#include <iostream>
#include <sstream>

namespace file_hasher {
namespace {

constexpr size_t DEFAULT_CHUNK_SIZE{1 << 20};

void printHelp() {
    std::cout << "Usage: FileHasher <input_file> <output_file> optional <chunk_size>" << std::endl;
    std::cout << "FileHasher reads input file in chunks, computes hash and writes into output file"
              << std::endl;
    std::cout << "Default size of chunk is 1M, K and G suffices are also allowed. Value without "
                 "any suffix is considered as bytes"
              << std::endl;
    std::cout << "\t-h, --help print usage" << std::endl;
    std::cout << "Example:" << std::endl;
    std::cout << "\t./FileHasher input.txt output.txt 256K" << std::endl;
    std::cout << "\t./FileHasher -h" << std::endl;
}

size_t parseChunkSize(const std::string& input) {
    std::istringstream is(input);
    size_t res = 1;
    is >> res;
    int factor = 0;
    if (isalpha(input.back())) {
        switch (input.back()) {
        case 'K':
            factor = 10;
            break;
        case 'M':
            factor = 20;
            break;
        case 'G':
            factor = 30;
            break;
        default:
            std::ostringstream os;
            os << "Unknown suffix: " << input.back();
            throw std::runtime_error(os.str());
        }
    }

    return res << factor;
}

} // namespace

Configuration parse(int argc, char** argv) {
    for (int i = 1; i < argc; ++i) {
        std::string flag{argv[i]};
        if (flag == "-h" || flag == "--help") {
            printHelp();
            exit(0);
        }
    }

    if (argc < 3 || argc > 4) {
        printHelp();
        exit(1);
    }

    Configuration config;
    config.input_path = std::string{argv[1]};
    config.output_path = std::string{argv[2]};
    config.chunk_size = DEFAULT_CHUNK_SIZE;
    if (argc == 4) {
        try {
            config.chunk_size = parseChunkSize(std::string{argv[3]});
        } catch (const std::exception& e) {
            std::cerr << "Failed to parse chunk size: " << e.what();
            exit(1);
        }
    }
    return config;
}
} // namespace file_hasher
