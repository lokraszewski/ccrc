/*
 * @Author: Lukasz
 * @Date:   05-12-2018
 * @Last Modified by:   Lukasz
 * @Last Modified time: 06-12-2018
 */

#pragma once

#include "bitop.h"
#include <cstddef> //size_t
#include <iostream>
#include <limits>
#include <stdint.h>
#include <type_traits>

namespace ccrc {

/**
 * @brief      Class for crc.
 *
 * @tparam     crc_t    Base crc type, uint32_t, uint16_t or uint8_t typically.
 * @tparam     POLY     Polynomial value to use
 * @tparam     SEED     Seed value to use
 * @tparam     XOR_OUT  { description }
 * @tparam     REF_IN   { description }
 * @tparam     REF_OUT  { description }
 *
 * @details    { detailed_item_description }
 */
template <typename crc_t, crc_t POLY,
          crc_t SEED = std::numeric_limits<crc_t>::max, crc_t XOR_OUT = 0,
          bool REF_IN = false, bool REF_OUT = false>
class crc_naive {
  using size_type = size_t;
  static constexpr std::size_t WIDTH = std::numeric_limits<crc_t>::digits;
  static constexpr std::size_t BYTE_WIDTH =
      std::numeric_limits<uint8_t>::digits;
  static constexpr crc_t TOP_BIT = (1 << (WIDTH - 1));

protected:
public:
  crc_naive(const crc_naive &) = delete;  // Disable copy constructor
  crc_naive(const crc_naive &&) = delete; // Disable move constructor

  /**
   * @brief      Checksum for iterable byte containers (such as array<uint8_t>)
   *
   * @param[in]  data                Container of bytes
   * @param[in]  seed                The seed
   *
   * @tparam     iterable_byte_type  Must be forward iterable type
   *
   * @return     crc
   *
   */
  template <typename iterable_byte_type>
  static constexpr crc_t checksum(iterable_byte_type data,
                                  const crc_t seed = SEED) {
    crc_t rc = seed;

    for (auto &byte : data)
      rc = checksum_byte(byte, rc);

    return out_value(rc);
  }

  /**
   * @brief      Checksum for iterable types which may require conversions.
   *
   * @param[in]  data           Container of data which is iterable
   * @param[in]  to_bytes       Lmabda function to convert each item from data
   *                            to bytes
   * @param[in]  seed           The seed
   *
   * @tparam     iterable_type  Must be forward iterable type
   * @tparam     lambda         Creates iterable byte container
   *
   * @return     crc
   *
   * @details    The user can specify a custom function to turn their big type
   *             to byte iterator
   */
  template <typename iterable_type, typename lambda>
  static constexpr crc_t checksum(iterable_type data, lambda to_bytes,
                                  const crc_t seed = SEED) {
    crc_t rc = seed;

    for (auto &item : data)
      for (auto &byte : to_bytes(item))
        rc = checksum_byte(byte, rc);

    return out_value(rc);
  }

  /**
   * @brief      Checksum for pointer + sz types
   *
   * @param[in]  ptr               The pointer
   * @param[in]  sz                The size
   * @param[in]  seed              The seed
   *
   * @tparam     raw_pointer_type  Must be a byte pointer such as uint8_t*.
   *
   * @return     crc
   *
   * @details    Ideally we would take any void* and cast it but that is not
   *             compatible with constexpr
   */
  template <typename raw_pointer_type>
  static constexpr crc_t checksum(raw_pointer_type ptr, std::size_t sz,
                                  const crc_t seed = SEED) {
    crc_t rc = seed;

    while (sz--) {
      rc = checksum_byte(*ptr, rc);
      ++ptr;
    }

    return out_value(rc);
  }

  /**
   * @brief      Calculates the CRC of a single byte
   *
   * @param[in]  byte  The byte
   * @param[in]  seed  The seed
   *
   * @return     CRC
   *
   */
  static constexpr crc_t checksum_byte(const uint8_t byte,
                                       const crc_t seed = SEED) {

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

  /**
   * @brief      Gets the out value
   *
   * @param[in]  crc   The crc
   *
   * @return     Final CRC
   *
   */
  static constexpr crc_t out_value(const crc_t crc = SEED) {
    if constexpr (REF_OUT) {
      return (bit::reverse(crc)) ^ XOR_OUT;
    } else {
      return crc ^ XOR_OUT;
    }
  }
};

} // namespace ccrc
