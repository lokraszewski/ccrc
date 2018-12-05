/*
 * @Author: lu
 * @Date:   10-01-2018
 * @Last Modified by:   Lukasz
 * @Last Modified time: 05-12-2018
 */

#include <array>
#include <iostream>
#include <map>
#include <stdint.h>
#include <string>

#include "crc/alias.h"
#include "crc/bitop.h"
#include "crc/crc.h"

#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>

const static std::string l_lorem_psum =
    "Lorem ipsum dolor sit amet, condimentum id, quia ut enim. Congue lacus justo et egestas lacus purus, nam molestie et dictumst "
    "praesent, porta placerat sodales magnis mi rerum, per justo pede orci in vitae, mauris in. Elit aliquet ac et sit suspendisse tortor, "
    "malesuada arcu imperdiet varius est maecenas nunc, aliquam leo, ac diam. Interdum volutpat morbi non libero, venenatis porttitor, "
    "eget metus orci mauris velit, eros torquent sem libero amet aliquam. Laoreet nec, sed etiam suspendisse lorem habitasse suspendisse, "
    "purus ultrices risus, consequat justo justo risus massa mauris. Neque in elit sed sed vestibulum sit, sodales dui, curabitur orci, "
    "accumsan est, fames deserunt vestibulum libero urna. Sit praesent donec amet, lacinia mauris neque vitae integer donec tincidunt, "
    "lectus in turpis";

const static uint8_t l_byte_raw_array_4[] = {0xDE, 0xAD, 0xBE, 0xEF};

static std::map<std::string, unsigned long> l_map_4 = {{"CRC_32", 0x7C9CA35A},
                                                       {"CRC_32_BZIP2", 0x7E25E5E7},
                                                       {"CRC_32C", 0xF1DC778E},
                                                       {"CRC_32D", 0xD325B831},
                                                       {"CRC_32_MPEG_2", 0x81DA1A18},
                                                       {"CRC_32_POSIX", 0xB921389C},
                                                       {"CRC_32Q", 0xA5932B47},
                                                       {"CRC_32_JAMCRC", 0x83635CA5},
                                                       {"CRC_32_XFER", 0x6F455145},
                                                       {"CRC_16_CCITT_FALSE", 0x4097},
                                                       {"CRC_16_ARC", 0xE59B},
                                                       {"CRC_16_AUG_CCITT", 0xCA47},
                                                       {"CRC_16_BUYPASS", 0x962B},
                                                       {"CRC_16_CDMA2000", 0xAEB8},
                                                       {"CRC_16_DDS_110", 0x96F3},
                                                       {"CRC_16_DECT_R", 0x303B},
                                                       {"CRC_16_DECT_X", 0x303A},
                                                       {"CRC_16_DNP", 0x60B8},
                                                       {"CRC_16_EN_13757", 0x27E4},
                                                       {"CRC_16_GENIBUS", 0xBF68},
                                                       {"CRC_16_MAXIM", 0x1A64},
                                                       {"CRC_16_MCRF4XX", 0x1A34},
                                                       {"CRC_16_RIELLO", 0x3E73},
                                                       {"CRC_16_T10_DIF", 0x34DC},
                                                       {"CRC_16_TELEDISK", 0x520D},
                                                       {"CRC_16_TMS37157", 0xE1CA},
                                                       {"CRC_16_USB", 0x3E64},
                                                       {"CRC_A", 0x4F15},
                                                       {"CRC_16_KERMIT", 0x1915},
                                                       {"CRC_16_MODBUS", 0xC19B},
                                                       {"CRC_16_X_25", 0xE5CB},
                                                       {"CRC_16_XMODEM", 0xC457},
                                                       {"CRC_8", 0xCA},
                                                       {"CRC_8_CDMA2000", 0x77},
                                                       {"CRC_8_DARC", 0xC0},
                                                       {"CRC_8_DVB_S2", 0xA5},
                                                       {"CRC_8_EBU", 0x64},
                                                       {"CRC_8_I_CODE", 0x6B},
                                                       {"CRC_8_ITU", 0x9F},
                                                       {"CRC_8_MAXIM", 0x84},
                                                       {"CRC_8_ROHC", 0xC3},
                                                       {"CRC_8_WCDMA", 0xCC}};

static std::map<std::string, unsigned long> l_map_string = {{"CRC_32", 0x2823594B},
                                                            {"CRC_32_BZIP2", 0xE070F5AA},
                                                            {"CRC_32C", 0x01351862},
                                                            {"CRC_32D", 0xE9C6D108},
                                                            {"CRC_32_MPEG_2", 0x1F8F0A55},
                                                            {"CRC_32_POSIX", 0xD8CAFB43},
                                                            {"CRC_32Q", 0x6E39BBB6},
                                                            {"CRC_32_JAMCRC", 0xD7DCA6B4},
                                                            {"CRC_32_XFER", 0xA90C29CD},
                                                            {"CRC_16_CCITT_FALSE", 0xEC01},
                                                            {"CRC_16_ARC", 0x4A8A},
                                                            {"CRC_16_AUG_CCITT", 0x800D},
                                                            {"CRC_16_BUYPASS", 0xB5AB},
                                                            {"CRC_16_CDMA2000", 0x6104},
                                                            {"CRC_16_DDS_110", 0x2406},
                                                            {"CRC_16_DECT_R", 0x82C4},
                                                            {"CRC_16_DECT_X", 0x82C5},
                                                            {"CRC_16_DNP", 0xE26F},
                                                            {"CRC_16_EN_13757", 0x9A81},
                                                            {"CRC_16_GENIBUS", 0x13FE},
                                                            {"CRC_16_MAXIM", 0xB575},
                                                            {"CRC_16_MCRF4XX", 0x6693},
                                                            {"CRC_16_RIELLO", 0x0A5C},
                                                            {"CRC_16_T10_DIF", 0x7F03},
                                                            {"CRC_16_TELEDISK", 0x4E4D},
                                                            {"CRC_16_TMS37157", 0x995F},
                                                            {"CRC_16_USB", 0x476A},
                                                            {"CRC_A", 0xE7CC},
                                                            {"CRC_16_KERMIT", 0x877B},
                                                            {"CRC_16_MODBUS", 0xB895},
                                                            {"CRC_16_X_25", 0x996C},
                                                            {"CRC_16_XMODEM", 0xFB86},
                                                            {"CRC_8", 0x8D},
                                                            {"CRC_8_CDMA2000", 0x87},
                                                            {"CRC_8_DARC", 0x15},
                                                            {"CRC_8_DVB_S2", 0x9F},
                                                            {"CRC_8_EBU", 0xAB},
                                                            {"CRC_8_I_CODE", 0xB0},
                                                            {"CRC_8_ITU", 0xD8},
                                                            {"CRC_8_MAXIM", 0x9F},
                                                            {"CRC_8_ROHC", 0xF6},
                                                            {"CRC_8_WCDMA", 0x3A}};

TEST_CASE("bitop::reverse works correctly. ", "[bitop]")
{

  SECTION("8 bit")
  {
    REQUIRE(bitop::reverse<uint8_t>(0xFF) == 0xFF);
    REQUIRE(bitop::reverse<uint8_t>(0x00) == 0x00);
    REQUIRE(bitop::reverse<uint8_t>(0x0F) == 0xF0);
    REQUIRE(bitop::reverse<uint8_t>(0x01) == 0x80);
    REQUIRE(bitop::reverse<uint8_t>(0x80) == 0x01);
    REQUIRE(bitop::reverse<uint8_t>(0xAA) == 0x55);
    REQUIRE(bitop::reverse<uint8_t>(0x55) == 0xAA);
  }

  SECTION("16 bit")
  {
    REQUIRE(bitop::reverse<uint16_t>(0xFFFF) == 0xFFFF);
    REQUIRE(bitop::reverse<uint16_t>(0x0000) == 0x0000);
    REQUIRE(bitop::reverse<uint16_t>(0x000F) == 0xF000);
    REQUIRE(bitop::reverse<uint16_t>(0x0001) == 0x8000);
    REQUIRE(bitop::reverse<uint16_t>(0xAAAA) == 0x5555);
    REQUIRE(bitop::reverse<uint16_t>(0x5555) == 0xAAAA);
  }

  SECTION("32 bit")
  {
    REQUIRE(bitop::reverse<uint32_t>(0xFFFFFFFF) == 0xFFFFFFFF);
    REQUIRE(bitop::reverse<uint32_t>(0x0000000F) == 0xF0000000);
    REQUIRE(bitop::reverse<uint32_t>(0x00000001) == 0x80000000);
    REQUIRE(bitop::reverse<uint32_t>(0x80000000) == 0x00000001);
    REQUIRE(bitop::reverse<uint32_t>(0x00000000) == 0x00000000);
    REQUIRE(bitop::reverse<uint32_t>(0xAAAAAAAA) == 0x55555555);
    REQUIRE(bitop::reverse<uint32_t>(0x55555555) == 0xAAAAAAAA);
  }
}

TEST_CASE("CRC Constructors", "[crc16-ctroes]")
{
  SECTION("Default")
  {
    crc_basic<uint16_t, 0x1021> l_c16;
    REQUIRE(l_c16.checksum() == 0xFFFF);
    REQUIRE(l_c16.get_poly() == 0x1021);
    REQUIRE(l_c16.get_seed() == 0xFFFF);
  }

  SECTION("CRC-16/CCITT-FALSE ")
  {
    crc_basic<uint16_t, 0x1021, 0xFFFF, 0x0000, false, false> l_c16;
    REQUIRE(l_c16.checksum() == 0xFFFF);
  }
}

TEST_CASE("All methods yeild same result", "")
{
  crc_basic<uint16_t, 0x1021> l_c16;
  const uint8_t               data[] = {0xDE, 0xAD, 0xBE, 0xEF};

  SECTION("Block") { REQUIRE(l_c16.process_block(data, data + 4) == 0x4097); }
  SECTION("Block") { REQUIRE(l_c16.process_bytes(data, 4) == 0x4097); }
  SECTION("Byte")
  {
    for (auto i = 0; i < 4; i++) l_c16.process_byte(data[i]);
    REQUIRE(l_c16.checksum() == 0x4097);
  }
}
TEST_CASE("Reseting works", "")
{
  crc_basic<uint16_t, 0x1021> l_c16;
  const uint8_t               data[] = {0xDE, 0xAD, 0xBE, 0xEF};
  REQUIRE(l_c16.process_block(data, data + 4) == 0x4097);
  l_c16.reset();
  REQUIRE(l_c16.checksum() == 0xFFFF);
  l_c16.reset(0xAABB);
  REQUIRE(l_c16.checksum() == 0xAABB);
}

TEST_CASE("Small data sets using basic computation", "[small]")
{
  using namespace crc::basic;
  SECTION("CRC_32")
  {

    default32_t crc;
    REQUIRE(crc.process_bytes(l_byte_raw_array_4, 4) == l_map_4["CRC_32"]);
  }
  SECTION("CRC_32_BZIP2")
  {
    bzip2_t crc;
    REQUIRE(crc.process_bytes(l_byte_raw_array_4, 4) == l_map_4["CRC_32_BZIP2"]);
  }
  SECTION("CRC_32C")
  {
    crc32c_t crc;
    REQUIRE(crc.process_bytes(l_byte_raw_array_4, 4) == l_map_4["CRC_32C"]);
  }
  SECTION("CRC_32D")
  {
    crc32d_t crc;
    REQUIRE(crc.process_bytes(l_byte_raw_array_4, 4) == l_map_4["CRC_32D"]);
  }
  SECTION("CRC_32_MPEG_2")
  {
    mpeg2_t crc;
    REQUIRE(crc.process_bytes(l_byte_raw_array_4, 4) == l_map_4["CRC_32_MPEG_2"]);
  }
  SECTION("CRC_32_POSIX")
  {
    posix_t crc;
    REQUIRE(crc.process_bytes(l_byte_raw_array_4, 4) == l_map_4["CRC_32_POSIX"]);
  }
  SECTION("CRC_32Q")
  {
    crc32q_t crc;
    REQUIRE(crc.process_bytes(l_byte_raw_array_4, 4) == l_map_4["CRC_32Q"]);
  }
  SECTION("CRC_32_JAMCRC")
  {
    jamcrc_t crc;
    REQUIRE(crc.process_bytes(l_byte_raw_array_4, 4) == l_map_4["CRC_32_JAMCRC"]);
  }
  SECTION("CRC_32_XFER")
  {
    xfer_t crc;
    REQUIRE(crc.process_bytes(l_byte_raw_array_4, 4) == l_map_4["CRC_32_XFER"]);
  }
  SECTION("CRC_16_CCITT_FALSE")
  {
    ccitt_t crc;
    REQUIRE(crc.process_bytes(l_byte_raw_array_4, 4) == l_map_4["CRC_16_CCITT_FALSE"]);
  }
  SECTION("CRC_16_ARC")
  {
    arc_t crc;
    REQUIRE(crc.process_bytes(l_byte_raw_array_4, 4) == l_map_4["CRC_16_ARC"]);
  }
  SECTION("CRC_16_AUG_CCITT")
  {
    aug_ccitt_t crc;
    REQUIRE(crc.process_bytes(l_byte_raw_array_4, 4) == l_map_4["CRC_16_AUG_CCITT"]);
  }
  SECTION("CRC_16_BUYPASS")
  {
    buypass_t crc;
    REQUIRE(crc.process_bytes(l_byte_raw_array_4, 4) == l_map_4["CRC_16_BUYPASS"]);
  }
  SECTION("CRC_16_CDMA2000")
  {
    cdma2000_16_t crc;
    REQUIRE(crc.process_bytes(l_byte_raw_array_4, 4) == l_map_4["CRC_16_CDMA2000"]);
  }
  SECTION("CRC_16_DDS_110")
  {
    dds_110_t crc;
    REQUIRE(crc.process_bytes(l_byte_raw_array_4, 4) == l_map_4["CRC_16_DDS_110"]);
  }
  SECTION("CRC_16_DECT_R")
  {
    dect_r_t crc;
    REQUIRE(crc.process_bytes(l_byte_raw_array_4, 4) == l_map_4["CRC_16_DECT_R"]);
  }
  SECTION("CRC_16_DECT_X")
  {
    dect_x_t crc;
    REQUIRE(crc.process_bytes(l_byte_raw_array_4, 4) == l_map_4["CRC_16_DECT_X"]);
  }
  SECTION("CRC_16_DNP")
  {
    dnp_t crc;
    REQUIRE(crc.process_bytes(l_byte_raw_array_4, 4) == l_map_4["CRC_16_DNP"]);
  }
  SECTION("CRC_16_EN_13757")
  {
    en_13757_t crc;
    REQUIRE(crc.process_bytes(l_byte_raw_array_4, 4) == l_map_4["CRC_16_EN_13757"]);
  }
  SECTION("CRC_16_GENIBUS")
  {
    genibus_t crc;
    REQUIRE(crc.process_bytes(l_byte_raw_array_4, 4) == l_map_4["CRC_16_GENIBUS"]);
  }
  SECTION("CRC_16_MAXIM")
  {
    maxim16_t crc;
    REQUIRE(crc.process_bytes(l_byte_raw_array_4, 4) == l_map_4["CRC_16_MAXIM"]);
  }
  SECTION("CRC_16_MCRF4XX")
  {
    mcrf4xx_t crc;
    REQUIRE(crc.process_bytes(l_byte_raw_array_4, 4) == l_map_4["CRC_16_MCRF4XX"]);
  }
  SECTION("CRC_16_RIELLO")
  {
    riello_t crc;
    REQUIRE(crc.process_bytes(l_byte_raw_array_4, 4) == l_map_4["CRC_16_RIELLO"]);
  }
  SECTION("CRC_16_T10_DIF")
  {
    t10_dif_t crc;
    REQUIRE(crc.process_bytes(l_byte_raw_array_4, 4) == l_map_4["CRC_16_T10_DIF"]);
  }
  SECTION("CRC_16_TELEDISK")
  {
    teledisk_t crc;
    REQUIRE(crc.process_bytes(l_byte_raw_array_4, 4) == l_map_4["CRC_16_TELEDISK"]);
  }
  SECTION("CRC_16_TMS37157")
  {
    tms37157_t crc;
    REQUIRE(crc.process_bytes(l_byte_raw_array_4, 4) == l_map_4["CRC_16_TMS37157"]);
  }
  SECTION("CRC_16_USB")
  {
    usb_t crc;
    REQUIRE(crc.process_bytes(l_byte_raw_array_4, 4) == l_map_4["CRC_16_USB"]);
  }
  SECTION("CRC_A")
  {
    crc16a_t crc;
    REQUIRE(crc.process_bytes(l_byte_raw_array_4, 4) == l_map_4["CRC_A"]);
  }
  SECTION("CRC_16_KERMIT")
  {
    kermit_t crc;
    REQUIRE(crc.process_bytes(l_byte_raw_array_4, 4) == l_map_4["CRC_16_KERMIT"]);
  }
  SECTION("CRC_16_MODBUS")
  {
    modbus_t crc;
    REQUIRE(crc.process_bytes(l_byte_raw_array_4, 4) == l_map_4["CRC_16_MODBUS"]);
  }
  SECTION("CRC_16_X_25")
  {
    x_25_t crc;
    REQUIRE(crc.process_bytes(l_byte_raw_array_4, 4) == l_map_4["CRC_16_X_25"]);
  }
  SECTION("CRC_16_XMODEM")
  {
    xmodem_t crc;
    REQUIRE(crc.process_bytes(l_byte_raw_array_4, 4) == l_map_4["CRC_16_XMODEM"]);
  }
  SECTION("CRC_8")
  {
    default8_t crc;
    REQUIRE(crc.process_bytes(l_byte_raw_array_4, 4) == l_map_4["CRC_8"]);
  }
  SECTION("CRC_8_CDMA2000")
  {
    cdma2000_8_t crc;
    REQUIRE(crc.process_bytes(l_byte_raw_array_4, 4) == l_map_4["CRC_8_CDMA2000"]);
  }
  SECTION("CRC_8_DARC")
  {
    darc_t crc;
    REQUIRE(crc.process_bytes(l_byte_raw_array_4, 4) == l_map_4["CRC_8_DARC"]);
  }
  SECTION("CRC_8_DVB_S2")
  {
    dvb_s2_t crc;
    REQUIRE(crc.process_bytes(l_byte_raw_array_4, 4) == l_map_4["CRC_8_DVB_S2"]);
  }
  SECTION("CRC_8_EBU")
  {
    ebu_t crc;
    REQUIRE(crc.process_bytes(l_byte_raw_array_4, 4) == l_map_4["CRC_8_EBU"]);
  }
  SECTION("CRC_8_I_CODE")
  {
    i_code_t crc;
    REQUIRE(crc.process_bytes(l_byte_raw_array_4, 4) == l_map_4["CRC_8_I_CODE"]);
  }
  SECTION("CRC_8_ITU")
  {
    itu_t crc;
    REQUIRE(crc.process_bytes(l_byte_raw_array_4, 4) == l_map_4["CRC_8_ITU"]);
  }
  SECTION("CRC_8_MAXIM")
  {
    maxim8_t crc;
    REQUIRE(crc.process_bytes(l_byte_raw_array_4, 4) == l_map_4["CRC_8_MAXIM"]);
  }
  SECTION("CRC_8_ROHC")
  {
    rohc_t crc;
    REQUIRE(crc.process_bytes(l_byte_raw_array_4, 4) == l_map_4["CRC_8_ROHC"]);
  }
  SECTION("CRC_8_WCDMA")
  {
    wcdma_t crc;
    REQUIRE(crc.process_bytes(l_byte_raw_array_4, 4) == l_map_4["CRC_8_WCDMA"]);
  }
}

TEST_CASE("String data sets using basic computation", "[string]")
{
  using namespace crc::basic;
  SECTION("CRC_32")
  {
    default32_t crc;
    REQUIRE(crc.process_bytes(l_lorem_psum.c_str(), l_lorem_psum.size()) == l_map_string["CRC_32"]);
  }
  SECTION("CRC_32_BZIP2")
  {
    bzip2_t crc;
    REQUIRE(crc.process_bytes(l_lorem_psum.c_str(), l_lorem_psum.size()) == l_map_string["CRC_32_BZIP2"]);
  }
  SECTION("CRC_32C")
  {
    crc32c_t crc;
    REQUIRE(crc.process_bytes(l_lorem_psum.c_str(), l_lorem_psum.size()) == l_map_string["CRC_32C"]);
  }
  SECTION("CRC_32D")
  {
    crc32d_t crc;
    REQUIRE(crc.process_bytes(l_lorem_psum.c_str(), l_lorem_psum.size()) == l_map_string["CRC_32D"]);
  }
  SECTION("CRC_32_MPEG_2")
  {
    mpeg2_t crc;
    REQUIRE(crc.process_bytes(l_lorem_psum.c_str(), l_lorem_psum.size()) == l_map_string["CRC_32_MPEG_2"]);
  }
  SECTION("CRC_32_POSIX")
  {
    posix_t crc;
    REQUIRE(crc.process_bytes(l_lorem_psum.c_str(), l_lorem_psum.size()) == l_map_string["CRC_32_POSIX"]);
  }
  SECTION("CRC_32Q")
  {
    crc32q_t crc;
    REQUIRE(crc.process_bytes(l_lorem_psum.c_str(), l_lorem_psum.size()) == l_map_string["CRC_32Q"]);
  }
  SECTION("CRC_32_JAMCRC")
  {
    jamcrc_t crc;
    REQUIRE(crc.process_bytes(l_lorem_psum.c_str(), l_lorem_psum.size()) == l_map_string["CRC_32_JAMCRC"]);
  }
  SECTION("CRC_32_XFER")
  {
    xfer_t crc;
    REQUIRE(crc.process_bytes(l_lorem_psum.c_str(), l_lorem_psum.size()) == l_map_string["CRC_32_XFER"]);
  }
  SECTION("CRC_16_CCITT_FALSE")
  {
    ccitt_t crc;
    REQUIRE(crc.process_bytes(l_lorem_psum.c_str(), l_lorem_psum.size()) == l_map_string["CRC_16_CCITT_FALSE"]);
  }
  SECTION("CRC_16_ARC")
  {
    arc_t crc;
    REQUIRE(crc.process_bytes(l_lorem_psum.c_str(), l_lorem_psum.size()) == l_map_string["CRC_16_ARC"]);
  }
  SECTION("CRC_16_AUG_CCITT")
  {
    aug_ccitt_t crc;
    REQUIRE(crc.process_bytes(l_lorem_psum.c_str(), l_lorem_psum.size()) == l_map_string["CRC_16_AUG_CCITT"]);
  }
  SECTION("CRC_16_BUYPASS")
  {
    buypass_t crc;
    REQUIRE(crc.process_bytes(l_lorem_psum.c_str(), l_lorem_psum.size()) == l_map_string["CRC_16_BUYPASS"]);
  }
  SECTION("CRC_16_CDMA2000")
  {
    cdma2000_16_t crc;
    REQUIRE(crc.process_bytes(l_lorem_psum.c_str(), l_lorem_psum.size()) == l_map_string["CRC_16_CDMA2000"]);
  }
  SECTION("CRC_16_DDS_110")
  {
    dds_110_t crc;
    REQUIRE(crc.process_bytes(l_lorem_psum.c_str(), l_lorem_psum.size()) == l_map_string["CRC_16_DDS_110"]);
  }
  SECTION("CRC_16_DECT_R")
  {
    dect_r_t crc;
    REQUIRE(crc.process_bytes(l_lorem_psum.c_str(), l_lorem_psum.size()) == l_map_string["CRC_16_DECT_R"]);
  }
  SECTION("CRC_16_DECT_X")
  {
    dect_x_t crc;
    REQUIRE(crc.process_bytes(l_lorem_psum.c_str(), l_lorem_psum.size()) == l_map_string["CRC_16_DECT_X"]);
  }
  SECTION("CRC_16_DNP")
  {
    dnp_t crc;
    REQUIRE(crc.process_bytes(l_lorem_psum.c_str(), l_lorem_psum.size()) == l_map_string["CRC_16_DNP"]);
  }
  SECTION("CRC_16_EN_13757")
  {
    en_13757_t crc;
    REQUIRE(crc.process_bytes(l_lorem_psum.c_str(), l_lorem_psum.size()) == l_map_string["CRC_16_EN_13757"]);
  }
  SECTION("CRC_16_GENIBUS")
  {
    genibus_t crc;
    REQUIRE(crc.process_bytes(l_lorem_psum.c_str(), l_lorem_psum.size()) == l_map_string["CRC_16_GENIBUS"]);
  }
  SECTION("CRC_16_MAXIM")
  {
    maxim16_t crc;
    REQUIRE(crc.process_bytes(l_lorem_psum.c_str(), l_lorem_psum.size()) == l_map_string["CRC_16_MAXIM"]);
  }
  SECTION("CRC_16_MCRF4XX")
  {
    mcrf4xx_t crc;
    REQUIRE(crc.process_bytes(l_lorem_psum.c_str(), l_lorem_psum.size()) == l_map_string["CRC_16_MCRF4XX"]);
  }
  SECTION("CRC_16_RIELLO")
  {
    riello_t crc;
    REQUIRE(crc.process_bytes(l_lorem_psum.c_str(), l_lorem_psum.size()) == l_map_string["CRC_16_RIELLO"]);
  }
  SECTION("CRC_16_T10_DIF")
  {
    t10_dif_t crc;
    REQUIRE(crc.process_bytes(l_lorem_psum.c_str(), l_lorem_psum.size()) == l_map_string["CRC_16_T10_DIF"]);
  }
  SECTION("CRC_16_TELEDISK")
  {
    teledisk_t crc;
    REQUIRE(crc.process_bytes(l_lorem_psum.c_str(), l_lorem_psum.size()) == l_map_string["CRC_16_TELEDISK"]);
  }
  SECTION("CRC_16_TMS37157")
  {
    tms37157_t crc;
    REQUIRE(crc.process_bytes(l_lorem_psum.c_str(), l_lorem_psum.size()) == l_map_string["CRC_16_TMS37157"]);
  }
  SECTION("CRC_16_USB")
  {
    usb_t crc;
    REQUIRE(crc.process_bytes(l_lorem_psum.c_str(), l_lorem_psum.size()) == l_map_string["CRC_16_USB"]);
  }
  SECTION("CRC_A")
  {
    crc16a_t crc;
    REQUIRE(crc.process_bytes(l_lorem_psum.c_str(), l_lorem_psum.size()) == l_map_string["CRC_A"]);
  }
  SECTION("CRC_16_KERMIT")
  {
    kermit_t crc;
    REQUIRE(crc.process_bytes(l_lorem_psum.c_str(), l_lorem_psum.size()) == l_map_string["CRC_16_KERMIT"]);
  }
  SECTION("CRC_16_MODBUS")
  {
    modbus_t crc;
    REQUIRE(crc.process_bytes(l_lorem_psum.c_str(), l_lorem_psum.size()) == l_map_string["CRC_16_MODBUS"]);
  }
  SECTION("CRC_16_X_25")
  {
    x_25_t crc;
    REQUIRE(crc.process_bytes(l_lorem_psum.c_str(), l_lorem_psum.size()) == l_map_string["CRC_16_X_25"]);
  }
  SECTION("CRC_16_XMODEM")
  {
    xmodem_t crc;
    REQUIRE(crc.process_bytes(l_lorem_psum.c_str(), l_lorem_psum.size()) == l_map_string["CRC_16_XMODEM"]);
  }
  SECTION("CRC_8")
  {
    default8_t crc;
    REQUIRE(crc.process_bytes(l_lorem_psum.c_str(), l_lorem_psum.size()) == l_map_string["CRC_8"]);
  }
  SECTION("CRC_8_CDMA2000")
  {
    cdma2000_8_t crc;
    REQUIRE(crc.process_bytes(l_lorem_psum.c_str(), l_lorem_psum.size()) == l_map_string["CRC_8_CDMA2000"]);
  }
  SECTION("CRC_8_DARC")
  {
    darc_t crc;
    REQUIRE(crc.process_bytes(l_lorem_psum.c_str(), l_lorem_psum.size()) == l_map_string["CRC_8_DARC"]);
  }
  SECTION("CRC_8_DVB_S2")
  {
    dvb_s2_t crc;
    REQUIRE(crc.process_bytes(l_lorem_psum.c_str(), l_lorem_psum.size()) == l_map_string["CRC_8_DVB_S2"]);
  }
  SECTION("CRC_8_EBU")
  {
    ebu_t crc;
    REQUIRE(crc.process_bytes(l_lorem_psum.c_str(), l_lorem_psum.size()) == l_map_string["CRC_8_EBU"]);
  }
  SECTION("CRC_8_I_CODE")
  {
    i_code_t crc;
    REQUIRE(crc.process_bytes(l_lorem_psum.c_str(), l_lorem_psum.size()) == l_map_string["CRC_8_I_CODE"]);
  }
  SECTION("CRC_8_ITU")
  {
    itu_t crc;
    REQUIRE(crc.process_bytes(l_lorem_psum.c_str(), l_lorem_psum.size()) == l_map_string["CRC_8_ITU"]);
  }
  SECTION("CRC_8_MAXIM")
  {
    maxim8_t crc;
    REQUIRE(crc.process_bytes(l_lorem_psum.c_str(), l_lorem_psum.size()) == l_map_string["CRC_8_MAXIM"]);
  }
  SECTION("CRC_8_ROHC")
  {
    rohc_t crc;
    REQUIRE(crc.process_bytes(l_lorem_psum.c_str(), l_lorem_psum.size()) == l_map_string["CRC_8_ROHC"]);
  }
  SECTION("CRC_8_WCDMA")
  {
    wcdma_t crc;
    REQUIRE(crc.process_bytes(l_lorem_psum.c_str(), l_lorem_psum.size()) == l_map_string["CRC_8_WCDMA"]);
  }
}
