/*
 * @Author: Lukasz
 * @Date:   05-12-2018
 * @Last Modified by:   Lukasz
 * @Last Modified time: 06-12-2018
 */

#pragma once

#include "bitop.h"
#include "table.h"
#include <stdint.h>

namespace ccrc {

namespace table {

template <typename crc_t, crc_t POLY, crc_t SEED = 0xFFFF, crc_t XOR_OUT = 0,
          bool REF_IN = false, bool REF_OUT = false>
class crc {
private:
  static constexpr LUT<crc_t> m_table{POLY};

protected:
  static constexpr size_t WIDTH = 8 * sizeof(crc_t);

public:
  crc() = default;
  crc(const crc &) = delete;  // Disable copy constructor
  crc(const crc &&) = delete; // Disable move constructor

  const crc_t get_seed() const { return SEED; }
  const crc_t get_poly() const { return POLY; }

  template <typename BYTE_TYPE, typename SIZE_TYPE>
  static constexpr crc_t checksum_bytes(BYTE_TYPE const *p,
                                        const SIZE_TYPE byte_count) {
    static_assert(sizeof(BYTE_TYPE) == 1, "Type passed is not compatible.");

    crc_t rc = SEED;
    for (auto bytes = byte_count; bytes--;) {
      if constexpr (REF_IN) {
        const auto d = bit::reverse(*p++) ^ (rc >> (WIDTH - 8));
        rc = m_table[d] ^ (rc << 8);
      } else {
        const auto d = (*p++) ^ (rc >> (WIDTH - 8));
        rc = m_table[d] ^ (rc << 8);
      }
    }

    if constexpr (REF_OUT) {
      return (bit::reverse(rc)) ^ XOR_OUT;
    } else {
      return rc ^ XOR_OUT;
    }
  }
};

} // namespace table
} // namespace ccrc
