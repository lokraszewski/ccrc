/*
 * @Author: Lukasz
 * @Date:   05-12-2018
 * @Last Modified by:   Lukasz
 * @Last Modified time: 06-12-2018
 */

#pragma once

#include "bitop.h"
#include <cstddef> //size_t
#include <stdint.h>

namespace ccrc {

namespace lut {

/**
 * @author     lokraszewski
 * @date       06-Dec-2018
 * @brief      Class for look up table.
 *
 * @tparam     T     Value type, uint8_t, uint16_t or uint32_t
 *
 * @details    constexpr constructable.
 */
template <typename T> class LUT {
  /// 256 bytes, there are no undefined entries for byte input
  static constexpr auto SIZE = 0x100;

public:
  constexpr LUT(const T poly) : m_values() {

    constexpr auto width = 8 * sizeof(T);
    constexpr auto top_bit = (1 << (width - 1));
    constexpr auto shift_places = width - 8;

    for (auto d = 0; d < SIZE; ++d) {
      T rem = d << shift_places;
      for (auto bit = 8; bit--;) {
        if (rem & top_bit) {
          rem = (rem << 1) ^ poly;
        } else {
          rem = (rem << 1);
        }
      }
      m_values[d] = rem;
    }
  }

  constexpr T operator[](const uint8_t i) const { return m_values[i]; }

private:
  T m_values[SIZE];
};

template <typename crc_t, crc_t POLY, crc_t SEED = 0xFFFF, crc_t XOR_OUT = 0,
          bool REF_IN = false, bool REF_OUT = false>
class crc {
private:
  static constexpr LUT<crc_t> m_table{POLY};

protected:
  static constexpr std::size_t WIDTH = CHAR_BIT * sizeof(crc_t);

public:
  crc(const crc &) = delete;  // Disable copy constructor
  crc(const crc &&) = delete; // Disable move constructor

  /**
   * @brief      Checksums raw memory. Takes a pointer type
   *
   * @param      ptr    The pointer to some memory
   * @param[in]  sz     Size in bytes.
   * @param[in]  seed   The seed value
   *
   * @tparam     ptr_t  Pointer type (generic)
   * @tparam     sz_t   size type (generic)
   *
   * @return     crc
   *
   */
  template <typename byte_t, typename sz_t>
  static constexpr crc_t checksum_memory(byte_t const *ptr, const sz_t sz,
                                         const crc_t seed = SEED) {
    static_assert(sizeof(byte_t) == 1, "Type passed is not compatible.");
    crc_t rc = seed;
    for (auto count = sz; count--;) {
      rc = checksum_byte(*ptr++, rc);
    }

    return out_value(rc);
  }

  template <typename byte_t>
  static constexpr crc_t checksum_byte(const byte_t byte,
                                       const crc_t seed = SEED) {
    static_assert(sizeof(byte_t) == 1, "Type passed is not compatible.");

    crc_t rc = seed;

    if constexpr (REF_IN) {
      const auto d = bit::reverse(byte) ^ (rc >> (WIDTH - 8));
      rc = m_table[d] ^ (rc << 8);
    } else {
      const auto d = (byte) ^ (rc >> (WIDTH - 8));
      rc = m_table[d] ^ (rc << 8);
    }

    return rc;
  }

  static constexpr crc_t out_value(const crc_t seed = SEED) {
    if constexpr (REF_OUT) {
      return (bit::reverse(seed)) ^ XOR_OUT;
    } else {
      return seed ^ XOR_OUT;
    }
  }
};

} // namespace lut
} // namespace ccrc
