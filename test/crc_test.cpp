/*
 * @Author: lu
 * @Date:   10-01-2018
 * @Last Modified by:   Lukasz
 * @Last Modified time: 05-12-2018
 */

#include <array>
#include <iostream>
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
    "lectus in turpis erat, quam et mauris ligula, amet sit eros venenatis. Tempus erat voluptatum parturient elit, ac condimentum "
    "fringilla natoque arcu, ad faucibus donec praesent mattis, commodo mi arcu magna id nisl vitae, sit potenti velit sit enim. Velit "
    "aliquam nunc sit nihil condimentum, ullamcorper mattis mauris tincidunt dictum ac mollis, taciti arcu suscipit fusce pellentesque "
    "tristique vel, convallis at sed dictumst gravida. Est convallis et sem cum. Felis duis sapien morbi scelerisque placerat, ad vel "
    "vitae deleniti sit. Sed sollicitudin, condimentum dui, eros suscipit bibendum ac eget. Donec conubia quis donec blandit laoreet, per "
    "tellus volutpat cras consectetuer, urna id eu feugiat sodales interdum tincidunt, ut suspendisse cursus. Sodales sint erat cras, "
    "purus ipsum sem bibendum tristique pretium nulla, arcu porttitor.  Maecenas vestibulum sit, aliquam dolor, erat purus elit vestibulum "
    "sed. Elit non duis. Diam leo sit dolorem. Eros in diam ut id diam, laoreet fringilla ante sit ut quis. Lacus mauris in donec sed. "
    "Enim neque nulla nec. Proin auctor est ullamcorper integer mauris quis, at erat lorem vitae fusce dignissim tempor, morbi odio velit "
    "eros ante. Lectus mus bibendum consequat, eros tincidunt, turpis rutrum non leo vitae quis, eu vestibulum accumsan, id dictumst. A "
    "vitae integer consequat eu non, accumsan velit pede in quis, quis velit fusce faucibus pharetra sem nec, non nibh ut in. Lacinia "
    "turpis sapien ante vitae convallis. Eu est felis cras eleifend a et, vestibulum sem et suspendisse vel, aliquam ac magna mauris "
    "malesuada praesent pellentesque, ligula est mus, tortor dictumst fermentum velit risus sodales. Nulla elit massa eleifend, eleifend "
    "vel aspernatur aenean, pede tellus dui. Integer quis velit ac, nibh leo tempor. Sodales non morbi in praesent, ipsum suspendisse "
    "mattis, bibendum consequat magna diam morbi, iaculis magna donec non tellus sed magna, massa sed vulputate posuere. In sagittis eu id "
    "lectus pede mi. Magna mus. Pellentesque suscipit, in amet libero consectetuer, tincidunt laboriosam, hymenaeos class mi in luctus "
    "dolor platea, tincidunt porta inceptos nibh sapien leo auctor.";

const static uint8_t l_byte_raw_array_4[] = {0xDE, 0xAD, 0xBE, 0xEF};

const static uint8_t l_byte_raw_array_512[] = {
    0x1d, 0xf7, 0x5f, 0xe3, 0xdf, 0x5b, 0xd1, 0x69, 0x86, 0xed, 0xb1, 0x27, 0xf4, 0x1b, 0x00, 0x2c, 0xd2, 0x3f, 0x74, 0xc8, 0xff, 0x42,
    0xb2, 0x69, 0x42, 0x09, 0xd3, 0x65, 0x14, 0x83, 0xac, 0xab, 0x80, 0x5a, 0x3b, 0x0e, 0xb5, 0xc1, 0x90, 0x20, 0x0f, 0x91, 0xa0, 0x8b,
    0x4c, 0xf5, 0xc8, 0xd6, 0xa5, 0x63, 0xe3, 0x35, 0x7f, 0x20, 0xaa, 0xc9, 0x4e, 0x49, 0x5a, 0x4d, 0xe7, 0x9e, 0xc1, 0xe1, 0x83, 0x81,
    0x00, 0xe2, 0xe1, 0xaa, 0xad, 0xdd, 0x29, 0xdb, 0x5f, 0x12, 0xbc, 0x7c, 0x83, 0xb2, 0x86, 0x53, 0x3c, 0x8a, 0x4d, 0x3c, 0xc9, 0xce,
    0x96, 0x0c, 0x93, 0xf7, 0xc7, 0x6b, 0x56, 0x7c, 0x9c, 0x64, 0xe4, 0x8b, 0x36, 0x80, 0x77, 0x9e, 0xc1, 0xd4, 0x55, 0xfa, 0xf4, 0x8a,
    0x50, 0x9f, 0xde, 0x2a, 0x40, 0x82, 0x6b, 0x4b, 0x7d, 0xfb, 0xb2, 0x47, 0xdd, 0xfb, 0x3f, 0x97, 0xc8, 0x40, 0x66, 0x1c, 0x4c, 0xe0,
    0x01, 0x45, 0x13, 0xa1, 0xfc, 0x62, 0xdf, 0x31, 0xbc, 0x1b, 0x52, 0x9f, 0xda, 0x78, 0x41, 0xae, 0xee, 0x2a, 0x2c, 0xd5, 0xab, 0x77,
    0x93, 0x23, 0xc7, 0xe0, 0x12, 0x25, 0xbc, 0x43, 0x4d, 0xab, 0x2a, 0x3b, 0xa3, 0xcb, 0xa3, 0x3b, 0x6e, 0x4b, 0x89, 0x50, 0x36, 0x01,
    0x63, 0x7c, 0x87, 0x06, 0x84, 0xbc, 0xbb, 0x98, 0xdb, 0x3c, 0x08, 0xbb, 0xed, 0xf6, 0x9f, 0x37, 0x12, 0xc9, 0xf5, 0xb6, 0x0c, 0x31,
    0x3f, 0x32, 0xab, 0xcd, 0xc0, 0xfc, 0x51, 0x71, 0x62, 0x9c, 0xa2, 0x94, 0xa7, 0x9b, 0x9f, 0x44, 0x2b, 0x31, 0x99, 0x17, 0x60, 0xff,
    0xd7, 0x10, 0x77, 0xae, 0x0a, 0x8f, 0xd6, 0x70, 0xc8, 0xea, 0x08, 0x36, 0xe6, 0x8e, 0x64, 0x1a, 0x36, 0x69, 0x13, 0xf0, 0x91, 0x75,
    0x1d, 0x73, 0xf9, 0x55, 0x92, 0x78, 0x96, 0xe6, 0xeb, 0x9a, 0x78, 0xbc, 0x4b, 0xd3, 0xab, 0x70, 0xf3, 0x12, 0x4a, 0xa9, 0x16, 0x77,
    0xe0, 0xa6, 0xdd, 0xcd, 0xac, 0xcf, 0xea, 0x4f, 0x10, 0x35, 0xf8, 0x75, 0x89, 0x15, 0xb7, 0xef, 0x8c, 0xf1, 0x8e, 0x75, 0xbf, 0xd0,
    0xf4, 0xf0, 0xd1, 0xb0, 0xf2, 0x0f, 0xb4, 0xae, 0x47, 0xcf, 0x83, 0x79, 0x57, 0x94, 0x02, 0x94, 0xa1, 0xc6, 0x6d, 0xea, 0x69, 0xa3,
    0x0e, 0x4f, 0x83, 0xa0, 0x2b, 0x7c, 0xe4, 0x84, 0xd4, 0xbf, 0x24, 0xa3, 0x5d, 0xbd, 0x76, 0x1c, 0xca, 0x42, 0xb7, 0xb1, 0xb3, 0x9c,
    0x3d, 0x3a, 0xc3, 0x0b, 0xf4, 0xe3, 0xed, 0x29, 0xe3, 0xb0, 0x15, 0xe7, 0xcd, 0xa2, 0x76, 0x5b, 0x79, 0x16, 0xb9, 0xd7, 0x26, 0xdb,
    0xa1, 0xb0, 0x10, 0x13, 0x66, 0xe1, 0xd2, 0xf8, 0x71, 0x5e, 0xe8, 0xac, 0x8b, 0xf4, 0x15, 0x3e, 0x2f, 0x9a, 0xd3, 0x70, 0x3c, 0xd6,
    0x93, 0x72, 0xd3, 0x46, 0xa9, 0x41, 0x3f, 0xf8, 0x47, 0x10, 0x4a, 0x6c, 0x36, 0x8f, 0x39, 0x8b, 0x8a, 0xe6, 0x4a, 0x05, 0xac, 0x2f,
    0xd0, 0xaa, 0x93, 0x5c, 0x98, 0x1b, 0x92, 0x19, 0x34, 0x55, 0x85, 0x6e, 0x0b, 0x1b, 0xd5, 0xf5, 0xec, 0x03, 0x95, 0x24, 0xda, 0xd3,
    0x94, 0xf9, 0x28, 0x5f, 0x6f, 0x27, 0x2f, 0xec, 0x91, 0xf6, 0xa0, 0x59, 0x44, 0xed, 0xfc, 0x1c, 0x83, 0x00, 0x60, 0xc8, 0xce, 0x57,
    0xcf, 0x85, 0xfc, 0x79, 0x01, 0x10, 0x8f, 0xee, 0x70, 0xb7, 0x63, 0xe0, 0xeb, 0xa2, 0xb9, 0x9c, 0x25, 0xf1, 0xf9, 0x2a, 0x95, 0xd6,
    0x9a, 0x71, 0xe4, 0x2a, 0x82, 0x4f, 0x6e, 0x4f, 0x82, 0xe5, 0x7c, 0xb8, 0x43, 0xa0, 0xdb, 0x6f, 0xab, 0x93, 0x2c, 0x21, 0xd2, 0x89,
    0x33, 0xcb, 0xc0, 0xc0, 0xbb, 0x3b, 0x54, 0x6d, 0x2b, 0x34, 0xc5, 0x89, 0x7d, 0x8c, 0x64, 0xe3, 0xf3, 0x84, 0xa6, 0x5f, 0x09, 0x6b,
    0xac, 0x3f, 0x38, 0x8e, 0x7d, 0xe9};

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

TEST_CASE("Basic 32 bit", "[basic-32]")
{

  SECTION("CRC-32")
  {
    crc::basic::default32_t crc;
    REQUIRE(crc.process_bytes(l_byte_raw_array_4, sizeof(l_byte_raw_array_4)) == 0x7C9CA35A);
    crc.reset();
    REQUIRE(crc.process_bytes(l_byte_raw_array_512, sizeof(l_byte_raw_array_512)) == 0x7DC21984);
    crc.reset();
    REQUIRE(crc.process_bytes(l_lorem_psum.c_str(), l_lorem_psum.size()) == 0x01877BBE);
  }

  SECTION("CRC-32/BZIP2")
  {
    crc::basic::bzip2_t crc;
    REQUIRE(crc.process_bytes(l_byte_raw_array_4, sizeof(l_byte_raw_array_4)) == 0x7E25E5E7);
    crc.reset();
    REQUIRE(crc.process_bytes(l_byte_raw_array_512, sizeof(l_byte_raw_array_512)) == 0x2CF8237A);
    crc.reset();
    REQUIRE(crc.process_bytes(l_lorem_psum.c_str(), l_lorem_psum.size()) == 0x5673AB77);
  }
  SECTION("CRC-32C")
  {
    crc::basic::crc32c_t crc;
    REQUIRE(crc.process_bytes(l_byte_raw_array_4, sizeof(l_byte_raw_array_4)) == 0xF1DC778E);
    crc.reset();
    REQUIRE(crc.process_bytes(l_byte_raw_array_512, sizeof(l_byte_raw_array_512)) == 0x0B80A70B);
    crc.reset();
    REQUIRE(crc.process_bytes(l_lorem_psum.c_str(), l_lorem_psum.size()) == 0x4A4E5A26);
  }
  SECTION("CRC-32D")
  {
    crc::basic::crc32d_t crc;
    REQUIRE(crc.process_bytes(l_byte_raw_array_4, sizeof(l_byte_raw_array_4)) == 0xD325B831);
    crc.reset();
    REQUIRE(crc.process_bytes(l_byte_raw_array_512, sizeof(l_byte_raw_array_512)) == 0xC72E79C0);
    crc.reset();
    REQUIRE(crc.process_bytes(l_lorem_psum.c_str(), l_lorem_psum.size()) == 0x0A4F0E08);
  }
  SECTION("CRC-32/MPEG")
  {
    crc::basic::mpeg2_t crc;
    REQUIRE(crc.process_bytes(l_byte_raw_array_4, sizeof(l_byte_raw_array_4)) == 0x81DA1A18);
    crc.reset();
    REQUIRE(crc.process_bytes(l_byte_raw_array_512, sizeof(l_byte_raw_array_512)) == 0xD307DC85);
    crc.reset();
    REQUIRE(crc.process_bytes(l_lorem_psum.c_str(), l_lorem_psum.size()) == 0xA98C5488);
  }
  SECTION("CRC-32/POSIX")
  {
    crc::basic::posix_t crc;
    REQUIRE(crc.process_bytes(l_byte_raw_array_4, sizeof(l_byte_raw_array_4)) == 0xB921389C);
    crc.reset();
    REQUIRE(crc.process_bytes(l_byte_raw_array_512, sizeof(l_byte_raw_array_512)) == 0xCDA989C8);
    crc.reset();
    REQUIRE(crc.process_bytes(l_lorem_psum.c_str(), l_lorem_psum.size()) == 0xAD4D2846);
  }
  SECTION("CRC-32Q")
  {
    crc::basic::crc32q_t crc;
    REQUIRE(crc.process_bytes(l_byte_raw_array_4, sizeof(l_byte_raw_array_4)) == 0xA5932B47);
    crc.reset();
    REQUIRE(crc.process_bytes(l_byte_raw_array_512, sizeof(l_byte_raw_array_512)) == 0x53D3490F);
    crc.reset();
    REQUIRE(crc.process_bytes(l_lorem_psum.c_str(), l_lorem_psum.size()) == 0xBD0B1C50);
  }
  SECTION("CRC-32/JAMCRC")
  {
    crc::basic::jamcrc_t crc;
    REQUIRE(crc.process_bytes(l_byte_raw_array_4, sizeof(l_byte_raw_array_4)) == 0x83635CA5);
    crc.reset();
    REQUIRE(crc.process_bytes(l_byte_raw_array_512, sizeof(l_byte_raw_array_512)) == 0x823DE67B);
    crc.reset();
    REQUIRE(crc.process_bytes(l_lorem_psum.c_str(), l_lorem_psum.size()) == 0xFE788441);
  }
  SECTION("CRC-32/XFER")
  {
    crc::basic::xfer_t crc;
    REQUIRE(crc.process_bytes(l_byte_raw_array_4, sizeof(l_byte_raw_array_4)) == 0x6F455145);
    crc.reset();
    REQUIRE(crc.process_bytes(l_byte_raw_array_512, sizeof(l_byte_raw_array_512)) == 0x6B04DAF3);
    crc.reset();
    REQUIRE(crc.process_bytes(l_lorem_psum.c_str(), l_lorem_psum.size()) == 0x28802431);
  }
}

// TEST_CASE("SLOW CRC16 CHECKSUMS ON SMALL DATA ARE COMPUTED CORRECTLY", "[crc16-slow]")
// {
//   const uint8_t data[] = {0xDE, 0xAD, 0xBE, 0xEF};

//   SECTION("CRC-16/CCITT-FALSE ")
//   {
//     crc_basic<uint16_t, 0x1021, 0xFFFF, 0x0000, false, false> l_c16;
//     REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0x4097);
//     REQUIRE(l_c16.checksum() == 0x4097);
//   }
//   SECTION("CRC-16/ARC         ")
//   {
//     crc_basic<uint16_t, 0x8005, 0x0000, 0x0000, true, true> l_c16;
//     REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0xE59B);
//   }
//   SECTION("CRC-16/AUG-CCITT   ")
//   {
//     crc_basic<uint16_t, 0x1021, 0x1D0F, 0x0000, false, false> l_c16;
//     REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0xCA47);
//   }
//   SECTION("CRC-16/BUYPASS     ")
//   {
//     crc_basic<uint16_t, 0x8005, 0x0000, 0x0000, false, false> l_c16;
//     REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0x962B);
//   }
//   SECTION("CRC-16/CDMA2000    ")
//   {
//     crc16_cdma2000_basic_t l_c16;
//     REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0xAEB8);
//   }
//   SECTION("CRC-16/DDS-110     ")
//   {
//     crc_basic<uint16_t, 0x8005, 0x800D, 0x0000, false, false> l_c16;
//     REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0x96F3);
//   }
//   SECTION("CRC-16/DECT-R      ")
//   {
//     crc_basic<uint16_t, 0x0589, 0x0000, 0x0001, false, false> l_c16;
//     REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0x303B);
//   }
//   SECTION("CRC-16/DECT-X      ")
//   {
//     crc_basic<uint16_t, 0x0589, 0x0000, 0x0000, false, false> l_c16;
//     REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0x303A);
//   }
//   SECTION("CRC-16/DNP         ")
//   {
//     crc_basic<uint16_t, 0x3D65, 0x0000, 0xFFFF, true, true> l_c16;
//     REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0x60B8);
//   }
//   SECTION("CRC-16/EN-13757    ")
//   {
//     crc_basic<uint16_t, 0x3D65, 0x0000, 0xFFFF, false, false> l_c16;
//     REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0x27E4);
//   }
//   SECTION("CRC-16/GENIBUS     ")
//   {
//     crc_basic<uint16_t, 0x1021, 0xFFFF, 0xFFFF, false, false> l_c16;
//     REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0xBF68);
//   }
//   SECTION("CRC-16/MAXIM       ")
//   {
//     crc_basic<uint16_t, 0x8005, 0x0000, 0xFFFF, true, true> l_c16;
//     REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0x1A64);
//   }
//   SECTION("CRC-16/MCRF4XX     ")
//   {
//     crc_basic<uint16_t, 0x1021, 0xFFFF, 0x0000, true, true> l_c16;
//     REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0x1A34);
//   }
//   SECTION("CRC-16/RIELLO      ")
//   {
//     crc_basic<uint16_t, 0x1021, 0xB2AA, 0x0000, true, true> l_c16;
//     REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0x3E73);
//   }
//   SECTION("CRC-16/T10-DIF     ")
//   {
//     crc_basic<uint16_t, 0x8BB7, 0x0000, 0x0000, false, false> l_c16;
//     REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0x34DC);
//   }
//   SECTION("CRC-16/TELEDISK    ")
//   {
//     crc_basic<uint16_t, 0xA097, 0x0000, 0x0000, false, false> l_c16;
//     REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0x520D);
//   }
//   SECTION("CRC-16/TMS37157    ")
//   {
//     crc_basic<uint16_t, 0x1021, 0x89EC, 0x0000, true, true> l_c16;
//     REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0xE1CA);
//   }
//   SECTION("CRC-16/USB         ")
//   {
//     crc_basic<uint16_t, 0x8005, 0xFFFF, 0xFFFF, true, true> l_c16;
//     REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0x3E64);
//   }
//   SECTION("CRC-A              ")
//   {
//     crc_basic<uint16_t, 0x1021, 0xC6C6, 0x0000, true, true> l_c16;
//     REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0x4F15);
//   }
//   SECTION("CRC-16/KERMIT      ")
//   {
//     crc_basic<uint16_t, 0x1021, 0x0000, 0x0000, true, true> l_c16;
//     REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0x1915);
//   }
//   SECTION("CRC-16/MODBUS      ")
//   {
//     crc_basic<uint16_t, 0x8005, 0xFFFF, 0x0000, true, true> l_c16;
//     REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0xC19B);
//   }
//   SECTION("CRC-16/X-25        ")
//   {
//     crc_basic<uint16_t, 0x1021, 0xFFFF, 0xFFFF, true, true> l_c16;
//     REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0xE5CB);
//   }
//   SECTION("CRC-16/XMODEM      ")
//   {
//     crc_basic<uint16_t, 0x1021, 0x0000, 0x0000, false, false> l_c16;
//     REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0xC457);
//   }
// }

#if 0

TEST_CASE("SLOW CRC8 CHECKSUMS ON SMALL DATA ARE COMPUTED CORRECTLY", "[crc8-slow]")
{
  using namespace crc::slow;
  uint8_t data[] = {0xDE, 0xAD, 0xBE, 0xEF};
  SECTION("CRC-8           ")
  {
    crc<uint8_t> c8(0x07, 0x00, 0x00, false, false);
    REQUIRE(c8.get(data, sizeof(data)) == 0xCA);
  }
  SECTION("CRC-8/CDMA2000  ")
  {
    crc<uint8_t> c8(0x9B, 0xFF, 0x00, false, false);
    REQUIRE(c8.get(data, sizeof(data)) == 0x77);
  }
  SECTION("CRC-8/DARC      ")
  {
    crc<uint8_t> c8(0x39, 0x00, 0x00, true, true);
    REQUIRE(c8.get(data, sizeof(data)) == 0xC0);
  }
  SECTION("CRC-8/DVB-S2    ")
  {
    crc<uint8_t> c8(0xD5, 0x00, 0x00, false, false);
    REQUIRE(c8.get(data, sizeof(data)) == 0xA5);
  }
  SECTION("CRC-8/EBU       ")
  {
    crc<uint8_t> c8(0x1D, 0xFF, 0x00, true, true);
    REQUIRE(c8.get(data, sizeof(data)) == 0x64);
  }
  SECTION("CRC-8/I-CODE    ")
  {
    crc<uint8_t> c8(0x1D, 0xFD, 0x00, false, false);
    REQUIRE(c8.get(data, sizeof(data)) == 0x6B);
  }
  SECTION("CRC-8/ITU       ")
  {
    crc<uint8_t> c8(0x07, 0x00, 0x55, false, false);
    REQUIRE(c8.get(data, sizeof(data)) == 0x9F);
  }
  SECTION("CRC-8/MAXIM     ")
  {
    crc<uint8_t> c8(0x31, 0x00, 0x00, true, true);
    REQUIRE(c8.get(data, sizeof(data)) == 0x84);
  }
  SECTION("CRC-8/ROHC      ")
  {
    crc<uint8_t> c8(0x07, 0xFF, 0x00, true, true);
    REQUIRE(c8.get(data, sizeof(data)) == 0xC3);
  }
  SECTION("CRC-8/WCDMA     ")
  {
    crc<uint8_t> c8(0x9B, 0x00, 0x00, true, true);
    REQUIRE(c8.get(data, sizeof(data)) == 0xCC);
  }
}

TEST_CASE("FAST CRC32 CHECKSUMS ON SMALL DATA ARE COMPUTED CORRECTLY", "[crc32-fast]")
{
  using namespace crc::fast;
  uint8_t data[] = {0xDE, 0xAD, 0xBE, 0xEF};
  SECTION("CRC-32")
  {
    crc_basic<uint32_t, 0x4C11DB7, 0xFFFFFFFF, 0xFFFFFFFF, true, true> crc;
    REQUIRE(crc.process_bytes(data, sizeof(data)) == 0x7C9CA35A);
  }

  SECTION("CRC-32/BZIP2")
  {
    crc_basic<uint32_t, 0x04C11DB7, 0xFFFFFFFF, 0xFFFFFFFF, false, false> crc;
    REQUIRE(crc.process_bytes(data, sizeof(data)) == 0x7E25E5E7);
  }
  SECTION("CRC-32C")
  {
    crc_basic<uint32_t, 0x1EDC6F41, 0xFFFFFFFF, 0xFFFFFFFF, true, true> crc;
    REQUIRE(crc.process_bytes(data, sizeof(data)) == 0xF1DC778E);
  }
  SECTION("CRC-32D")
  {
    crc_basic<uint32_t, 0xA833982B, 0xFFFFFFFF, 0xFFFFFFFF, true, true> crc;
    REQUIRE(crc.process_bytes(data, sizeof(data)) == 0xD325B831);
  }
  SECTION("CRC-32/MPEG")
  {
    crc_basic<uint32_t, 0x04C11DB7, 0xFFFFFFFF, 0x00000000, false, false> crc;
    REQUIRE(crc.process_bytes(data, sizeof(data)) == 0x81DA1A18);
  }
  SECTION("CRC-32/POSIX")
  {
    crc_basic<uint32_t, 0x04C11DB7, 0x00000000, 0xFFFFFFFF, false, false> crc;
    REQUIRE(crc.process_bytes(data, sizeof(data)) == 0xB921389C);
  }
  SECTION("CRC-32Q")
  {
    crc_basic<uint32_t, 0x814141AB, 0x00000000, 0x00000000, false, false> crc;
    REQUIRE(crc.process_bytes(data, sizeof(data)) == 0xA5932B47);
  }
  SECTION("CRC-32/JAMCRC")
  {
    crc_basic<uint32_t, 0x04C11DB7, 0xFFFFFFFF, 0x00000000, true, true> crc;
    REQUIRE(crc.process_bytes(data, sizeof(data)) == 0x83635CA5);
  }
  SECTION("CRC-32/XFER")
  {
    crc_basic<uint32_t, 0x000000AF, 0x00000000, 0x00000000, false, false> crc;
    REQUIRE(crc.process_bytes(data, sizeof(data)) == 0x6F455145);
  }
}

TEST_CASE("FAST CRC16 CHECKSUMS ON SMALL DATA ARE COMPUTED CORRECTLY", "[crc16-fast]")
{
  using namespace crc::fast;
  uint8_t data[] = {0xDE, 0xAD, 0xBE, 0xEF};
  SECTION("CRC-16/CCITT-FALSE ")
  {
    crc<uint16_t> c16(0x1021, 0xFFFF, 0x0000, false, false);
    REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0x4097);
  }
  SECTION("CRC-16/ARC         ")
  {
    crc<uint16_t> c16(0x8005, 0x0000, 0x0000, true, true);
    REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0xE59B);
  }
  SECTION("CRC-16/AUG-CCITT   ")
  {
    crc<uint16_t> c16(0x1021, 0x1D0F, 0x0000, false, false);
    REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0xCA47);
  }
  SECTION("CRC-16/BUYPASS     ")
  {
    crc<uint16_t> c16(0x8005, 0x0000, 0x0000, false, false);
    REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0x962B);
  }
  SECTION("CRC-16/CDMA2000    ")
  {
    crc<uint16_t> c16(0xC867, 0xFFFF, 0x0000, false, false);
    REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0xAEB8);
  }
  SECTION("CRC-16/DDS-110     ")
  {
    crc<uint16_t> c16(0x8005, 0x800D, 0x0000, false, false);
    REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0x96F3);
  }
  SECTION("CRC-16/DECT-R      ")
  {
    crc<uint16_t> c16(0x0589, 0x0000, 0x0001, false, false);
    REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0x303B);
  }
  SECTION("CRC-16/DECT-X      ")
  {
    crc<uint16_t> c16(0x0589, 0x0000, 0x0000, false, false);
    REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0x303A);
  }
  SECTION("CRC-16/DNP         ")
  {
    crc<uint16_t> c16(0x3D65, 0x0000, 0xFFFF, true, true);
    REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0x60B8);
  }
  SECTION("CRC-16/EN-13757    ")
  {
    crc<uint16_t> c16(0x3D65, 0x0000, 0xFFFF, false, false);
    REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0x27E4);
  }
  SECTION("CRC-16/GENIBUS     ")
  {
    crc<uint16_t> c16(0x1021, 0xFFFF, 0xFFFF, false, false);
    REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0xBF68);
  }
  SECTION("CRC-16/MAXIM       ")
  {
    crc<uint16_t> c16(0x8005, 0x0000, 0xFFFF, true, true);
    REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0x1A64);
  }
  SECTION("CRC-16/MCRF4XX     ")
  {
    crc<uint16_t> c16(0x1021, 0xFFFF, 0x0000, true, true);
    REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0x1A34);
  }
  SECTION("CRC-16/RIELLO      ")
  {
    crc<uint16_t> c16(0x1021, 0xB2AA, 0x0000, true, true);
    REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0x3E73);
  }
  SECTION("CRC-16/T10-DIF     ")
  {
    crc<uint16_t> c16(0x8BB7, 0x0000, 0x0000, false, false);
    REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0x34DC);
  }
  SECTION("CRC-16/TELEDISK    ")
  {
    crc<uint16_t> c16(0xA097, 0x0000, 0x0000, false, false);
    REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0x520D);
  }
  SECTION("CRC-16/TMS37157    ")
  {
    crc<uint16_t> c16(0x1021, 0x89EC, 0x0000, true, true);
    REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0xE1CA);
  }
  SECTION("CRC-16/USB         ")
  {
    crc<uint16_t> c16(0x8005, 0xFFFF, 0xFFFF, true, true);
    REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0x3E64);
  }
  SECTION("CRC-A              ")
  {
    crc<uint16_t> c16(0x1021, 0xC6C6, 0x0000, true, true);
    REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0x4F15);
  }
  SECTION("CRC-16/KERMIT      ")
  {
    crc<uint16_t> c16(0x1021, 0x0000, 0x0000, true, true);
    REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0x1915);
  }
  SECTION("CRC-16/MODBUS      ")
  {
    crc<uint16_t> c16(0x8005, 0xFFFF, 0x0000, true, true);
    REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0xC19B);
  }
  SECTION("CRC-16/X-25        ")
  {
    crc<uint16_t> c16(0x1021, 0xFFFF, 0xFFFF, true, true);
    REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0xE5CB);
  }
  SECTION("CRC-16/XMODEM      ")
  {
    crc<uint16_t> c16(0x1021, 0x0000, 0x0000, false, false);
    REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0xC457);
  }
}

TEST_CASE("FAST CRC8 CHECKSUMS ON SMALL DATA ARE COMPUTED CORRECTLY", "[crc8-fast]")
{
  using namespace crc::fast;
  uint8_t data[] = {0xDE, 0xAD, 0xBE, 0xEF};
  SECTION("CRC-8           ")
  {
    crc<uint8_t> c8(0x07, 0x00, 0x00, false, false);
    REQUIRE(c8.get(data, sizeof(data)) == 0xCA);
  }
  SECTION("CRC-8/CDMA2000  ")
  {
    crc<uint8_t> c8(0x9B, 0xFF, 0x00, false, false);
    REQUIRE(c8.get(data, sizeof(data)) == 0x77);
  }
  SECTION("CRC-8/DARC      ")
  {
    crc<uint8_t> c8(0x39, 0x00, 0x00, true, true);
    REQUIRE(c8.get(data, sizeof(data)) == 0xC0);
  }
  SECTION("CRC-8/DVB-S2    ")
  {
    crc<uint8_t> c8(0xD5, 0x00, 0x00, false, false);
    REQUIRE(c8.get(data, sizeof(data)) == 0xA5);
  }
  SECTION("CRC-8/EBU       ")
  {
    crc<uint8_t> c8(0x1D, 0xFF, 0x00, true, true);
    REQUIRE(c8.get(data, sizeof(data)) == 0x64);
  }
  SECTION("CRC-8/I-CODE    ")
  {
    crc<uint8_t> c8(0x1D, 0xFD, 0x00, false, false);
    REQUIRE(c8.get(data, sizeof(data)) == 0x6B);
  }
  SECTION("CRC-8/ITU       ")
  {
    crc<uint8_t> c8(0x07, 0x00, 0x55, false, false);
    REQUIRE(c8.get(data, sizeof(data)) == 0x9F);
  }
  SECTION("CRC-8/MAXIM     ")
  {
    crc<uint8_t> c8(0x31, 0x00, 0x00, true, true);
    REQUIRE(c8.get(data, sizeof(data)) == 0x84);
  }
  SECTION("CRC-8/ROHC      ")
  {
    crc<uint8_t> c8(0x07, 0xFF, 0x00, true, true);
    REQUIRE(c8.get(data, sizeof(data)) == 0xC3);
  }
  SECTION("CRC-8/WCDMA     ")
  {
    crc<uint8_t> c8(0x9B, 0x00, 0x00, true, true);
    REQUIRE(c8.get(data, sizeof(data)) == 0xCC);
  }
}
#endif
