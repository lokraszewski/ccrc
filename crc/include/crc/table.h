/*
 * @Author: Lukasz
 * @Date:   06-12-2018
 * @Last Modified by:   Lukasz
 * @Last Modified time: 06-12-2018
 */

#pragma once

#include <stdint.h>

namespace ccrc {

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
} // namespace ccrc
