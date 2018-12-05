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
    "purus ipsum sem bibendum tristique pretium nulla, arcu porttitor.	Maecenas vestibulum sit, aliquam dolor, erat purus elit vestibulum "
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
#if 0
TEST_CASE("SLOW CRC32 CHECKSUMS ON SMALL DATA ARE COMPUTED CORRECTLY", "[crc32-slow]")
{
  using namespace crc::slow;
  uint8_t data[] = {0xDE, 0xAD, 0xBE, 0xEF};
  SECTION("CRC-32")
  {
    crc<uint32_t> c32(0x4C11DB7, 0xFFFFFFFF, 0xFFFFFFFF, true, true);
    REQUIRE(c32.get(data, sizeof(data)) == 0x7C9CA35A);
  }

  SECTION("CRC-32/BZIP2")
  {
    crc<uint32_t> c32(0x04C11DB7, 0xFFFFFFFF, 0xFFFFFFFF, false, false);
    REQUIRE(c32.get(data, sizeof(data)) == 0x7E25E5E7);
  }
  SECTION("CRC-32C")
  {
    crc<uint32_t> c32(0x1EDC6F41, 0xFFFFFFFF, 0xFFFFFFFF, true, true);
    REQUIRE(c32.get(data, sizeof(data)) == 0xF1DC778E);
  }
  SECTION("CRC-32D")
  {
    crc<uint32_t> c32(0xA833982B, 0xFFFFFFFF, 0xFFFFFFFF, true, true);
    REQUIRE(c32.get(data, sizeof(data)) == 0xD325B831);
  }
  SECTION("CRC-32/MPEG")
  {
    crc<uint32_t> c32(0x04C11DB7, 0xFFFFFFFF, 0x00000000, false, false);
    REQUIRE(c32.get(data, sizeof(data)) == 0x81DA1A18);
  }
  SECTION("CRC-32/POSIX")
  {
    crc<uint32_t> c32(0x04C11DB7, 0x00000000, 0xFFFFFFFF, false, false);
    REQUIRE(c32.get(data, sizeof(data)) == 0xB921389C);
  }
  SECTION("CRC-32Q")
  {
    crc<uint32_t> c32(0x814141AB, 0x00000000, 0x00000000, false, false);
    REQUIRE(c32.get(data, sizeof(data)) == 0xA5932B47);
  }
  SECTION("CRC-32/JAMCRC")
  {
    crc<uint32_t> c32(0x04C11DB7, 0xFFFFFFFF, 0x00000000, true, true);
    REQUIRE(c32.get(data, sizeof(data)) == 0x83635CA5);
  }
  SECTION("CRC-32/XFER")
  {
    crc<uint32_t> c32(0x000000AF, 0x00000000, 0x00000000, false, false);
    REQUIRE(c32.get(data, sizeof(data)) == 0x6F455145);
  }
}
#endif
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

TEST_CASE("SLOW CRC16 CHECKSUMS ON SMALL DATA ARE COMPUTED CORRECTLY", "[crc16-slow]")
{
  const uint8_t data[] = {0xDE, 0xAD, 0xBE, 0xEF};

  SECTION("CRC-16/CCITT-FALSE ")
  {
    crc_basic<uint16_t, 0x1021, 0xFFFF, 0x0000, false, false> l_c16;
    REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0x4097);
    REQUIRE(l_c16.checksum() == 0x4097);
  }
  SECTION("CRC-16/ARC         ")
  {
    crc_basic<uint16_t, 0x8005, 0x0000, 0x0000, true, true> l_c16;
    REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0xE59B);
  }
  SECTION("CRC-16/AUG-CCITT   ")
  {
    crc_basic<uint16_t, 0x1021, 0x1D0F, 0x0000, false, false> l_c16;
    REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0xCA47);
  }
  SECTION("CRC-16/BUYPASS     ")
  {
    crc_basic<uint16_t, 0x8005, 0x0000, 0x0000, false, false> l_c16;
    REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0x962B);
  }
  SECTION("CRC-16/CDMA2000    ")
  {
    crc_basic<uint16_t, 0xC867, 0xFFFF, 0x0000, false, false> l_c16;
    REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0xAEB8);
  }
  SECTION("CRC-16/DDS-110     ")
  {
    crc_basic<uint16_t, 0x8005, 0x800D, 0x0000, false, false> l_c16;
    REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0x96F3);
  }
  SECTION("CRC-16/DECT-R      ")
  {
    crc_basic<uint16_t, 0x0589, 0x0000, 0x0001, false, false> l_c16;
    REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0x303B);
  }
  SECTION("CRC-16/DECT-X      ")
  {
    crc_basic<uint16_t, 0x0589, 0x0000, 0x0000, false, false> l_c16;
    REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0x303A);
  }
  SECTION("CRC-16/DNP         ")
  {
    crc_basic<uint16_t, 0x3D65, 0x0000, 0xFFFF, true, true> l_c16;
    REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0x60B8);
  }
  SECTION("CRC-16/EN-13757    ")
  {
    crc_basic<uint16_t, 0x3D65, 0x0000, 0xFFFF, false, false> l_c16;
    REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0x27E4);
  }
  SECTION("CRC-16/GENIBUS     ")
  {
    crc_basic<uint16_t, 0x1021, 0xFFFF, 0xFFFF, false, false> l_c16;
    REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0xBF68);
  }
  SECTION("CRC-16/MAXIM       ")
  {
    crc_basic<uint16_t, 0x8005, 0x0000, 0xFFFF, true, true> l_c16;
    REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0x1A64);
  }
  SECTION("CRC-16/MCRF4XX     ")
  {
    crc_basic<uint16_t, 0x1021, 0xFFFF, 0x0000, true, true> l_c16;
    REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0x1A34);
  }
  SECTION("CRC-16/RIELLO      ")
  {
    crc_basic<uint16_t, 0x1021, 0xB2AA, 0x0000, true, true> l_c16;
    REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0x3E73);
  }
  SECTION("CRC-16/T10-DIF     ")
  {
    crc_basic<uint16_t, 0x8BB7, 0x0000, 0x0000, false, false> l_c16;
    REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0x34DC);
  }
  SECTION("CRC-16/TELEDISK    ")
  {
    crc_basic<uint16_t, 0xA097, 0x0000, 0x0000, false, false> l_c16;
    REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0x520D);
  }
  SECTION("CRC-16/TMS37157    ")
  {
    crc_basic<uint16_t, 0x1021, 0x89EC, 0x0000, true, true> l_c16;
    REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0xE1CA);
  }
  SECTION("CRC-16/USB         ")
  {
    crc_basic<uint16_t, 0x8005, 0xFFFF, 0xFFFF, true, true> l_c16;
    REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0x3E64);
  }
  SECTION("CRC-A              ")
  {
    crc_basic<uint16_t, 0x1021, 0xC6C6, 0x0000, true, true> l_c16;
    REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0x4F15);
  }
  SECTION("CRC-16/KERMIT      ")
  {
    crc_basic<uint16_t, 0x1021, 0x0000, 0x0000, true, true> l_c16;
    REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0x1915);
  }
  SECTION("CRC-16/MODBUS      ")
  {
    crc_basic<uint16_t, 0x8005, 0xFFFF, 0x0000, true, true> l_c16;
    REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0xC19B);
  }
  SECTION("CRC-16/X-25        ")
  {
    crc_basic<uint16_t, 0x1021, 0xFFFF, 0xFFFF, true, true> l_c16;
    REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0xE5CB);
  }
  SECTION("CRC-16/XMODEM      ")
  {
    crc_basic<uint16_t, 0x1021, 0x0000, 0x0000, false, false> l_c16;
    REQUIRE(l_c16.process_bytes(data, sizeof(data)) == 0xC457);
  }
}

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
    crc<uint32_t> c32(0x4C11DB7, 0xFFFFFFFF, 0xFFFFFFFF, true, true);
    REQUIRE(c32.get(data, sizeof(data)) == 0x7C9CA35A);
  }

  SECTION("CRC-32/BZIP2")
  {
    crc<uint32_t> c32(0x04C11DB7, 0xFFFFFFFF, 0xFFFFFFFF, false, false);
    REQUIRE(c32.get(data, sizeof(data)) == 0x7E25E5E7);
  }
  SECTION("CRC-32C")
  {
    crc<uint32_t> c32(0x1EDC6F41, 0xFFFFFFFF, 0xFFFFFFFF, true, true);
    REQUIRE(c32.get(data, sizeof(data)) == 0xF1DC778E);
  }
  SECTION("CRC-32D")
  {
    crc<uint32_t> c32(0xA833982B, 0xFFFFFFFF, 0xFFFFFFFF, true, true);
    REQUIRE(c32.get(data, sizeof(data)) == 0xD325B831);
  }
  SECTION("CRC-32/MPEG")
  {
    crc<uint32_t> c32(0x04C11DB7, 0xFFFFFFFF, 0x00000000, false, false);
    REQUIRE(c32.get(data, sizeof(data)) == 0x81DA1A18);
  }
  SECTION("CRC-32/POSIX")
  {
    crc<uint32_t> c32(0x04C11DB7, 0x00000000, 0xFFFFFFFF, false, false);
    REQUIRE(c32.get(data, sizeof(data)) == 0xB921389C);
  }
  SECTION("CRC-32Q")
  {
    crc<uint32_t> c32(0x814141AB, 0x00000000, 0x00000000, false, false);
    REQUIRE(c32.get(data, sizeof(data)) == 0xA5932B47);
  }
  SECTION("CRC-32/JAMCRC")
  {
    crc<uint32_t> c32(0x04C11DB7, 0xFFFFFFFF, 0x00000000, true, true);
    REQUIRE(c32.get(data, sizeof(data)) == 0x83635CA5);
  }
  SECTION("CRC-32/XFER")
  {
    crc<uint32_t> c32(0x000000AF, 0x00000000, 0x00000000, false, false);
    REQUIRE(c32.get(data, sizeof(data)) == 0x6F455145);
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
