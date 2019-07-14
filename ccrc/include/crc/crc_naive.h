/*
 * @Author: Lukasz
 * @Date:   05-12-2018
 * @Last Modified by:   Lukasz
 * @Last Modified time: 05-12-2018
 */

#pragma once

#include "bitop.h"
#include <array>
#include <iostream>
#include <limits.h>
#include <stdint.h>

namespace ccrc {

namespace naive {

template <typename crc_t, crc_t POLY, crc_t SEED = 0xFFFF, crc_t XOR_OUT = 0,
          bool REF_IN = false, bool REF_OUT = false>
class crc {
private:
protected:
  static constexpr size_t WIDTH = CHAR_BIT * sizeof(crc_t);
  static constexpr crc_t TOP_BIT = (1 << (WIDTH - 1));

public:
  crc(const crc &) = delete;  // Disable copy constructor
  crc(const crc &&) = delete; // Disable move constructor

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
    static_assert(CHAR_BIT == 8);

    crc_t rc = seed;

    if constexpr (REF_IN) {
      rc ^= (bit::reverse(byte) << (WIDTH - CHAR_BIT));
    } else {
      rc ^= (byte << (WIDTH - CHAR_BIT));
    }

    for (auto bit = CHAR_BIT; bit--;) {
      if (rc & TOP_BIT) {
        rc = (rc << 1) ^ POLY;
      } else {
        rc = rc << 1;
      }
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

} // namespace naive
} // namespace ccrc