/*
* @Author: lu
* @Date:   10-01-2018
* @Last Modified by:   lu
* @Last Modified time: 26-01-2018
*/

#include <iostream>
#include <string>
#include <array>
#include <stdint.h>

#include "cpp-crc.hpp"
#include "bitop.hpp"


#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch.hpp"



TEST_CASE("bitop::reverse works correctly. ", "[bitop]")
{

    SECTION( "8 bit" )
    {
        REQUIRE( bitop::reverse<uint8_t>(0xFF) == 0xFF);
        REQUIRE( bitop::reverse<uint8_t>(0x00) == 0x00);
        REQUIRE( bitop::reverse<uint8_t>(0x0F) == 0xF0);
        REQUIRE( bitop::reverse<uint8_t>(0x01) == 0x80);
        REQUIRE( bitop::reverse<uint8_t>(0x80) == 0x01);
        REQUIRE( bitop::reverse<uint8_t>(0xAA) == 0x55);
        REQUIRE( bitop::reverse<uint8_t>(0x55) == 0xAA);
    }

    SECTION( "16 bit" )
    {
        REQUIRE( bitop::reverse<uint16_t>(0xFFFF) == 0xFFFF);
        REQUIRE( bitop::reverse<uint16_t>(0x0000) == 0x0000);
        REQUIRE( bitop::reverse<uint16_t>(0x000F) == 0xF000);
        REQUIRE( bitop::reverse<uint16_t>(0x0001) == 0x8000);
        REQUIRE( bitop::reverse<uint16_t>(0xAAAA) == 0x5555);
        REQUIRE( bitop::reverse<uint16_t>(0x5555) == 0xAAAA);
    }

    SECTION( "32 bit" )
    {
        REQUIRE( bitop::reverse<uint32_t>(0xFFFFFFFF) == 0xFFFFFFFF);
        REQUIRE( bitop::reverse<uint32_t>(0x0000000F) == 0xF0000000);
        REQUIRE( bitop::reverse<uint32_t>(0x00000001) == 0x80000000);
        REQUIRE( bitop::reverse<uint32_t>(0x80000000) == 0x00000001);
        REQUIRE( bitop::reverse<uint32_t>(0x00000000) == 0x00000000);
        REQUIRE( bitop::reverse<uint32_t>(0xAAAAAAAA) == 0x55555555);
        REQUIRE( bitop::reverse<uint32_t>(0x55555555) == 0xAAAAAAAA);
    }

}

TEST_CASE("SLOW CRC32 CHECKSUMS ON SMALL DATA ARE COMPUTED CORRECTLY", "[crc32]")
{
//         Algorithm       Result      Poly        Init        RefIn   RefOut  XorOut
//         CRC-32          0x7C9CA35A  0x04C11DB7  0xFFFFFFFF  true    true    0xFFFFFFFF
//         CRC-32/BZIP2    0x7E25E5E7  0x04C11DB7  0xFFFFFFFF  false   false   0xFFFFFFFF
//         CRC-32C         0xF1DC778E  0x1EDC6F41  0xFFFFFFFF  true    true    0xFFFFFFFF
//         CRC-32D         0xD325B831  0xA833982B  0xFFFFFFFF  true    true    0xFFFFFFFF
//         CRC-32/MPEG-2   0x81DA1A18  0x04C11DB7  0xFFFFFFFF  false   false   0x00000000
//         CRC-32/POSIX    0xB921389C  0x04C11DB7  0x00000000  false   false   0xFFFFFFFF
//         CRC-32Q         0xA5932B47  0x814141AB  0x00000000  false   false   0x00000000
//         CRC-32/JAMCRC   0x83635CA5  0x04C11DB7  0xFFFFFFFF  true    true    0x00000000
//         CRC-32/XFER     0x6F455145  0x000000AF  0x00000000  false   false   0x00000000
    using namespace cpp_crc::slow;
    uint8_t data[] = {0xDE, 0xAD, 0xBE, 0xEF};
    SECTION( "CRC-32" )
    {
        crc<uint32_t> c32(0x4C11DB7, 0xFFFFFFFF, 0xFFFFFFFF, true, true );
        REQUIRE( c32.get(data, sizeof(data)) ==  0x7C9CA35A);
    }

    SECTION("CRC-32/BZIP2")
    {
        crc<uint32_t> c32(0x04C11DB7, 0xFFFFFFFF, 0xFFFFFFFF, false, false);
        REQUIRE( c32.get(data, sizeof(data)) ==  0x7E25E5E7);
    }
	SECTION("CRC-32C")
	{
		crc<uint32_t> c32(0x1EDC6F41, 0xFFFFFFFF, 0xFFFFFFFF, true, true );
        REQUIRE( c32.get(data, sizeof(data)) ==  0xF1DC778E);
	}
	SECTION("CRC-32D")
	{
		crc<uint32_t> c32(0xA833982B, 0xFFFFFFFF, 0xFFFFFFFF, true, true );
        REQUIRE( c32.get(data, sizeof(data)) ==  0xD325B831);
	}
	SECTION("CRC-32/MPEG")
	{
		crc<uint32_t> c32(0x04C11DB7, 0xFFFFFFFF, 0x00000000, false, false);
        REQUIRE( c32.get(data, sizeof(data)) ==  0x81DA1A18);
	}
	SECTION("CRC-32/POSIX")
	{
		crc<uint32_t> c32(0x04C11DB7, 0x00000000, 0xFFFFFFFF, false, false);
        REQUIRE( c32.get(data, sizeof(data)) ==  0xB921389C);
	}
	SECTION("CRC-32Q")
	{
		crc<uint32_t> c32(0x814141AB, 0x00000000, 0x00000000, false, false);
        REQUIRE( c32.get(data, sizeof(data)) ==  0xA5932B47);
	}
	SECTION("CRC-32/JAMCRC")
	{
		crc<uint32_t> c32(0x04C11DB7, 0xFFFFFFFF, 0x00000000, true, true );
        REQUIRE( c32.get(data, sizeof(data)) ==  0x83635CA5);
	}
	SECTION("CRC-32/XFER")
	{
		crc<uint32_t> c32(0x000000AF, 0x00000000, 0x00000000, false, false);
        REQUIRE( c32.get(data, sizeof(data)) ==  0x6F455145);
	}
}


TEST_CASE("SLOW CRC16 CHECKSUMS ON SMALL DATA ARE COMPUTED CORRECTLY", "[crc16]")
{
//         Algorithm           Result  Poly    Init    RefIn   RefOut  XorOut
//         CRC-16/CCITT-FALSE  0x4097  0x1021  0xFFFF  false   false   0x0000
//         CRC-16/ARC          0xE59B  0x8005  0x0000  true    true    0x0000
//         CRC-16/AUG-CCITT    0xCA47  0x1021  0x1D0F  false   false   0x0000
//         CRC-16/BUYPASS      0x962B  0x8005  0x0000  false   false   0x0000
//         CRC-16/CDMA2000     0xAEB8  0xC867  0xFFFF  false   false   0x0000
//         CRC-16/DDS-110      0x96F3  0x8005  0x800D  false   false   0x0000
//         CRC-16/DECT-R       0x303B  0x0589  0x0000  false   false   0x0001
//         CRC-16/DECT-X       0x303A  0x0589  0x0000  false   false   0x0000
//         CRC-16/DNP          0x60B8  0x3D65  0x0000  true    true    0xFFFF
//         CRC-16/EN-13757     0x27E4  0x3D65  0x0000  false   false   0xFFFF
//         CRC-16/GENIBUS      0xBF68  0x1021  0xFFFF  false   false   0xFFFF
//         CRC-16/MAXIM        0x1A64  0x8005  0x0000  true    true    0xFFFF
//         CRC-16/MCRF4XX      0x1A34  0x1021  0xFFFF  true    true    0x0000
//         CRC-16/RIELLO       0x3E73  0x1021  0xB2AA  true    true    0x0000
//         CRC-16/T10-DIF      0x34DC  0x8BB7  0x0000  false   false   0x0000
//         CRC-16/TELEDISK     0x520D  0xA097  0x0000  false   false   0x0000
//         CRC-16/TMS37157     0xE1CA  0x1021  0x89EC  true    true    0x0000
//         CRC-16/USB          0x3E64  0x8005  0xFFFF  true    true    0xFFFF
//         CRC-A               0x4F15  0x1021  0xC6C6  true    true    0x0000
//         CRC-16/KERMIT       0x1915  0x1021  0x0000  true    true    0x0000
//         CRC-16/MODBUS       0xC19B  0x8005  0xFFFF  true    true    0x0000
//         CRC-16/X-25         0xE5CB  0x1021  0xFFFF  true    true    0xFFFF
//         CRC-16/XMODEM       0xC457  0x1021  0x0000  false   false   0x0000
	using namespace cpp_crc::slow;
	uint8_t data[] = {0xDE, 0xAD, 0xBE, 0xEF};
	SECTION("CRC-16/CCITT-FALSE ")
	{
		crc<uint16_t> c16(0x1021, 0xFFFF, 0x0000, false, false);
		REQUIRE( c16.get(data, sizeof(data)) == 0x4097);
	}
	SECTION("CRC-16/ARC         ")
	{
		crc<uint16_t> c16(0x8005, 0x0000, 0x0000, true, true);
		REQUIRE( c16.get(data, sizeof(data)) == 0xE59B);
	}
	SECTION("CRC-16/AUG-CCITT   ")
	{
		crc<uint16_t> c16(0x1021, 0x1D0F, 0x0000, false, false);
		REQUIRE( c16.get(data, sizeof(data)) == 0xCA47);
	}
	SECTION("CRC-16/BUYPASS     ")
	{
		crc<uint16_t> c16(0x8005, 0x0000, 0x0000, false, false);
		REQUIRE( c16.get(data, sizeof(data)) == 0x962B);
	}
	SECTION("CRC-16/CDMA2000    ")
	{
		crc<uint16_t> c16(0xC867, 0xFFFF, 0x0000, false, false);
		REQUIRE( c16.get(data, sizeof(data)) == 0xAEB8);
	}
	SECTION("CRC-16/DDS-110     ")
	{
		crc<uint16_t> c16(0x8005, 0x800D, 0x0000, false, false);
		REQUIRE( c16.get(data, sizeof(data)) == 0x96F3);
	}
	SECTION("CRC-16/DECT-R      ")
	{
		crc<uint16_t> c16(0x0589, 0x0000, 0x0001, false, false);
		REQUIRE( c16.get(data, sizeof(data)) == 0x303B);
	}
	SECTION("CRC-16/DECT-X      ")
	{
		crc<uint16_t> c16(0x0589, 0x0000, 0x0000, false, false);
		REQUIRE( c16.get(data, sizeof(data)) == 0x303A);
	}
	SECTION("CRC-16/DNP         ")
	{
		crc<uint16_t> c16(0x3D65, 0x0000, 0xFFFF, true, true);
		REQUIRE( c16.get(data, sizeof(data)) == 0x60B8);
	}
	SECTION("CRC-16/EN-13757    ")
	{
		crc<uint16_t> c16(0x3D65, 0x0000, 0xFFFF, false, false);
		REQUIRE( c16.get(data, sizeof(data)) == 0x27E4);
	}
	SECTION("CRC-16/GENIBUS     ")
	{
		crc<uint16_t> c16(0x1021, 0xFFFF, 0xFFFF, false, false);
		REQUIRE( c16.get(data, sizeof(data)) == 0xBF68);
	}
	SECTION("CRC-16/MAXIM       ")
	{
		crc<uint16_t> c16(0x8005, 0x0000, 0xFFFF, true, true);
		REQUIRE( c16.get(data, sizeof(data)) == 0x1A64);
	}
	SECTION("CRC-16/MCRF4XX     ")
	{
		crc<uint16_t> c16(0x1021, 0xFFFF, 0x0000, true, true);
		REQUIRE( c16.get(data, sizeof(data)) == 0x1A34);
	}
	SECTION("CRC-16/RIELLO      ")
	{
		crc<uint16_t> c16(0x1021, 0xB2AA, 0x0000, true, true);
		REQUIRE( c16.get(data, sizeof(data)) == 0x3E73);
	}
	SECTION("CRC-16/T10-DIF     ")
	{
		crc<uint16_t> c16(0x8BB7, 0x0000, 0x0000, false, false);
		REQUIRE( c16.get(data, sizeof(data)) == 0x34DC);
	}
	SECTION("CRC-16/TELEDISK    ")
	{
		crc<uint16_t> c16(0xA097, 0x0000, 0x0000, false, false);
		REQUIRE( c16.get(data, sizeof(data)) == 0x520D);
	}
	SECTION("CRC-16/TMS37157    ")
	{
		crc<uint16_t> c16(0x1021, 0x89EC, 0x0000, true, true);
		REQUIRE( c16.get(data, sizeof(data)) == 0xE1CA);
	}
	SECTION("CRC-16/USB         ")
	{
		crc<uint16_t> c16(0x8005, 0xFFFF, 0xFFFF, true, true);
		REQUIRE( c16.get(data, sizeof(data)) == 0x3E64 );
	}
	SECTION("CRC-A              ")
	{
		crc<uint16_t> c16(0x1021, 0xC6C6, 0x0000, true, true);
		REQUIRE( c16.get(data, sizeof(data)) == 0x4F15);
	}
	SECTION("CRC-16/KERMIT      ")
	{
		crc<uint16_t> c16(0x1021, 0x0000, 0x0000, true, true);
		REQUIRE( c16.get(data, sizeof(data)) == 0x1915);
	}
	SECTION("CRC-16/MODBUS      ")
	{
		crc<uint16_t> c16(0x8005, 0xFFFF, 0x0000, true, true);
		REQUIRE( c16.get(data, sizeof(data)) == 0xC19B );
	}
	SECTION("CRC-16/X-25        ")
	{
		crc<uint16_t> c16(0x1021, 0xFFFF, 0xFFFF, true, true);
		REQUIRE( c16.get(data, sizeof(data)) == 0xE5CB );
	}
	SECTION("CRC-16/XMODEM      ")
	{
		crc<uint16_t> c16(0x1021, 0x0000, 0x0000, false, false);
		REQUIRE( c16.get(data, sizeof(data)) == 0xC457);
	}
}

TEST_CASE("SLOW CRC8 CHECKSUMS ON SMALL DATA ARE COMPUTED CORRECTLY", "[crc8]")
{
	using namespace cpp_crc::slow;
	uint8_t data[] = {0xDE, 0xAD, 0xBE, 0xEF};
//         Algorithm       Result  Check   Poly    Init    RefIn   RefOut  XorOut
//         CRC-8           0xCA    0xF4    0x07    0x00    false   false   0x00
//         CRC-8/CDMA2000  0x77    0xDA    0x9B    0xFF    false   false   0x00
//         CRC-8/DARC      0xC0    0x15    0x39    0x00    true    true    0x00
//         CRC-8/DVB-S2    0xA5    0xBC    0xD5    0x00    false   false   0x00
//         CRC-8/EBU       0x64    0x97    0x1D    0xFF    true    true    0x00
//         CRC-8/I-CODE    0x6B    0x7E    0x1D    0xFD    false   false   0x00
//         CRC-8/ITU       0x9F    0xA1    0x07    0x00    false   false   0x55
//         CRC-8/MAXIM     0x84    0xA1    0x31    0x00    true    true    0x00
//         CRC-8/ROHC      0xC3    0xD0    0x07    0xFF    true    true    0x00
//         CRC-8/WCDMA     0xCC    0x25    0x9B    0x00    true    true    0x00
	SECTION("CRC-8           ")
	{
		crc<uint8_t> c8(0x07, 0x00, 0x00, false, false);
		REQUIRE( c8.get(data, sizeof(data)) == 0xCA);
	}
	SECTION("CRC-8/CDMA2000  ")
	{
		crc<uint8_t> c8(0x9B, 0xFF, 0x00, false, false);
		REQUIRE( c8.get(data, sizeof(data)) == 0x77);
	}
	SECTION("CRC-8/DARC      ")
	{
		crc<uint8_t> c8(0x39, 0x00, 0x00, true,  true );
		REQUIRE( c8.get(data, sizeof(data)) == 0xC0);
	}
	SECTION("CRC-8/DVB-S2    ")
	{
		crc<uint8_t> c8(0xD5, 0x00, 0x00, false, false);
		REQUIRE( c8.get(data, sizeof(data)) == 0xA5);
	}
	SECTION("CRC-8/EBU       ")
	{
		crc<uint8_t> c8(0x1D, 0xFF, 0x00, true,  true );
		REQUIRE( c8.get(data, sizeof(data)) == 0x64);
	}
	SECTION("CRC-8/I-CODE    ")
	{
		crc<uint8_t> c8(0x1D, 0xFD, 0x00, false, false);
		REQUIRE( c8.get(data, sizeof(data)) == 0x6B);
	}
	SECTION("CRC-8/ITU       ")
	{
		crc<uint8_t> c8(0x07, 0x00, 0x55, false, false);
		REQUIRE( c8.get(data, sizeof(data)) == 0x9F);
	}
	SECTION("CRC-8/MAXIM     ")
	{
		crc<uint8_t> c8(0x31, 0x00, 0x00, true,  true );
		REQUIRE( c8.get(data, sizeof(data)) == 0x84);
	}
	SECTION("CRC-8/ROHC      ")
	{
		crc<uint8_t> c8(0x07, 0xFF, 0x00, true,  true );
		REQUIRE( c8.get(data, sizeof(data)) == 0xC3);
	}
	SECTION("CRC-8/WCDMA     ")
	{
		crc<uint8_t> c8(0x9B, 0x00, 0x00, true,  true );
		REQUIRE( c8.get(data, sizeof(data)) == 0xCC);
	}
}




