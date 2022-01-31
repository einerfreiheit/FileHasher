# FileHasher

A portable console application for computing file hash for Linux / Windows.

## Build

Install libboost-dev before: 
```
apt-get install libboost-dev
git clone https://github.com/einerfreiheit/FileHasher.git
cd FileHasher
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ../
make
```

## Launch

Get usage with example command:

```
./FileHasher -h

Usage: FileHasher <input_file> <output_file> optional <chunk_size>
FileHasher reads input file in chunks, computes hash and writes into output file
Default size of chunk is 1M (K and G suffices are also allowed). Value without any suffix is considered as bytes
        -h, --help print usage
Example:
        ./FileHasher input.txt output.txt 256K
        ./FileHasher -h
```
