# cpp-crc

[![Build Status](https://travis-ci.com/lokraszewski/cpp-crc.svg?branch=master)](https://travis-ci.com/lokraszewski/cpp-crc)

A simple header only CRC class. Currently only supports a naive algorithm (slow) and raw pointers.


### Prerequisites
* [cmake](https://cmake.org/)
* [Google Benchmark](https://github.com/google/benchmark)
* clang

## Build
```
mkdir build
cd build
cmake ..
make
```
## Running the tests

### Unit tests
Unit tests are located in ./unit_tests and are built on [Catch2](https://github.com/catchorg/Catch2). To run:

```
build/bin/cpp-test0
```

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/lokraszewski/cpp-crc/tags).

## TODOs
* Implement the fast algorithm based on a look-up table.
* Consider removing the need to instanciate the object before getting a CRC.
* Add std containers support (std::array && std::vector).


## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* [sunshine2k](http://www.sunshine2k.de/coding/javascript/crc/crc_js.html) - Online CRC calculator used to confirm checksums with all the neccearry pre-defined checksums.

See also the list of [contributors](https://github.com/lokraszewski/cpp-crc/contributors) who participated in this project.
