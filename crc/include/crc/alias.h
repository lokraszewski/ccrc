/*
 * @Author: Lukasz
 * @Last Modified by:   Lukasz
 * @Last Modified time: 05-12-2018
 */
#pragma once
#include "basic.h"
#include "fast.h"

namespace crc
{
namespace basic
{
typedef crc_basic<uint32_t, 0x04C11DB7, 0xFFFFFFFF, 0xFFFFFFFF, true, true>   default32_t;
typedef crc_basic<uint32_t, 0x04C11DB7, 0xFFFFFFFF, 0xFFFFFFFF, false, false> bzip2_t;
typedef crc_basic<uint32_t, 0x1EDC6F41, 0xFFFFFFFF, 0xFFFFFFFF, true, true>   crc32c_t;
typedef crc_basic<uint32_t, 0xA833982B, 0xFFFFFFFF, 0xFFFFFFFF, true, true>   crc32d_t;
typedef crc_basic<uint32_t, 0x04C11DB7, 0xFFFFFFFF, 0x00000000, false, false> mpeg2_t;
typedef crc_basic<uint32_t, 0x04C11DB7, 0x00000000, 0xFFFFFFFF, false, false> posix_t;
typedef crc_basic<uint32_t, 0x814141AB, 0x00000000, 0x00000000, false, false> crc32q_t;
typedef crc_basic<uint32_t, 0x04C11DB7, 0xFFFFFFFF, 0x00000000, true, true>   jamcrc_t;
typedef crc_basic<uint32_t, 0x000000AF, 0x00000000, 0x00000000, false, false> xfer_t;
typedef crc_basic<uint16_t, 0x1021, 0xFFFF, 0x0000, false, false>             ccitt_t;
typedef crc_basic<uint16_t, 0x8005, 0x0000, 0x0000, true, true>               arc_t;
typedef crc_basic<uint16_t, 0x1021, 0x1D0F, 0x0000, false, false>             aug_ccitt_t;
typedef crc_basic<uint16_t, 0x8005, 0x0000, 0x0000, false, false>             buypass_t;
typedef crc_basic<uint16_t, 0xC867, 0xFFFF, 0x0000, false, false>             cdma2000_16_t;
typedef crc_basic<uint16_t, 0x8005, 0x800D, 0x0000, false, false>             dds_110_t;
typedef crc_basic<uint16_t, 0x0589, 0x0000, 0x0001, false, false>             dect_r_t;
typedef crc_basic<uint16_t, 0x0589, 0x0000, 0x0000, false, false>             dect_x_t;
typedef crc_basic<uint16_t, 0x3D65, 0x0000, 0xFFFF, true, true>               dnp_t;
typedef crc_basic<uint16_t, 0x3D65, 0x0000, 0xFFFF, false, false>             en_13757_t;
typedef crc_basic<uint16_t, 0x1021, 0xFFFF, 0xFFFF, false, false>             genibus_t;
typedef crc_basic<uint16_t, 0x8005, 0x0000, 0xFFFF, true, true>               maxim16_t;
typedef crc_basic<uint16_t, 0x1021, 0xFFFF, 0x0000, true, true>               mcrf4xx_t;
typedef crc_basic<uint16_t, 0x1021, 0xB2AA, 0x0000, true, true>               riello_t;
typedef crc_basic<uint16_t, 0x8BB7, 0x0000, 0x0000, false, false>             t10_dif_t;
typedef crc_basic<uint16_t, 0xA097, 0x0000, 0x0000, false, false>             teledisk_t;
typedef crc_basic<uint16_t, 0x1021, 0x89EC, 0x0000, true, true>               tms37157_t;
typedef crc_basic<uint16_t, 0x8005, 0xFFFF, 0xFFFF, true, true>               usb_t;
typedef crc_basic<uint16_t, 0x1021, 0xC6C6, 0x0000, true, true>               crc16a_t;
typedef crc_basic<uint16_t, 0x1021, 0x0000, 0x0000, true, true>               kermit_t;
typedef crc_basic<uint16_t, 0x8005, 0xFFFF, 0x0000, true, true>               modbus_t;
typedef crc_basic<uint16_t, 0x1021, 0xFFFF, 0xFFFF, true, true>               x_25_t;
typedef crc_basic<uint16_t, 0x1021, 0x0000, 0x0000, false, false>             xmodem_t;
typedef crc_basic<uint8_t, 0x07, 0x00, 0x00, false, false>                    default8_t;
typedef crc_basic<uint8_t, 0x9B, 0xFF, 0x00, false, false>                    cdma2000_8_t;
typedef crc_basic<uint8_t, 0x39, 0x00, 0x00, true, true>                      darc_t;
typedef crc_basic<uint8_t, 0xD5, 0x00, 0x00, false, false>                    dvb_s2_t;
typedef crc_basic<uint8_t, 0x1D, 0xFF, 0x00, true, true>                      ebu_t;
typedef crc_basic<uint8_t, 0x1D, 0xFD, 0x00, false, false>                    i_code_t;
typedef crc_basic<uint8_t, 0x07, 0x00, 0x55, false, false>                    itu_t;
typedef crc_basic<uint8_t, 0x31, 0x00, 0x00, true, true>                      maxim8_t;
typedef crc_basic<uint8_t, 0x07, 0xFF, 0x00, true, true>                      rohc_t;
typedef crc_basic<uint8_t, 0x9B, 0x00, 0x00, true, true>                      wcdma_t;

} // namespace basic

namespace fast
{
typedef crc_table<uint32_t, 0x04C11DB7, 0xFFFFFFFF, 0xFFFFFFFF, true, true>   default32_t;
typedef crc_table<uint32_t, 0x04C11DB7, 0xFFFFFFFF, 0xFFFFFFFF, false, false> bzip2_t;
typedef crc_table<uint32_t, 0x1EDC6F41, 0xFFFFFFFF, 0xFFFFFFFF, true, true>   crc32c_t;
typedef crc_table<uint32_t, 0xA833982B, 0xFFFFFFFF, 0xFFFFFFFF, true, true>   crc32d_t;
typedef crc_table<uint32_t, 0x04C11DB7, 0xFFFFFFFF, 0x00000000, false, false> mpeg2_t;
typedef crc_table<uint32_t, 0x04C11DB7, 0x00000000, 0xFFFFFFFF, false, false> posix_t;
typedef crc_table<uint32_t, 0x814141AB, 0x00000000, 0x00000000, false, false> crc32q_t;
typedef crc_table<uint32_t, 0x04C11DB7, 0xFFFFFFFF, 0x00000000, true, true>   jamcrc_t;
typedef crc_table<uint32_t, 0x000000AF, 0x00000000, 0x00000000, false, false> xfer_t;
typedef crc_table<uint16_t, 0x1021, 0xFFFF, 0x0000, false, false>             ccitt_t;
typedef crc_table<uint16_t, 0x8005, 0x0000, 0x0000, true, true>               arc_t;
typedef crc_table<uint16_t, 0x1021, 0x1D0F, 0x0000, false, false>             aug_ccitt_t;
typedef crc_table<uint16_t, 0x8005, 0x0000, 0x0000, false, false>             buypass_t;
typedef crc_table<uint16_t, 0xC867, 0xFFFF, 0x0000, false, false>             cdma2000_16_t;
typedef crc_table<uint16_t, 0x8005, 0x800D, 0x0000, false, false>             dds_110_t;
typedef crc_table<uint16_t, 0x0589, 0x0000, 0x0001, false, false>             dect_r_t;
typedef crc_table<uint16_t, 0x0589, 0x0000, 0x0000, false, false>             dect_x_t;
typedef crc_table<uint16_t, 0x3D65, 0x0000, 0xFFFF, true, true>               dnp_t;
typedef crc_table<uint16_t, 0x3D65, 0x0000, 0xFFFF, false, false>             en_13757_t;
typedef crc_table<uint16_t, 0x1021, 0xFFFF, 0xFFFF, false, false>             genibus_t;
typedef crc_table<uint16_t, 0x8005, 0x0000, 0xFFFF, true, true>               maxim16_t;
typedef crc_table<uint16_t, 0x1021, 0xFFFF, 0x0000, true, true>               mcrf4xx_t;
typedef crc_table<uint16_t, 0x1021, 0xB2AA, 0x0000, true, true>               riello_t;
typedef crc_table<uint16_t, 0x8BB7, 0x0000, 0x0000, false, false>             t10_dif_t;
typedef crc_table<uint16_t, 0xA097, 0x0000, 0x0000, false, false>             teledisk_t;
typedef crc_table<uint16_t, 0x1021, 0x89EC, 0x0000, true, true>               tms37157_t;
typedef crc_table<uint16_t, 0x8005, 0xFFFF, 0xFFFF, true, true>               usb_t;
typedef crc_table<uint16_t, 0x1021, 0xC6C6, 0x0000, true, true>               crc16a_t;
typedef crc_table<uint16_t, 0x1021, 0x0000, 0x0000, true, true>               kermit_t;
typedef crc_table<uint16_t, 0x8005, 0xFFFF, 0x0000, true, true>               modbus_t;
typedef crc_table<uint16_t, 0x1021, 0xFFFF, 0xFFFF, true, true>               x_25_t;
typedef crc_table<uint16_t, 0x1021, 0x0000, 0x0000, false, false>             xmodem_t;
typedef crc_table<uint8_t, 0x07, 0x00, 0x00, false, false>                    default8_t;
typedef crc_table<uint8_t, 0x9B, 0xFF, 0x00, false, false>                    cdma2000_8_t;
typedef crc_table<uint8_t, 0x39, 0x00, 0x00, true, true>                      darc_t;
typedef crc_table<uint8_t, 0xD5, 0x00, 0x00, false, false>                    dvb_s2_t;
typedef crc_table<uint8_t, 0x1D, 0xFF, 0x00, true, true>                      ebu_t;
typedef crc_table<uint8_t, 0x1D, 0xFD, 0x00, false, false>                    i_code_t;
typedef crc_table<uint8_t, 0x07, 0x00, 0x55, false, false>                    itu_t;
typedef crc_table<uint8_t, 0x31, 0x00, 0x00, true, true>                      maxim8_t;
typedef crc_table<uint8_t, 0x07, 0xFF, 0x00, true, true>                      rohc_t;
typedef crc_table<uint8_t, 0x9B, 0x00, 0x00, true, true>                      wcdma_t;
} // namespace fast
} // namespace crc
