/*
 * @Author: lu
 * @Date:   10-01-2018
 * @Last Modified by:   Lukasz
 * @Last Modified time: 05-12-2018
 */

#include <array>
#include <iostream>
#include <map>
#include <string>

#include "crc/crc.h"

#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this
                          // in one cpp file
#include <catch2/catch.hpp>

using namespace ccrc::base;

constexpr static std::array<uint8_t, 4> raw_array = {{0xDE, 0xAD, 0xBE, 0xEF}};

#define TEST_HELPER(type, data, expected)                                      \
  do {                                                                         \
    constexpr auto r = type::checksum(data);                                   \
    static_assert(r == expected);                                              \
    REQUIRE(r == expected);                                                    \
  } while (0)

TEST_CASE("Compile Time Tests: Small byte array") {
  TEST_HELPER(crc32_default_t, raw_array, 0x7C9CA35A);
  TEST_HELPER(bzip2_t, raw_array, 0x7E25E5E7UL);
  TEST_HELPER(crc32c_t, raw_array, 0xF1DC778EUL);
  TEST_HELPER(crc32d_t, raw_array, 0xD325B831UL);
  TEST_HELPER(mpeg2_t, raw_array, 0x81DA1A18UL);
  TEST_HELPER(posix_t, raw_array, 0xB921389CUL);
  TEST_HELPER(crc32q_t, raw_array, 0xA5932B47UL);
  TEST_HELPER(jamcrc_t, raw_array, 0x83635CA5UL);
  TEST_HELPER(xfer_t, raw_array, 0x6F455145UL);
  TEST_HELPER(ccitt_t, raw_array, 0x4097UL);
  TEST_HELPER(arc_t, raw_array, 0xE59BUL);
  TEST_HELPER(aug_ccitt_t, raw_array, 0xCA47UL);
  TEST_HELPER(buypass_t, raw_array, 0x962BUL);
  TEST_HELPER(cdma2000_16_t, raw_array, 0xAEB8UL);
  TEST_HELPER(dds_110_t, raw_array, 0x96F3UL);
  TEST_HELPER(dect_r_t, raw_array, 0x303BUL);
  TEST_HELPER(dect_x_t, raw_array, 0x303AUL);
  TEST_HELPER(dnp_t, raw_array, 0x60B8UL);
  TEST_HELPER(en_13757_t, raw_array, 0x27E4UL);
  TEST_HELPER(genibus_t, raw_array, 0xBF68UL);
  TEST_HELPER(maxim16_t, raw_array, 0x1A64UL);
  TEST_HELPER(mcrf4xx_t, raw_array, 0x1A34UL);
  TEST_HELPER(riello_t, raw_array, 0x3E73UL);
  TEST_HELPER(t10_dif_t, raw_array, 0x34DCUL);
  TEST_HELPER(teledisk_t, raw_array, 0x520DUL);
  TEST_HELPER(tms37157_t, raw_array, 0xE1CAUL);
  TEST_HELPER(usb_t, raw_array, 0x3E64UL);
  TEST_HELPER(crc16a_t, raw_array, 0x4F15UL);
  TEST_HELPER(kermit_t, raw_array, 0x1915UL);
  TEST_HELPER(modbus_t, raw_array, 0xC19BUL);
  TEST_HELPER(x_25_t, raw_array, 0xE5CBUL);
  TEST_HELPER(xmodem_t, raw_array, 0xC457UL);
  TEST_HELPER(default8_t, raw_array, 0xCAUL);
  TEST_HELPER(cdma2000_8_t, raw_array, 0x77UL);
  TEST_HELPER(darc_t, raw_array, 0xC0UL);
  TEST_HELPER(dvb_s2_t, raw_array, 0xA5UL);
  TEST_HELPER(ebu_t, raw_array, 0x64UL);
  TEST_HELPER(i_code_t, raw_array, 0x6BUL);
  TEST_HELPER(itu_t, raw_array, 0x9FUL);
  TEST_HELPER(maxim8_t, raw_array, 0x84UL);
  TEST_HELPER(rohc_t, raw_array, 0xC3UL);
  TEST_HELPER(wcdma_t, raw_array, 0xCCUL);
}
