/*
 * @Author: Lukasz
 * @Date:   05-12-2018
 * @Last Modified by:   Lukasz
 * @Last Modified time: 06-12-2018
 */

#pragma once

#include "bitop.h"
#include "crc_base.h"
#include "crc_lut.h"
#include <cstddef> //size_t
#include <limits>
#include <stdint.h>

namespace ccrc {

/**
 * @brief      Class for crc.
 *
 * @tparam     crc_t    Base crc type, uint32_t, uint16_t or uint8_t typically.
 * @tparam     POLY     Polynomial value to use
 * @tparam     SEED     Seed value to use
 */
template <typename crc_t, crc_t POLY,
          crc_t SEED = std::numeric_limits<crc_t>::max, crc_t XOR_OUT = 0,
          bool REF_IN = false, bool REF_OUT = false>
class crc_lut : public crc_naive<crc_t, POLY, SEED, XOR_OUT, REF_IN, REF_OUT> {
  using size_type = size_t;
  static constexpr std::size_t WIDTH = std::numeric_limits<crc_t>::digits;
  static constexpr std::size_t BYTE_WIDTH =
      std::numeric_limits<uint8_t>::digits;
  static constexpr crc_t TOP_BIT = (1 << (WIDTH - 1));

private:
  static constexpr LUT<crc_t> m_table{POLY};

protected:
public:
  crc_lut(const crc_lut &) = delete;  // Disable copy constructor
  crc_lut(const crc_lut &&) = delete; // Disable move constructor

  static constexpr crc_t checksum_byte(const uint8_t byte,
                                       const crc_t seed = SEED) {

    crc_t rc = seed;

    if constexpr (REF_IN) {
      const auto d = bit::reverse(byte) ^ (rc >> (WIDTH - BYTE_WIDTH));
      rc = m_table[d] ^ (rc << BYTE_WIDTH);
    } else {
      const auto d = (byte) ^ (rc >> (WIDTH - BYTE_WIDTH));
      rc = m_table[d] ^ (rc << BYTE_WIDTH);
    }

    return rc;
  }
};

} // namespace ccrc
