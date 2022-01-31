#include "ArgParser.hpp"
#include "Configuration.hpp"
#include "FileHasher.hpp"

#include <chrono>
#include <iostream>

namespace {

class Timer {
public:
    Timer() : start_() {
        reset();
    }
    void reset() {
        start_ = clock_::now();
    }
    double elapsed() const {
        return std::chrono::duration_cast<second_>(clock_::now() - start_).count();
    }

private:
    using clock_ = std::chrono::high_resolution_clock;
    using second_ = std::chrono::duration<double, std::ratio<1>>;
    std::chrono::time_point<clock_> start_;
};

} // namespace

int main(int argc, char** argv) {
    using namespace file_hasher;
    Configuration config = parse(argc, argv);

    // FileHasher performs all io operation and computes hash
    FileHasher hasher(config);

    Timer t;
    hasher.makeHash();
    std::cout << "Elapsed time: " << t.elapsed() << std::endl;
    return 0;
}
