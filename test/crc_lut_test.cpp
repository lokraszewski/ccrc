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

using namespace ccrc::fast;

const static std::string l_lorem_psum =
    "Lorem ipsum dolor sit amet, condimentum id, quia ut enim. Congue lacus "
    "justo et egestas lacus purus, nam molestie et dictumst "
    "praesent, porta placerat sodales magnis mi rerum, per justo pede orci in "
    "vitae, mauris in. Elit aliquet ac et sit suspendisse tortor, "
    "malesuada arcu imperdiet varius est maecenas nunc, aliquam leo, ac diam. "
    "Interdum volutpat morbi non libero, venenatis porttitor, "
    "eget metus orci mauris velit, eros torquent sem libero amet aliquam. "
    "Laoreet nec, sed etiam suspendisse lorem habitasse suspendisse, "
    "purus ultrices risus, consequat justo justo risus massa mauris. Neque in "
    "elit sed sed vestibulum sit, sodales dui, curabitur orci, "
    "accumsan est, fames deserunt vestibulum libero urna. Sit praesent donec "
    "amet, lacinia mauris neque vitae integer donec tincidunt, "
    "lectus in turpis";

constexpr static std::array<uint8_t, 4> t_small = {{0xDE, 0xAD, 0xBE, 0xEF}};

static std::map<std::string, unsigned long> l_map_4 = {
    {"crc32_default_t", 0x7C9CA35A},
    {"bzip2_t", 0x7E25E5E7},
    {"crc32c_t", 0xF1DC778E},
    {"crc32d_t", 0xD325B831},
    {"mpeg2_t", 0x81DA1A18},
    {"posix_t", 0xB921389C},
    {"crc32q_t", 0xA5932B47},
    {"jamcrc_t", 0x83635CA5},
    {"xfer_t", 0x6F455145},
    {"ccitt_t", 0x4097},
    {"arc_t", 0xE59B},
    {"aug_ccitt_t", 0xCA47},
    {"buypass_t", 0x962B},
    {"cdma2000_16_t", 0xAEB8},
    {"dds_110_t", 0x96F3},
    {"dect_r_t", 0x303B},
    {"dect_x_t", 0x303A},
    {"dnp_t", 0x60B8},
    {"en_13757_t", 0x27E4},
    {"genibus_t", 0xBF68},
    {"maxim16_t", 0x1A64},
    {"mcrf4xx_t", 0x1A34},
    {"riello_t", 0x3E73},
    {"t10_dif_t", 0x34DC},
    {"teledisk_t", 0x520D},
    {"tms37157_t", 0xE1CA},
    {"usb_t", 0x3E64},
    {"crc16a_t", 0x4F15},
    {"kermit_t", 0x1915},
    {"modbus_t", 0xC19B},
    {"x_25_t", 0xE5CB},
    {"xmodem_t", 0xC457},
    {"default8_t", 0xCA},
    {"cdma2000_8_t", 0x77},
    {"darc_t", 0xC0},
    {"dvb_s2_t", 0xA5},
    {"ebu_t", 0x64},
    {"i_code_t", 0x6B},
    {"itu_t", 0x9F},
    {"maxim8_t", 0x84},
    {"rohc_t", 0xC3},
    {"wcdma_t", 0xCC}};

static std::map<std::string, unsigned long> l_map_string = {
    {"crc32_default_t", 0x2823594B},
    {"bzip2_t", 0xE070F5AA},
    {"crc32c_t", 0x01351862},
    {"crc32d_t", 0xE9C6D108},
    {"mpeg2_t", 0x1F8F0A55},
    {"posix_t", 0xD8CAFB43},
    {"crc32q_t", 0x6E39BBB6},
    {"jamcrc_t", 0xD7DCA6B4},
    {"xfer_t", 0xA90C29CD},
    {"ccitt_t", 0xEC01},
    {"arc_t", 0x4A8A},
    {"aug_ccitt_t", 0x800D},
    {"buypass_t", 0xB5AB},
    {"cdma2000_16_t", 0x6104},
    {"dds_110_t", 0x2406},
    {"dect_r_t", 0x82C4},
    {"dect_x_t", 0x82C5},
    {"dnp_t", 0xE26F},
    {"en_13757_t", 0x9A81},
    {"genibus_t", 0x13FE},
    {"maxim16_t", 0xB575},
    {"mcrf4xx_t", 0x6693},
    {"riello_t", 0x0A5C},
    {"t10_dif_t", 0x7F03},
    {"teledisk_t", 0x4E4D},
    {"tms37157_t", 0x995F},
    {"usb_t", 0x476A},
    {"crc16a_t", 0xE7CC},
    {"kermit_t", 0x877B},
    {"modbus_t", 0xB895},
    {"x_25_t", 0x996C},
    {"xmodem_t", 0xFB86},
    {"default8_t", 0x8D},
    {"cdma2000_8_t", 0x87},
    {"darc_t", 0x15},
    {"dvb_s2_t", 0x9F},
    {"ebu_t", 0xAB},
    {"i_code_t", 0xB0},
    {"itu_t", 0xD8},
    {"maxim8_t", 0x9F},
    {"rohc_t", 0xF6},
    {"wcdma_t", 0x3A}};

#define TEST_HELPER(type, data, expected)                                      \
  do {                                                                         \
    REQUIRE(type::checksum(data) == expected[#type]);                          \
  } while (0)

#define GROUP_TEST_HELPER(data, expected)                                      \
  do {                                                                         \
    TEST_HELPER(crc32_default_t, data, expected);                              \
    TEST_HELPER(bzip2_t, data, expected);                                      \
    TEST_HELPER(crc32c_t, data, expected);                                     \
    TEST_HELPER(crc32d_t, data, expected);                                     \
    TEST_HELPER(mpeg2_t, data, expected);                                      \
    TEST_HELPER(posix_t, data, expected);                                      \
    TEST_HELPER(crc32q_t, data, expected);                                     \
    TEST_HELPER(jamcrc_t, data, expected);                                     \
    TEST_HELPER(xfer_t, data, expected);                                       \
    TEST_HELPER(ccitt_t, data, expected);                                      \
    TEST_HELPER(arc_t, data, expected);                                        \
    TEST_HELPER(aug_ccitt_t, data, expected);                                  \
    TEST_HELPER(buypass_t, data, expected);                                    \
    TEST_HELPER(cdma2000_16_t, data, expected);                                \
    TEST_HELPER(dds_110_t, data, expected);                                    \
    TEST_HELPER(dect_r_t, data, expected);                                     \
    TEST_HELPER(dect_x_t, data, expected);                                     \
    TEST_HELPER(dnp_t, data, expected);                                        \
    TEST_HELPER(en_13757_t, data, expected);                                   \
    TEST_HELPER(genibus_t, data, expected);                                    \
    TEST_HELPER(maxim16_t, data, expected);                                    \
    TEST_HELPER(mcrf4xx_t, data, expected);                                    \
    TEST_HELPER(riello_t, data, expected);                                     \
    TEST_HELPER(t10_dif_t, data, expected);                                    \
    TEST_HELPER(teledisk_t, data, expected);                                   \
    TEST_HELPER(tms37157_t, data, expected);                                   \
    TEST_HELPER(usb_t, data, expected);                                        \
    TEST_HELPER(crc16a_t, data, expected);                                     \
    TEST_HELPER(kermit_t, data, expected);                                     \
    TEST_HELPER(modbus_t, data, expected);                                     \
    TEST_HELPER(x_25_t, data, expected);                                       \
    TEST_HELPER(xmodem_t, data, expected);                                     \
    TEST_HELPER(default8_t, data, expected);                                   \
    TEST_HELPER(cdma2000_8_t, data, expected);                                 \
    TEST_HELPER(darc_t, data, expected);                                       \
    TEST_HELPER(dvb_s2_t, data, expected);                                     \
    TEST_HELPER(ebu_t, data, expected);                                        \
    TEST_HELPER(i_code_t, data, expected);                                     \
    TEST_HELPER(itu_t, data, expected);                                        \
    TEST_HELPER(maxim8_t, data, expected);                                     \
    TEST_HELPER(rohc_t, data, expected);                                       \
    TEST_HELPER(wcdma_t, data, expected);                                      \
  } while (0)

TEST_CASE("Testing CRC with LUT", "[fast]") {

  SECTION("CRC32 - bigger data set") {
    GROUP_TEST_HELPER(l_lorem_psum, l_map_string);
  }

  SECTION("CRC32 - small data set") { GROUP_TEST_HELPER(t_small, l_map_4); }
}
