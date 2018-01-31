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
	const CRC_TYPE m_seed;
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

#endif
