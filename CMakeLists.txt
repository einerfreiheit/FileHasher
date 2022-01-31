cmake_minimum_required(VERSION 3.2)

project(FileHasher)

find_package(Threads REQUIRED)
find_package(Boost 1.70.0 REQUIRED system iostreams)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_DEFAULT 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

if(CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE Release)
endif()

include_directories(
    "include"
    ${Boost_INCLUDE_DIR}
)

set(SOURCE
    "src/hasher/MD5Hasher.cpp"
    
    "src/reader/MemoryReader.cpp"

    "src/writer/MemoryWriter.cpp"

    "src/ArgParser.cpp"
    "src/FileHasher.cpp"
    "src/Runner.cpp"
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(
        -Wall
        -Werror
        -Wextra
        -pedantic
    )
endif()

add_executable(FileHasher "src/main.cpp" ${SOURCE}) 
target_link_libraries(FileHasher ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})
target_compile_features(FileHasher PRIVATE)
