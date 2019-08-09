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
cmake -DBUILD_TEST=ON -DBUILD_EXAMPLE=ON ..
make -j
```

### Unit tests
Unit tests are built on [Catch2](https://github.com/catchorg/Catch2).

To run tests simply run:
```
./run_all_tests.sh
```

### Example
The project provides an example application. Currently the application supports the following operations:
```
./bin/ccrc_example -h                                                                     ✹
Example crc usage.
Usage:
  crc_example [OPTION...]

      --help       Print help
  -f, --file arg   File input.
  -i, --input arg  String input

```

Example input string:
```
./bin/ccrc_example -i "123456789"                                                         ✹
[2019-08-09 23:59:35.762] [crc] [info] Attempting to checksum string : '123456789'
[2019-08-09 23:59:35.762] [crc] [info]  crc32_default_t : 0xcbf43926
[2019-08-09 23:59:35.762] [crc] [info]          bzip2_t : 0xfc891918
[2019-08-09 23:59:35.762] [crc] [info]         crc32c_t : 0xe3069283
[2019-08-09 23:59:35.762] [crc] [info]         crc32d_t : 0x87315576
[2019-08-09 23:59:35.762] [crc] [info]          mpeg2_t : 0x376e6e7
[2019-08-09 23:59:35.762] [crc] [info]          posix_t : 0x765e7680
### More results here
[2019-08-09 23:59:35.762] [crc] [info]         i_code_t : 0x7e
[2019-08-09 23:59:35.762] [crc] [info]            itu_t : 0xa1
[2019-08-09 23:59:35.762] [crc] [info]         maxim8_t : 0xa1
[2019-08-09 23:59:35.762] [crc] [info]           rohc_t : 0xd0
[2019-08-09 23:59:35.762] [crc] [info]          wcdma_t : 0x25

```
You can compare these values to an online calculator such as [crccalc](https://crccalc.com/?crc=123456789&method=crc8&datatype=ascii&outtype=hex)

You can also checksum files:
```
./bin/ccrc_example -f ../LICENSE.md                                                       ✹
[2019-08-10 00:00:48.094] [crc] [info] Attempting to checksum file : '../LICENSE.md'
[2019-08-10 00:00:48.094] [crc] [info] 1075 bytes read
[2019-08-10 00:00:48.094] [crc] [info]  crc32_default_t : 0x29d01e9d
[2019-08-10 00:00:48.094] [crc] [info]          bzip2_t : 0x9c17fcb9
[2019-08-10 00:00:48.094] [crc] [info]         crc32c_t : 0x101f9585
[2019-08-10 00:00:48.094] [crc] [info]         crc32d_t : 0x1f31440
[2019-08-10 00:00:48.095] [crc] [info]          mpeg2_t : 0x63e80346
[2019-08-10 00:00:48.095] [crc] [info]          posix_t : 0x267b554
### More results here
[2019-08-10 00:00:48.100] [crc] [info]         i_code_t : 0x81
[2019-08-10 00:00:48.100] [crc] [info]            itu_t : 0xfe
[2019-08-10 00:00:48.100] [crc] [info]         maxim8_t : 0xfb
[2019-08-10 00:00:48.100] [crc] [info]           rohc_t : 0xc8
[2019-08-10 00:00:48.101] [crc] [info]          wcdma_t : 0x4f

```
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
