/*
* @Author: lu
* @Date:   10-01-2018
* @Last Modified by:   lu
* @Last Modified time: 12-01-2018
*/

#include <stdint.h>
#include <iostream>
#include <array>

#include "bitop.hpp"

/*

	- IDEA 1: Make this entire shit static. So it could be used in the following way:


		crc::crc<uint16_t> crc16(0x8005, 0x0000); // Create a crc16 instance.

		uint8_t some_data[10212];

		auto cs = crc16::get(some_data, sizeof some_data);
 */
#ifndef _CPP_CEC_H_
#define _CPP_CEC_H_ 0

namespace cpp_crc
{

namespace slow
{
template<typename CRC_TYPE>
class crc
{
private:

protected:
	const CRC_TYPE m_poly;
	const CRC_TYPE m_seed; /* this stores the seed that the class was initlized with. */
	const CRC_TYPE m_xor;

	const bool m_ref_in;
	const bool m_ref_out;
	const size_t WIDTH;
	const CRC_TYPE TOP_BIT;

public:
	crc(const CRC_TYPE poly, const CRC_TYPE seed = 0, const CRC_TYPE XorOut = 0, const bool RefIn = false,  const bool RefOut = false) :
		m_poly(poly),
		m_seed(seed),
		m_xor(XorOut),
		m_ref_in(RefIn),
		m_ref_out(RefOut),
		WIDTH(8 * sizeof(CRC_TYPE)),
		TOP_BIT((1 << (WIDTH - 1)))
	{
		// std::cout << " PARAM " << std::hex
		// << "m_poly : 0x" << m_poly
		// << "m_seed : 0x" << m_seed
		// << "m_xor : 0x" << m_xor
		// << "m_ref_in : 0x" << m_ref_in
		// << "m_ref_out : 0x" << m_ref_out
		// << "WIDTH : 0x" << WIDTH
		// << "TOP_BIT : 0x" << TOP_BIT
		// << std::endl;
	}

	const CRC_TYPE get_seed() const
	{
		return m_seed;
	}

	const CRC_TYPE get_poly() const
	{
		return m_poly;
	}

	CRC_TYPE get(uint8_t *data, uint32_t len)
	{
		return get(data, len, m_seed);
	}

	CRC_TYPE get(uint8_t *data, uint32_t len, const CRC_TYPE seed)
	{
		CRC_TYPE crc = seed;

		// std::cout << std::hex << "0x" << unsigned(crc) << " ";

		while (len--)
		{
			if(m_ref_in)
			{
				crc ^= (bitop::reverse(*data++) << (WIDTH - 8));
			}
			else
			{
				crc ^= (*data++ << (WIDTH - 8));
			}


			for (auto bit = 8; bit--;)
			{
				if (crc & TOP_BIT)
				{
					crc = (crc << 1) ^ m_poly;
				}
				else
				{
					crc = crc << 1;
				}
			}

			// std::cout << std::hex << "0x" << unsigned(crc) << " ";
		}

		if(m_ref_out)
		{
			return (bitop::reverse(crc)) ^ m_xor;
		}
		else
		{
			return crc ^ m_xor;
		}
	}
};

}

namespace fast
{

}

}

/* Usage ::



	crc::get<>




 */



#endif
