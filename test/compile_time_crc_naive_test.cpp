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

using namespace ccrc::naive;

constexpr static uint8_t l_byte_raw_array_4[] = {0xDE, 0xAD, 0xBE, 0xEF};

TEST_CASE("Compile Time Tests: Small byte array") {
  constexpr auto &p = l_byte_raw_array_4;
  constexpr auto sz = sizeof(p);
  static_assert(sz == 4);
  static_assert(crc32_default_t::checksum_memory(p, sz) == 0x7C9CA35A);
  static_assert(bzip2_t::checksum_memory(p, sz) == 0x7E25E5E7UL);
  static_assert(crc32c_t::checksum_memory(p, sz) == 0xF1DC778EUL);
  static_assert(crc32d_t::checksum_memory(p, sz) == 0xD325B831UL);
  static_assert(mpeg2_t::checksum_memory(p, sz) == 0x81DA1A18UL);
  static_assert(posix_t::checksum_memory(p, sz) == 0xB921389CUL);
  static_assert(crc32q_t::checksum_memory(p, sz) == 0xA5932B47UL);
  static_assert(jamcrc_t::checksum_memory(p, sz) == 0x83635CA5UL);
  static_assert(xfer_t::checksum_memory(p, sz) == 0x6F455145UL);
  static_assert(ccitt_t::checksum_memory(p, sz) == 0x4097UL);
  static_assert(arc_t::checksum_memory(p, sz) == 0xE59BUL);
  static_assert(aug_ccitt_t::checksum_memory(p, sz) == 0xCA47UL);
  static_assert(buypass_t::checksum_memory(p, sz) == 0x962BUL);
  static_assert(cdma2000_16_t::checksum_memory(p, sz) == 0xAEB8UL);
  static_assert(dds_110_t::checksum_memory(p, sz) == 0x96F3UL);
  static_assert(dect_r_t::checksum_memory(p, sz) == 0x303BUL);
  static_assert(dect_x_t::checksum_memory(p, sz) == 0x303AUL);
  static_assert(dnp_t::checksum_memory(p, sz) == 0x60B8UL);
  static_assert(en_13757_t::checksum_memory(p, sz) == 0x27E4UL);
  static_assert(genibus_t::checksum_memory(p, sz) == 0xBF68UL);
  static_assert(maxim16_t::checksum_memory(p, sz) == 0x1A64UL);
  static_assert(mcrf4xx_t::checksum_memory(p, sz) == 0x1A34UL);
  static_assert(riello_t::checksum_memory(p, sz) == 0x3E73UL);
  static_assert(t10_dif_t::checksum_memory(p, sz) == 0x34DCUL);
  static_assert(teledisk_t::checksum_memory(p, sz) == 0x520DUL);
  static_assert(tms37157_t::checksum_memory(p, sz) == 0xE1CAUL);
  static_assert(usb_t::checksum_memory(p, sz) == 0x3E64UL);
  static_assert(crc16a_t::checksum_memory(p, sz) == 0x4F15UL);
  static_assert(kermit_t::checksum_memory(p, sz) == 0x1915UL);
  static_assert(modbus_t::checksum_memory(p, sz) == 0xC19BUL);
  static_assert(x_25_t::checksum_memory(p, sz) == 0xE5CBUL);
  static_assert(xmodem_t::checksum_memory(p, sz) == 0xC457UL);
  static_assert(default8_t::checksum_memory(p, sz) == 0xCAUL);
  static_assert(cdma2000_8_t::checksum_memory(p, sz) == 0x77UL);
  static_assert(darc_t::checksum_memory(p, sz) == 0xC0UL);
  static_assert(dvb_s2_t::checksum_memory(p, sz) == 0xA5UL);
  static_assert(ebu_t::checksum_memory(p, sz) == 0x64UL);
  static_assert(i_code_t::checksum_memory(p, sz) == 0x6BUL);
  static_assert(itu_t::checksum_memory(p, sz) == 0x9FUL);
  static_assert(maxim8_t::checksum_memory(p, sz) == 0x84UL);
  static_assert(rohc_t::checksum_memory(p, sz) == 0xC3UL);
  static_assert(wcdma_t::checksum_memory(p, sz) == 0xCCUL);
}
