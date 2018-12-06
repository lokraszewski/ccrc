# cpp-crc

[![Build Status](https://travis-ci.com/lokraszewski/cpp-crc.svg?branch=master)](https://travis-ci.com/lokraszewski/cpp-crc) [![Version](https://img.shields.io/badge/version-1.2.0-blue.svg)](https://github.com/lokraszewski/cpp-crc/tags)

A simple header only CRC class. Currently only supports raw pointers.

## Motivation 
A standalone flexible crc solution with API similiar to that of [boost crc](https://www.boost.org/doc/libs/1_64_0/libs/crc/)


### Prerequisites
* [cmake](https://cmake.org/)
* [conan](https://conan.io/) - For Catch2 unit tests.

## Build
```
mkdir build && cd build
conan install ..
cmake -DBUILD_TEST=ON -DBUILD_EXAMPLE=ON ..
make
```

## Running the tests

### Unit tests
Unit tests are built on [Catch2](https://github.com/catchorg/Catch2). To run:

```
build/bin/unit_tests
```

## Versioning
We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/lokraszewski/cpp-crc/tags).

## TODOs
* Add std containers support (iterator containers).


## License
This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments
* [sunshine2k](http://www.sunshine2k.de/coding/javascript/crc/crc_js.html) - Online CRC calculator used to confirm checksums with all the neccearry pre-defined checksums.
* [jarro2783 - cxxopts](https://github.com/jarro2783/cxxopts) - awesome command line parser in C++. 
* [Boost crc](https://www.boost.org/doc/libs/1_64_0/libs/crc/) - great library which has inspired this project.

See also the list of [contributors](https://github.com/lokraszewski/cpp-crc/contributors) who participated in this project.
