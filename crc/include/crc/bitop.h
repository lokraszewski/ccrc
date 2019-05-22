#pragma once

#include <stdint.h>

namespace bit {

template <class T> T reverse(T n) {
  const auto BITS = (sizeof(T) * 8);
  T x = 0;

  for (auto i = BITS; i--;) {
    x |= (n & 1) << i;
    n >>= 1;
  }

  return x;
};

/* Add specializations here for super fast reverse. */
template <> uint32_t reverse(uint32_t n) {
  n = ((n >> 1) & 0x55555555) | ((n << 1) & 0xaaaaaaaa);
  n = ((n >> 2) & 0x33333333) | ((n << 2) & 0xcccccccc);
  n = ((n >> 4) & 0x0f0f0f0f) | ((n << 4) & 0xf0f0f0f0);
  n = ((n >> 8) & 0x00ff00ff) | ((n << 8) & 0xff00ff00);
  n = ((n >> 16) & 0x0000ffff) | ((n << 16) & 0xffff0000);
  return n;
}

template <> uint16_t reverse(uint16_t n) {
  n = ((n >> 1) & 0x5555) | ((n << 1) & 0xaaaa);
  n = ((n >> 2) & 0x3333) | ((n << 2) & 0xcccc);
  n = ((n >> 4) & 0x0f0f) | ((n << 4) & 0xf0f0);
  n = ((n >> 8) & 0x00ff) | ((n << 8) & 0xff00);
  return n;
}

template <> uint8_t reverse(uint8_t n) {
  n = ((n >> 1) & 0x55) | ((n << 1) & 0xaa);
  n = ((n >> 2) & 0x33) | ((n << 2) & 0xcc);
  n = ((n >> 4) & 0x0f) | ((n << 4) & 0xf0);
  return n;
}
} // namespace bit
