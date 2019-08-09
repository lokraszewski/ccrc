# cpp-crc

[![Build Status](https://travis-ci.com/lokraszewski/ccrc.svg?branch=master)](https://travis-ci.com/lokraszewski/ccrc) [![Version](https://img.shields.io/badge/version-1.3.1-blue.svg)](https://github.com/lokraszewski/ccrc/tags)

A simple header only CRC class. Currently only supports raw pointers to uint8_t data (bytes).

## Motivation
A simple CRC class without external dependancies, I also wanted to make use of `constexpr` to calculate LUTs at compile time.

### Prerequisites
* [cmake](https://cmake.org/)
* [Catch2](https://github.com/catchorg/Catch2) - for unit testing

## Build
```
mkdir build && cd build
conan install ..
cmake -DBUILD_TEST=ON -DBUILD_EXAMPLE=ON ..
make
```

### Unit tests
Unit tests are built on [Catch2](https://github.com/catchorg/Catch2).

## Versioning
We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/lokraszewski/ccrc/tags).


## Usage


```C++

#include "crc/crc.h"

using namespace ccrc::lut;


int main(int argc, char **argv) {
    constexpr static std::array<uint8_t, 4> t_small = {{0xDE, 0xAD, 0xBE, 0xEF}};
    std::cout << crc32_default_t::checksum(t_small) << std::endl;
}
```


## License
This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments
* [sunshine2k](http://www.sunshine2k.de/coding/javascript/crc/crc_js.html) - Online CRC calculator used to confirm checksums with all the neccearry pre-defined checksums.
* [jarro2783 - cxxopts](https://github.com/jarro2783/cxxopts) - awesome command line parser in C++.
* [Boost crc](https://www.boost.org/doc/libs/1_64_0/libs/crc/) - great library which has inspired this project.

See also the list of [contributors](https://github.com/lokraszewski/cpp-crc/contributors) who participated in this project.
