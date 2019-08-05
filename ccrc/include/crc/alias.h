/*
 * @Author: Lukasz
 * @Last Modified by:   Lukasz
 * @Last Modified time: 05-12-2018
 */
#pragma once
#include "crc_base.h"
#include "crc_fast.h"

namespace ccrc {

namespace slow {
using crc32_default_t =
    crc_naive<uint32_t, 0x04C11DB7, 0xFFFFFFFF, 0xFFFFFFFF, true, true>;
using bzip2_t =
    crc_naive<uint32_t, 0x04C11DB7, 0xFFFFFFFF, 0xFFFFFFFF, false, false>;
using crc32c_t =
    crc_naive<uint32_t, 0x1EDC6F41, 0xFFFFFFFF, 0xFFFFFFFF, true, true>;
using crc32d_t =
    crc_naive<uint32_t, 0xA833982B, 0xFFFFFFFF, 0xFFFFFFFF, true, true>;
using mpeg2_t =
    crc_naive<uint32_t, 0x04C11DB7, 0xFFFFFFFF, 0x00000000, false, false>;
using posix_t =
    crc_naive<uint32_t, 0x04C11DB7, 0x00000000, 0xFFFFFFFF, false, false>;
using crc32q_t =
    crc_naive<uint32_t, 0x814141AB, 0x00000000, 0x00000000, false, false>;
using jamcrc_t =
    crc_naive<uint32_t, 0x04C11DB7, 0xFFFFFFFF, 0x00000000, true, true>;
using xfer_t =
    crc_naive<uint32_t, 0x000000AF, 0x00000000, 0x00000000, false, false>;
using ccitt_t = crc_naive<uint16_t, 0x1021, 0xFFFF, 0x0000, false, false>;
using arc_t = crc_naive<uint16_t, 0x8005, 0x0000, 0x0000, true, true>;
using aug_ccitt_t = crc_naive<uint16_t, 0x1021, 0x1D0F, 0x0000, false, false>;
using buypass_t = crc_naive<uint16_t, 0x8005, 0x0000, 0x0000, false, false>;
using cdma2000_16_t = crc_naive<uint16_t, 0xC867, 0xFFFF, 0x0000, false, false>;
using dds_110_t = crc_naive<uint16_t, 0x8005, 0x800D, 0x0000, false, false>;
using dect_r_t = crc_naive<uint16_t, 0x0589, 0x0000, 0x0001, false, false>;
using dect_x_t = crc_naive<uint16_t, 0x0589, 0x0000, 0x0000, false, false>;
using dnp_t = crc_naive<uint16_t, 0x3D65, 0x0000, 0xFFFF, true, true>;
using en_13757_t = crc_naive<uint16_t, 0x3D65, 0x0000, 0xFFFF, false, false>;
using genibus_t = crc_naive<uint16_t, 0x1021, 0xFFFF, 0xFFFF, false, false>;
using maxim16_t = crc_naive<uint16_t, 0x8005, 0x0000, 0xFFFF, true, true>;
using mcrf4xx_t = crc_naive<uint16_t, 0x1021, 0xFFFF, 0x0000, true, true>;
using riello_t = crc_naive<uint16_t, 0x1021, 0xB2AA, 0x0000, true, true>;
using t10_dif_t = crc_naive<uint16_t, 0x8BB7, 0x0000, 0x0000, false, false>;
using teledisk_t = crc_naive<uint16_t, 0xA097, 0x0000, 0x0000, false, false>;
using tms37157_t = crc_naive<uint16_t, 0x1021, 0x89EC, 0x0000, true, true>;
using usb_t = crc_naive<uint16_t, 0x8005, 0xFFFF, 0xFFFF, true, true>;
using crc16a_t = crc_naive<uint16_t, 0x1021, 0xC6C6, 0x0000, true, true>;
using kermit_t = crc_naive<uint16_t, 0x1021, 0x0000, 0x0000, true, true>;
using modbus_t = crc_naive<uint16_t, 0x8005, 0xFFFF, 0x0000, true, true>;
using x_25_t = crc_naive<uint16_t, 0x1021, 0xFFFF, 0xFFFF, true, true>;
using xmodem_t = crc_naive<uint16_t, 0x1021, 0x0000, 0x0000, false, false>;
using default8_t = crc_naive<uint8_t, 0x07, 0x00, 0x00, false, false>;
using cdma2000_8_t = crc_naive<uint8_t, 0x9B, 0xFF, 0x00, false, false>;
using darc_t = crc_naive<uint8_t, 0x39, 0x00, 0x00, true, true>;
using dvb_s2_t = crc_naive<uint8_t, 0xD5, 0x00, 0x00, false, false>;
using ebu_t = crc_naive<uint8_t, 0x1D, 0xFF, 0x00, true, true>;
using i_code_t = crc_naive<uint8_t, 0x1D, 0xFD, 0x00, false, false>;
using itu_t = crc_naive<uint8_t, 0x07, 0x00, 0x55, false, false>;
using maxim8_t = crc_naive<uint8_t, 0x31, 0x00, 0x00, true, true>;
using rohc_t = crc_naive<uint8_t, 0x07, 0xFF, 0x00, true, true>;
using wcdma_t = crc_naive<uint8_t, 0x9B, 0x00, 0x00, true, true>;
} // namespace slow
namespace lut {
using crc32_default_t =
    crc_lut<uint32_t, 0x04C11DB7, 0xFFFFFFFF, 0xFFFFFFFF, true, true>;
using bzip2_t =
    crc_lut<uint32_t, 0x04C11DB7, 0xFFFFFFFF, 0xFFFFFFFF, false, false>;
using crc32c_t =
    crc_lut<uint32_t, 0x1EDC6F41, 0xFFFFFFFF, 0xFFFFFFFF, true, true>;
using crc32d_t =
    crc_lut<uint32_t, 0xA833982B, 0xFFFFFFFF, 0xFFFFFFFF, true, true>;
using mpeg2_t =
    crc_lut<uint32_t, 0x04C11DB7, 0xFFFFFFFF, 0x00000000, false, false>;
using posix_t =
    crc_lut<uint32_t, 0x04C11DB7, 0x00000000, 0xFFFFFFFF, false, false>;
using crc32q_t =
    crc_lut<uint32_t, 0x814141AB, 0x00000000, 0x00000000, false, false>;
using jamcrc_t =
    crc_lut<uint32_t, 0x04C11DB7, 0xFFFFFFFF, 0x00000000, true, true>;
using xfer_t =
    crc_lut<uint32_t, 0x000000AF, 0x00000000, 0x00000000, false, false>;
using ccitt_t = crc_lut<uint16_t, 0x1021, 0xFFFF, 0x0000, false, false>;
using arc_t = crc_lut<uint16_t, 0x8005, 0x0000, 0x0000, true, true>;
using aug_ccitt_t = crc_lut<uint16_t, 0x1021, 0x1D0F, 0x0000, false, false>;
using buypass_t = crc_lut<uint16_t, 0x8005, 0x0000, 0x0000, false, false>;
using cdma2000_16_t = crc_lut<uint16_t, 0xC867, 0xFFFF, 0x0000, false, false>;
using dds_110_t = crc_lut<uint16_t, 0x8005, 0x800D, 0x0000, false, false>;
using dect_r_t = crc_lut<uint16_t, 0x0589, 0x0000, 0x0001, false, false>;
using dect_x_t = crc_lut<uint16_t, 0x0589, 0x0000, 0x0000, false, false>;
using dnp_t = crc_lut<uint16_t, 0x3D65, 0x0000, 0xFFFF, true, true>;
using en_13757_t = crc_lut<uint16_t, 0x3D65, 0x0000, 0xFFFF, false, false>;
using genibus_t = crc_lut<uint16_t, 0x1021, 0xFFFF, 0xFFFF, false, false>;
using maxim16_t = crc_lut<uint16_t, 0x8005, 0x0000, 0xFFFF, true, true>;
using mcrf4xx_t = crc_lut<uint16_t, 0x1021, 0xFFFF, 0x0000, true, true>;
using riello_t = crc_lut<uint16_t, 0x1021, 0xB2AA, 0x0000, true, true>;
using t10_dif_t = crc_lut<uint16_t, 0x8BB7, 0x0000, 0x0000, false, false>;
using teledisk_t = crc_lut<uint16_t, 0xA097, 0x0000, 0x0000, false, false>;
using tms37157_t = crc_lut<uint16_t, 0x1021, 0x89EC, 0x0000, true, true>;
using usb_t = crc_lut<uint16_t, 0x8005, 0xFFFF, 0xFFFF, true, true>;
using crc16a_t = crc_lut<uint16_t, 0x1021, 0xC6C6, 0x0000, true, true>;
using kermit_t = crc_lut<uint16_t, 0x1021, 0x0000, 0x0000, true, true>;
using modbus_t = crc_lut<uint16_t, 0x8005, 0xFFFF, 0x0000, true, true>;
using x_25_t = crc_lut<uint16_t, 0x1021, 0xFFFF, 0xFFFF, true, true>;
using xmodem_t = crc_lut<uint16_t, 0x1021, 0x0000, 0x0000, false, false>;
using default8_t = crc_lut<uint8_t, 0x07, 0x00, 0x00, false, false>;
using cdma2000_8_t = crc_lut<uint8_t, 0x9B, 0xFF, 0x00, false, false>;
using darc_t = crc_lut<uint8_t, 0x39, 0x00, 0x00, true, true>;
using dvb_s2_t = crc_lut<uint8_t, 0xD5, 0x00, 0x00, false, false>;
using ebu_t = crc_lut<uint8_t, 0x1D, 0xFF, 0x00, true, true>;
using i_code_t = crc_lut<uint8_t, 0x1D, 0xFD, 0x00, false, false>;
using itu_t = crc_lut<uint8_t, 0x07, 0x00, 0x55, false, false>;
using maxim8_t = crc_lut<uint8_t, 0x31, 0x00, 0x00, true, true>;
using rohc_t = crc_lut<uint8_t, 0x07, 0xFF, 0x00, true, true>;
using wcdma_t = crc_lut<uint8_t, 0x9B, 0x00, 0x00, true, true>;

} // namespace lut
} // namespace ccrc
