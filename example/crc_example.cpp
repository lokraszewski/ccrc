/*
 * @Author: lu
 * @Date:   10-01-2018
 * @Last Modified by:   Lukasz
 * @Last Modified time: 05-12-2018
 */

#include "crc/crc.h"
#include <array>
#include <chrono>
#include <cxxopts.hpp>
#include <fstream>
#include <iostream>
#include <map>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <stdint.h>
#include <string>

static auto l_log = spdlog::stdout_color_mt("crc");

template <typename T>
void checksum_and_print_(std::string label, T &crc, const uint8_t *buffer, const size_t size)
{
  auto       start = std::chrono::steady_clock::now();
  const auto res   = crc.process_bytes(buffer, size);
  auto       end   = std::chrono::steady_clock::now();
  l_log->info("{:>16} : {:#x} : {}ns", label, res, std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
}

#define checksum_and_print(name, buffer, size) checksum_and_print_(#name, (name), buffer, size)

int checksum_all(const uint8_t *buffer, const size_t size)
{
  l_log->info("Running checksums on {} bytes", size);
  (void)buffer;

  using namespace crc::fast; // change to crc::slow if you wish.
  default32_t   default32;
  bzip2_t       bzip2;
  crc32c_t      crc32c;
  crc32d_t      crc32d;
  mpeg2_t       mpeg2;
  posix_t       posix;
  crc32q_t      crc32q;
  jamcrc_t      jamcrc;
  xfer_t        xfer;
  ccitt_t       ccitt;
  arc_t         arc;
  aug_ccitt_t   aug_ccitt;
  buypass_t     buypass;
  cdma2000_16_t cdma2000_16;
  dds_110_t     dds_110;
  dect_r_t      dect_r;
  dect_x_t      dect_x;
  dnp_t         dnp;
  en_13757_t    en_13757;
  genibus_t     genibus;
  maxim16_t     maxim16;
  mcrf4xx_t     mcrf4xx;
  riello_t      riello;
  t10_dif_t     t10_dif;
  teledisk_t    teledisk;
  tms37157_t    tms37157;
  usb_t         usb;
  crc16a_t      crc16a;
  kermit_t      kermit;
  modbus_t      modbus;
  x_25_t        x_25;
  xmodem_t      xmodem;
  default8_t    default8;
  cdma2000_8_t  cdma2000_8;
  darc_t        darc;
  dvb_s2_t      dvb_s2;
  ebu_t         ebu;
  i_code_t      i_code;
  itu_t         itu;
  maxim8_t      maxim8;
  rohc_t        rohc;
  wcdma_t       wcdma;

  checksum_and_print(default32, buffer, size);
  checksum_and_print(bzip2, buffer, size);
  checksum_and_print(crc32c, buffer, size);
  checksum_and_print(crc32d, buffer, size);
  checksum_and_print(mpeg2, buffer, size);
  checksum_and_print(posix, buffer, size);
  checksum_and_print(crc32q, buffer, size);
  checksum_and_print(jamcrc, buffer, size);
  checksum_and_print(xfer, buffer, size);
  checksum_and_print(ccitt, buffer, size);
  checksum_and_print(arc, buffer, size);
  checksum_and_print(aug_ccitt, buffer, size);
  checksum_and_print(buypass, buffer, size);
  checksum_and_print(cdma2000_16, buffer, size);
  checksum_and_print(dds_110, buffer, size);
  checksum_and_print(dect_r, buffer, size);
  checksum_and_print(dect_x, buffer, size);
  checksum_and_print(dnp, buffer, size);
  checksum_and_print(en_13757, buffer, size);
  checksum_and_print(genibus, buffer, size);
  checksum_and_print(maxim16, buffer, size);
  checksum_and_print(mcrf4xx, buffer, size);
  checksum_and_print(riello, buffer, size);
  checksum_and_print(t10_dif, buffer, size);
  checksum_and_print(teledisk, buffer, size);
  checksum_and_print(tms37157, buffer, size);
  checksum_and_print(usb, buffer, size);
  checksum_and_print(crc16a, buffer, size);
  checksum_and_print(kermit, buffer, size);
  checksum_and_print(modbus, buffer, size);
  checksum_and_print(x_25, buffer, size);
  checksum_and_print(xmodem, buffer, size);
  checksum_and_print(default8, buffer, size);
  checksum_and_print(cdma2000_8, buffer, size);
  checksum_and_print(darc, buffer, size);
  checksum_and_print(dvb_s2, buffer, size);
  checksum_and_print(ebu, buffer, size);
  checksum_and_print(i_code, buffer, size);
  checksum_and_print(itu, buffer, size);
  checksum_and_print(maxim8, buffer, size);
  checksum_and_print(rohc, buffer, size);
  checksum_and_print(wcdma, buffer, size);

  return 0;
}

int main(int argc, char **argv)
{
  static cxxopts::Options options("crc_example", "Example crc usage.");
  options.positional_help("[optional args]").show_positional_help();
  options.allow_unrecognised_options();
  options.add_options()("help", "Print help");
  options.add_options()("f,file", "File input.", cxxopts::value<std::string>());
  options.add_options()("i,input", "String input", cxxopts::value<std::string>());

  auto result            = options.parse(argc, argv);
  auto file_input_flag   = result.count("f");
  auto string_input_flag = result.count("i");

  if (result.count("help") || (!file_input_flag && !string_input_flag))
  {
    std::cout << options.help({"", "Group"}) << std::endl;
    exit(0);
  }

  if (file_input_flag)
  {
    auto &filename = result["f"].as<std::string>();
    l_log->info("Attempting to checksum file : '{}'", filename);
    std::ifstream           ifs(filename, std::ios::binary | std::ios::ate);
    std::ifstream::pos_type pos = ifs.tellg();
    std::vector<char>       result(pos);
    ifs.seekg(0, std::ios::beg);
    ifs.read(&result[0], pos);
    l_log->info("{} bytes read", result.size());
    return checksum_all((const uint8_t *)result.data(), result.size());
  }

  if (string_input_flag)
  {
    auto &user_string = result["i"].as<std::string>();
    l_log->info("Attempting to checksum string : '{}'", user_string);
    return checksum_all((const uint8_t *)user_string.c_str(), user_string.size());
  }

  return 0;
}
