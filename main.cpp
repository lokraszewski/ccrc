/*
* @Author: lu
* @Date:   10-01-2018
* @Last Modified by:   lu
* @Last Modified time: 10-01-2018
*/

#include <iostream>
#include <string>
#include <array>
#include <stdint.h>

#include "cpp-crc.h"


int main(int argc, char *argv[]){

	using namespace cpp_crc::slow;

    crc<uint16_t> c16(0x8005, 0x800D);
    crc<uint32_t> c32(0x04C11DB7, 0xFFFFFFFF);


    std::array<uint8_t, 4> some_data = {0xDE, 0xAD, 0xBE, 0xEF};



    // for (auto d : some_data)
        // std::cout << static_cast<int>(d) << std::endl;


    auto check16 = c16.get((uint8_t*)&some_data[0], some_data.size());
    auto check32 = c32.get((uint8_t*)&some_data[0], some_data.size());

    std::cout << std::hex;
    std::cout << "CEHCKSUM16 : " << check16 << " EXPECT : 0x96F3" << std::endl;
    std::cout << "CEHCKSUM32 : " << check32 << std::endl;


   return 0;
}
