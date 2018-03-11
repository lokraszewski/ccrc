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
	crc(const CRC_TYPE poly,
		const CRC_TYPE seed = 0,
		const CRC_TYPE XorOut = 0,
		const bool RefIn = false,
		const bool RefOut = false) :
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
			if (m_ref_in)
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

		if (m_ref_out)
		{
			return (bitop::reverse(crc)) ^ m_xor;
		}
		else
		{
			return crc ^ m_xor;
		}
	}
};

} /* slow */

namespace fast
{
template<typename CRC_TYPE>
class crc
{
private:
	constexpr std::array<CRC_TYPE, 0x100> init_table(void)
	{
        std::array<CRC_TYPE, 0x100> r;

		for (auto d = 0; d < 0x100; ++d)
     	{
			/*
			 * Start with the dividend followed by zeros.
			 */
			CRC_TYPE rem = d << (WIDTH - 8);

			/*
			 * Perform modulo-2 division, a bit at a time.
			 */
			for (auto bit = 8; bit--;)
			{
				/*
				 * Try to divide the current data bit.
				 */
				if (rem & TOP_BIT)
				{
					rem = (rem << 1) ^ m_poly;
				}
				else
				{
					rem = (rem << 1);
				}
			}

			/*
			 * Store the result into the table.
			 */
			r[d] = rem;
		}

        return r;
	}
protected:
	const CRC_TYPE m_poly;
	const CRC_TYPE m_seed;
	const CRC_TYPE m_xor;

	const bool m_ref_in;
	const bool m_ref_out;
	const size_t WIDTH;
	const CRC_TYPE TOP_BIT;

	const std::array<CRC_TYPE, 0x100> m_table;

public:
	crc(const CRC_TYPE poly,
		const CRC_TYPE seed = 0,
		const CRC_TYPE XorOut = 0,
		const bool RefIn = false,
		const bool RefOut = false) :
		m_poly(poly),
		m_seed(seed),
		m_xor(XorOut),
		m_ref_in(RefIn),
		m_ref_out(RefOut),
		WIDTH(8 * sizeof(CRC_TYPE)),
		TOP_BIT((1 << (WIDTH - 1))),
		m_table(init_table())
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
			if (m_ref_in)
			{
				const auto d = bitop::reverse(*data++) ^ (crc >> (WIDTH - 8));
				crc = m_table[d] ^ (crc << 8);
			}
			else
			{
				const auto d = (*data++) ^ (crc >> (WIDTH - 8));
				crc = m_table[d] ^ (crc << 8);
			}
		}

		if (m_ref_out)
		{
			return (bitop::reverse(crc)) ^ m_xor;
		}
		else
		{
			return crc ^ m_xor;
		}
	}
};
} /*fast*/

} /*cpp_crc*/

#endif
