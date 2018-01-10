/*
* @Author: lu
* @Date:   10-01-2018
* @Last Modified by:   lu
* @Last Modified time: 10-01-2018
*/

#include <stdint.h>
#include <iostream>
#include <array>

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
	const uint TOP_BIT;
	const uint WIDTH;

public:
	crc(const CRC_TYPE poly, const CRC_TYPE seed = 0) : m_poly(poly), m_seed(seed), WIDTH(8 * sizeof(CRC_TYPE)), TOP_BIT((1 << (WIDTH - 1)))
	{
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

		/*
		 * Perform modulo-2 division, a byte at a time.
		 */
		// for (byte = 0; byte < nBytes; ++byte)
		while(len--)
		{
			/*
			 * Bring the next byte into the crc.
			 */
			crc ^= (*data++ << (WIDTH - 8));

			/*
			 * Perform modulo-2 division, a bit at a time.
			 */
			for (auto bit = 8; bit > 0; --bit)
			{
				/*
				 * Try to divide the current data bit.
				 */
				if (crc & TOP_BIT)
				{
					crc = (crc << 1) ^ m_poly;
				}
				else
				{
					crc <<= 1;
				}
			}
		}

		/*
		 * The final crc is the CRC result.
		 */
		return crc;
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
