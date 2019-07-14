/*
 * @Author: lu
 * @Date:   10-01-2018
 * @Last Modified by:   Lukasz
 * @Last Modified time: 05-12-2018
 */

#include "crc/bitop.h"

#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this
                          // in one cpp file
#include <catch2/catch.hpp>

TEST_CASE("bit::reverse works correctly. ", "[bitop]") {
  SECTION("Compile time tests") {
    static_assert(bit::reverse<uint8_t>(0xFF) == 0xFF);
    static_assert(bit::reverse<uint8_t>(0x00) == 0x00);
    static_assert(bit::reverse<uint8_t>(0x0F) == 0xF0);
    static_assert(bit::reverse<uint8_t>(0x01) == 0x80);
    static_assert(bit::reverse<uint8_t>(0x80) == 0x01);
    static_assert(bit::reverse<uint8_t>(0xAA) == 0x55);
    static_assert(bit::reverse<uint8_t>(0x55) == 0xAA);
    static_assert(bit::reverse<uint16_t>(0xFFFF) == 0xFFFF);
    static_assert(bit::reverse<uint16_t>(0x0000) == 0x0000);
    static_assert(bit::reverse<uint16_t>(0x000F) == 0xF000);
    static_assert(bit::reverse<uint16_t>(0x0001) == 0x8000);
    static_assert(bit::reverse<uint16_t>(0xAAAA) == 0x5555);
    static_assert(bit::reverse<uint16_t>(0x5555) == 0xAAAA);
    static_assert(bit::reverse<uint32_t>(0xFFFFFFFF) == 0xFFFFFFFF);
    static_assert(bit::reverse<uint32_t>(0x0000000F) == 0xF0000000);
    static_assert(bit::reverse<uint32_t>(0x00000001) == 0x80000000);
    static_assert(bit::reverse<uint32_t>(0x80000000) == 0x00000001);
    static_assert(bit::reverse<uint32_t>(0x00000000) == 0x00000000);
    static_assert(bit::reverse<uint32_t>(0xAAAAAAAA) == 0x55555555);
    static_assert(bit::reverse<uint32_t>(0x55555555) == 0xAAAAAAAA);
  }

  SECTION("8 bit") {
    REQUIRE(bit::reverse<uint8_t>(0xFF) == 0xFF);
    REQUIRE(bit::reverse<uint8_t>(0x00) == 0x00);
    REQUIRE(bit::reverse<uint8_t>(0x0F) == 0xF0);
    REQUIRE(bit::reverse<uint8_t>(0x01) == 0x80);
    REQUIRE(bit::reverse<uint8_t>(0x80) == 0x01);
    REQUIRE(bit::reverse<uint8_t>(0xAA) == 0x55);
    REQUIRE(bit::reverse<uint8_t>(0x55) == 0xAA);
  }

  SECTION("16 bit") {
    REQUIRE(bit::reverse<uint16_t>(0xFFFF) == 0xFFFF);
    REQUIRE(bit::reverse<uint16_t>(0x0000) == 0x0000);
    REQUIRE(bit::reverse<uint16_t>(0x000F) == 0xF000);
    REQUIRE(bit::reverse<uint16_t>(0x0001) == 0x8000);
    REQUIRE(bit::reverse<uint16_t>(0xAAAA) == 0x5555);
    REQUIRE(bit::reverse<uint16_t>(0x5555) == 0xAAAA);
  }

  SECTION("32 bit") {
    REQUIRE(bit::reverse<uint32_t>(0xFFFFFFFF) == 0xFFFFFFFF);
    REQUIRE(bit::reverse<uint32_t>(0x0000000F) == 0xF0000000);
    REQUIRE(bit::reverse<uint32_t>(0x00000001) == 0x80000000);
    REQUIRE(bit::reverse<uint32_t>(0x80000000) == 0x00000001);
    REQUIRE(bit::reverse<uint32_t>(0x00000000) == 0x00000000);
    REQUIRE(bit::reverse<uint32_t>(0xAAAAAAAA) == 0x55555555);
    REQUIRE(bit::reverse<uint32_t>(0x55555555) == 0xAAAAAAAA);
  }
}
