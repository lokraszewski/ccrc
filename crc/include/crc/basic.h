/*
 * @Author: Lukasz
 * @Date:   05-12-2018
 * @Last Modified by:   Lukasz
 * @Last Modified time: 05-12-2018
 */

#pragma once

#include <array>
#include <iostream>
#include <stdint.h>

#include "bitop.h"

template <typename crc_t, crc_t POLY, crc_t SEED = 0xFFFF, crc_t XOR_OUT = 0, bool REF_IN = false, bool REF_OUT = false>
class crc_basic
{
private:
  crc_t m_checksum;

protected:
  static constexpr size_t WIDTH   = 8 * sizeof(crc_t);
  static constexpr crc_t  TOP_BIT = (1 << (WIDTH - 1));

public:
  crc_basic() : m_checksum(SEED) {}

  const crc_t checksum() const noexcept
  {
    if constexpr (REF_OUT)
    {
      return (bitop::reverse(m_checksum)) ^ XOR_OUT;
    }
    else
    {
      return m_checksum ^ XOR_OUT;
    }
  }

  const crc_t get_seed() const { return SEED; }
  const crc_t get_poly() const { return POLY; }
  void        reset(const crc_t new_seed) { m_checksum = new_seed; }
  void        reset() { m_checksum = SEED; }

  crc_t process_byte(unsigned char byte)
  {
    if constexpr (REF_IN)
    {
      m_checksum ^= (bitop::reverse(byte) << (WIDTH - 8));
    }
    else
    {
      m_checksum ^= (byte << (WIDTH - 8));
    }

    for (auto bit = 8; bit--;)
    {
      if (m_checksum & TOP_BIT)
      {
        m_checksum = (m_checksum << 1) ^ POLY;
      }
      else
      {
        m_checksum = m_checksum << 1;
      }
    }

    return checksum();
  }

  crc_t process_block(void const *bytes_begin, void const *bytes_end)
  {
    const uint8_t *p_begin = reinterpret_cast<const uint8_t *>(bytes_begin);
    const uint8_t *p_end   = reinterpret_cast<const uint8_t *>(bytes_end);

    while (p_begin != p_end)
    {
      (void)process_byte(*p_begin++);
    }
    return checksum();
  }

  crc_t process_bytes(void const *buffer, const std::size_t byte_count)
  {
    const uint8_t *p = reinterpret_cast<const uint8_t *>(buffer);

    for (auto bytes = byte_count; bytes--;)
    {
      (void)process_byte(*p++);
    }

    return checksum();
  }
};
