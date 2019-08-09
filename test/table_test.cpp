/*
 * @Author: lu
 * @Date:   10-01-2018
 * @Last Modified by:   Lukasz
 * @Last Modified time: 05-12-2018
 */

#include <array>
#include <map>

#include "crc/crc_lut.h"

#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this
                          // in one cpp file
#include <catch2/catch.hpp>

using namespace ccrc;

constexpr static std::array<uint16_t, 0x100> crc_lut_check = {
    {0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7, 0x8108,
     0x9129, 0xA14A, 0xB16B, 0xC18C, 0xD1AD, 0xE1CE, 0xF1EF, 0x1231, 0x0210,
     0x3273, 0x2252, 0x52B5, 0x4294, 0x72F7, 0x62D6, 0x9339, 0x8318, 0xB37B,
     0xA35A, 0xD3BD, 0xC39C, 0xF3FF, 0xE3DE, 0x2462, 0x3443, 0x0420, 0x1401,
     0x64E6, 0x74C7, 0x44A4, 0x5485, 0xA56A, 0xB54B, 0x8528, 0x9509, 0xE5EE,
     0xF5CF, 0xC5AC, 0xD58D, 0x3653, 0x2672, 0x1611, 0x0630, 0x76D7, 0x66F6,
     0x5695, 0x46B4, 0xB75B, 0xA77A, 0x9719, 0x8738, 0xF7DF, 0xE7FE, 0xD79D,
     0xC7BC, 0x48C4, 0x58E5, 0x6886, 0x78A7, 0x0840, 0x1861, 0x2802, 0x3823,
     0xC9CC, 0xD9ED, 0xE98E, 0xF9AF, 0x8948, 0x9969, 0xA90A, 0xB92B, 0x5AF5,
     0x4AD4, 0x7AB7, 0x6A96, 0x1A71, 0x0A50, 0x3A33, 0x2A12, 0xDBFD, 0xCBDC,
     0xFBBF, 0xEB9E, 0x9B79, 0x8B58, 0xBB3B, 0xAB1A, 0x6CA6, 0x7C87, 0x4CE4,
     0x5CC5, 0x2C22, 0x3C03, 0x0C60, 0x1C41, 0xEDAE, 0xFD8F, 0xCDEC, 0xDDCD,
     0xAD2A, 0xBD0B, 0x8D68, 0x9D49, 0x7E97, 0x6EB6, 0x5ED5, 0x4EF4, 0x3E13,
     0x2E32, 0x1E51, 0x0E70, 0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC, 0xBF1B, 0xAF3A,
     0x9F59, 0x8F78, 0x9188, 0x81A9, 0xB1CA, 0xA1EB, 0xD10C, 0xC12D, 0xF14E,
     0xE16F, 0x1080, 0x00A1, 0x30C2, 0x20E3, 0x5004, 0x4025, 0x7046, 0x6067,
     0x83B9, 0x9398, 0xA3FB, 0xB3DA, 0xC33D, 0xD31C, 0xE37F, 0xF35E, 0x02B1,
     0x1290, 0x22F3, 0x32D2, 0x4235, 0x5214, 0x6277, 0x7256, 0xB5EA, 0xA5CB,
     0x95A8, 0x8589, 0xF56E, 0xE54F, 0xD52C, 0xC50D, 0x34E2, 0x24C3, 0x14A0,
     0x0481, 0x7466, 0x6447, 0x5424, 0x4405, 0xA7DB, 0xB7FA, 0x8799, 0x97B8,
     0xE75F, 0xF77E, 0xC71D, 0xD73C, 0x26D3, 0x36F2, 0x0691, 0x16B0, 0x6657,
     0x7676, 0x4615, 0x5634, 0xD94C, 0xC96D, 0xF90E, 0xE92F, 0x99C8, 0x89E9,
     0xB98A, 0xA9AB, 0x5844, 0x4865, 0x7806, 0x6827, 0x18C0, 0x08E1, 0x3882,
     0x28A3, 0xCB7D, 0xDB5C, 0xEB3F, 0xFB1E, 0x8BF9, 0x9BD8, 0xABBB, 0xBB9A,
     0x4A75, 0x5A54, 0x6A37, 0x7A16, 0x0AF1, 0x1AD0, 0x2AB3, 0x3A92, 0xFD2E,
     0xED0F, 0xDD6C, 0xCD4D, 0xBDAA, 0xAD8B, 0x9DE8, 0x8DC9, 0x7C26, 0x6C07,
     0x5C64, 0x4C45, 0x3CA2, 0x2C83, 0x1CE0, 0x0CC1, 0xEF1F, 0xFF3E, 0xCF5D,
     0xDF7C, 0xAF9B, 0xBFBA, 0x8FD9, 0x9FF8, 0x6E17, 0x7E36, 0x4E55, 0x5E74,
     0x2E93, 0x3EB2, 0x0ED1, 0x1EF0}};

constexpr static LUT<uint16_t> g_lut(0x1021);

TEST_CASE("Compile Time Tests") {
  static_assert(g_lut[107] == crc_lut_check[107], "Table[107] Check");
  static_assert(g_lut[107] == crc_lut_check[107], "Table[107] Check");
  static_assert(g_lut[112] == crc_lut_check[112], "Table[112] Check");
  static_assert(g_lut[126] == crc_lut_check[126], "Table[126] Check");
  static_assert(g_lut[129] == crc_lut_check[129], "Table[129] Check");
  static_assert(g_lut[131] == crc_lut_check[131], "Table[131] Check");
  static_assert(g_lut[136] == crc_lut_check[136], "Table[136] Check");
  static_assert(g_lut[139] == crc_lut_check[139], "Table[139] Check");
  static_assert(g_lut[140] == crc_lut_check[140], "Table[140] Check");
  static_assert(g_lut[141] == crc_lut_check[141], "Table[141] Check");
  static_assert(g_lut[144] == crc_lut_check[144], "Table[144] Check");
  static_assert(g_lut[156] == crc_lut_check[156], "Table[156] Check");
  static_assert(g_lut[161] == crc_lut_check[161], "Table[161] Check");
  static_assert(g_lut[162] == crc_lut_check[162], "Table[162] Check");
  static_assert(g_lut[164] == crc_lut_check[164], "Table[164] Check");
  static_assert(g_lut[16] == crc_lut_check[16], "Table[16] Check");
  static_assert(g_lut[183] == crc_lut_check[183], "Table[183] Check");
  static_assert(g_lut[211] == crc_lut_check[211], "Table[211] Check");
  static_assert(g_lut[215] == crc_lut_check[215], "Table[215] Check");
  static_assert(g_lut[217] == crc_lut_check[217], "Table[217] Check");
  static_assert(g_lut[222] == crc_lut_check[222], "Table[222] Check");
  static_assert(g_lut[225] == crc_lut_check[225], "Table[225] Check");
  static_assert(g_lut[230] == crc_lut_check[230], "Table[230] Check");
  static_assert(g_lut[238] == crc_lut_check[238], "Table[238] Check");
  static_assert(g_lut[23] == crc_lut_check[23], "Table[23] Check");
  static_assert(g_lut[243] == crc_lut_check[243], "Table[243] Check");
  static_assert(g_lut[248] == crc_lut_check[248], "Table[248] Check");
  static_assert(g_lut[32] == crc_lut_check[32], "Table[32] Check");
  static_assert(g_lut[35] == crc_lut_check[35], "Table[35] Check");
  static_assert(g_lut[45] == crc_lut_check[45], "Table[45] Check");
  static_assert(g_lut[4] == crc_lut_check[4], "Table[4] Check");
  static_assert(g_lut[53] == crc_lut_check[53], "Table[53] Check");
  static_assert(g_lut[56] == crc_lut_check[56], "Table[56] Check");
  static_assert(g_lut[57] == crc_lut_check[57], "Table[57] Check");
  static_assert(g_lut[58] == crc_lut_check[58], "Table[58] Check");
  static_assert(g_lut[66] == crc_lut_check[66], "Table[66] Check");
  static_assert(g_lut[68] == crc_lut_check[68], "Table[68] Check");
  static_assert(g_lut[69] == crc_lut_check[69], "Table[69] Check");
  static_assert(g_lut[80] == crc_lut_check[80], "Table[80] Check");
  static_assert(g_lut[89] == crc_lut_check[89], "Table[89] Check");
  static_assert(g_lut[90] == crc_lut_check[90], "Table[90] Check");
  static_assert(g_lut[96] == crc_lut_check[96], "Table[96] Check");
  static_assert(g_lut[99] == crc_lut_check[99], "Table[99] Check");
  static_assert(g_lut[9] == crc_lut_check[9], "Table[9] Check");
  static_assert(g_lut[9] == crc_lut_check[9], "Table[9] Check");
}

TEST_CASE("Run Time Tests") {
  for (size_t i = 0; i < 0x100; ++i) {
    REQUIRE(g_lut[i] == crc_lut_check[i]);
  }
}
