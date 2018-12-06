/*
 * @Author: Lukasz
 * @Date:   05-12-2018
 * @Last Modified by:   Lukasz
 * @Last Modified time: 06-12-2018
 */

#pragma once

#include "bitop.h"
#include "table.h"
#include <array>
#include <iostream>
#include <stdint.h>

template <typename crc_t, crc_t POLY, crc_t SEED = 0xFFFF, crc_t XOR_OUT = 0, bool REF_IN = false, bool REF_OUT = false>
class crc_table
{
private:
  const crc::LookUpTable<crc_t> m_table = crc::LookUpTable<crc_t>(POLY);

protected:
  crc_t                   m_checksum = SEED;
  static constexpr size_t WIDTH      = 8 * sizeof(crc_t);

public:
  crc_table()                   = default;
  crc_table(const crc_table &)  = delete; // Disable copy constructor
  crc_table(const crc_table &&) = delete; // Disable move constructor

  const crc_t get_seed() const { return SEED; }
  const crc_t get_poly() const { return POLY; }
  void        reset(const crc_t new_seed) { m_checksum = new_seed; }
  void        reset() { m_checksum = SEED; }

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

  crc_t process_byte(unsigned char byte)
  {
    if constexpr (REF_IN)
    {
      const auto d = bitop::reverse(byte) ^ (m_checksum >> (WIDTH - 8));
      m_checksum   = m_table[d] ^ (m_checksum << 8);
    }
    else
    {
      const auto d = (byte) ^ (m_checksum >> (WIDTH - 8));
      m_checksum   = m_table[d] ^ (m_checksum << 8);
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
