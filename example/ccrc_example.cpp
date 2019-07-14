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

using namespace ccrc::lut;

template <typename T> struct TypeName { static const char *name; };
template <typename T> const char *TypeName<T>::name = "unknown";
template <> const char *TypeName<crc32_default_t>::name = "crc32_default_t";
template <> const char *TypeName<bzip2_t>::name = "bzip2_t";
template <> const char *TypeName<crc32c_t>::name = "crc32c_t";
template <> const char *TypeName<crc32d_t>::name = "crc32d_t";
template <> const char *TypeName<mpeg2_t>::name = "mpeg2_t";
template <> const char *TypeName<posix_t>::name = "posix_t";
template <> const char *TypeName<crc32q_t>::name = "crc32q_t";
template <> const char *TypeName<jamcrc_t>::name = "jamcrc_t";
template <> const char *TypeName<xfer_t>::name = "xfer_t";
template <> const char *TypeName<ccitt_t>::name = "ccitt_t";
template <> const char *TypeName<arc_t>::name = "arc_t";
template <> const char *TypeName<aug_ccitt_t>::name = "aug_ccitt_t";
template <> const char *TypeName<buypass_t>::name = "buypass_t";
template <> const char *TypeName<cdma2000_16_t>::name = "cdma2000_16_t";
template <> const char *TypeName<dds_110_t>::name = "dds_110_t";
template <> const char *TypeName<dect_r_t>::name = "dect_r_t";
template <> const char *TypeName<dect_x_t>::name = "dect_x_t";
template <> const char *TypeName<dnp_t>::name = "dnp_t";
template <> const char *TypeName<en_13757_t>::name = "en_13757_t";
template <> const char *TypeName<genibus_t>::name = "genibus_t";
template <> const char *TypeName<maxim16_t>::name = "maxim16_t";
template <> const char *TypeName<mcrf4xx_t>::name = "mcrf4xx_t";
template <> const char *TypeName<riello_t>::name = "riello_t";
template <> const char *TypeName<t10_dif_t>::name = "t10_dif_t";
template <> const char *TypeName<teledisk_t>::name = "teledisk_t";
template <> const char *TypeName<tms37157_t>::name = "tms37157_t";
template <> const char *TypeName<usb_t>::name = "usb_t";
template <> const char *TypeName<crc16a_t>::name = "crc16a_t";
template <> const char *TypeName<kermit_t>::name = "kermit_t";
template <> const char *TypeName<modbus_t>::name = "modbus_t";
template <> const char *TypeName<x_25_t>::name = "x_25_t";
template <> const char *TypeName<xmodem_t>::name = "xmodem_t";
template <> const char *TypeName<default8_t>::name = "default8_t";
template <> const char *TypeName<cdma2000_8_t>::name = "cdma2000_8_t";
template <> const char *TypeName<darc_t>::name = "darc_t";
template <> const char *TypeName<dvb_s2_t>::name = "dvb_s2_t";
template <> const char *TypeName<ebu_t>::name = "ebu_t";
template <> const char *TypeName<i_code_t>::name = "i_code_t";
template <> const char *TypeName<itu_t>::name = "itu_t";
template <> const char *TypeName<maxim8_t>::name = "maxim8_t";
template <> const char *TypeName<rohc_t>::name = "rohc_t";
template <> const char *TypeName<wcdma_t>::name = "wcdma_t";

static auto l_log = spdlog::stdout_color_mt("crc");

template <typename crc_t>
void checksum_and_print(const uint8_t *buffer, const size_t size) {

  const auto res = crc_t::checksum_memory(buffer, size);
  l_log->info("{:>16} : {:#x}", TypeName<crc_t>::name, res);
}

int checksum_all(const uint8_t *buffer, const size_t size) {
  l_log->info("Running checksums on {} bytes", size);
  checksum_and_print<crc32_default_t>(buffer, size);
  checksum_and_print<bzip2_t>(buffer, size);
  checksum_and_print<crc32c_t>(buffer, size);
  checksum_and_print<crc32d_t>(buffer, size);
  checksum_and_print<mpeg2_t>(buffer, size);
  checksum_and_print<posix_t>(buffer, size);
  checksum_and_print<crc32q_t>(buffer, size);
  checksum_and_print<jamcrc_t>(buffer, size);
  checksum_and_print<xfer_t>(buffer, size);
  checksum_and_print<ccitt_t>(buffer, size);
  checksum_and_print<arc_t>(buffer, size);
  checksum_and_print<aug_ccitt_t>(buffer, size);
  checksum_and_print<buypass_t>(buffer, size);
  checksum_and_print<cdma2000_16_t>(buffer, size);
  checksum_and_print<dds_110_t>(buffer, size);
  checksum_and_print<dect_r_t>(buffer, size);
  checksum_and_print<dect_x_t>(buffer, size);
  checksum_and_print<dnp_t>(buffer, size);
  checksum_and_print<en_13757_t>(buffer, size);
  checksum_and_print<genibus_t>(buffer, size);
  checksum_and_print<maxim16_t>(buffer, size);
  checksum_and_print<mcrf4xx_t>(buffer, size);
  checksum_and_print<riello_t>(buffer, size);
  checksum_and_print<t10_dif_t>(buffer, size);
  checksum_and_print<teledisk_t>(buffer, size);
  checksum_and_print<tms37157_t>(buffer, size);
  checksum_and_print<usb_t>(buffer, size);
  checksum_and_print<crc16a_t>(buffer, size);
  checksum_and_print<kermit_t>(buffer, size);
  checksum_and_print<modbus_t>(buffer, size);
  checksum_and_print<x_25_t>(buffer, size);
  checksum_and_print<xmodem_t>(buffer, size);
  checksum_and_print<default8_t>(buffer, size);
  checksum_and_print<cdma2000_8_t>(buffer, size);
  checksum_and_print<darc_t>(buffer, size);
  checksum_and_print<dvb_s2_t>(buffer, size);
  checksum_and_print<ebu_t>(buffer, size);
  checksum_and_print<i_code_t>(buffer, size);
  checksum_and_print<itu_t>(buffer, size);
  checksum_and_print<maxim8_t>(buffer, size);
  checksum_and_print<rohc_t>(buffer, size);
  checksum_and_print<wcdma_t>(buffer, size);

  return 0;
}

int main(int argc, char **argv) {
  static cxxopts::Options options("crc_example", "Example crc usage.");
  options.positional_help("[optional args]").show_positional_help();
  options.allow_unrecognised_options();
  options.add_options()("help", "Print help");
  options.add_options()("f,file", "File input.", cxxopts::value<std::string>());
  options.add_options()("i,input", "String input",
                        cxxopts::value<std::string>());

  auto result = options.parse(argc, argv);
  auto file_input_flag = result.count("f");
  auto string_input_flag = result.count("i");

  if (result.count("help") || (!file_input_flag && !string_input_flag)) {
    std::cout << options.help({"", "Group"}) << std::endl;
    exit(0);
  }

  if (file_input_flag) {
    auto &filename = result["f"].as<std::string>();
    l_log->info("Attempting to checksum file : '{}'", filename);
    std::ifstream ifs(filename, std::ios::binary | std::ios::ate);
    std::ifstream::pos_type pos = ifs.tellg();
    std::vector<char> result(pos);
    ifs.seekg(0, std::ios::beg);
    ifs.read(&result[0], pos);
    l_log->info("{} bytes read", result.size());
    return checksum_all((const uint8_t *)result.data(), result.size());
  }

  if (string_input_flag) {
    auto &user_string = result["i"].as<std::string>();
    l_log->info("Attempting to checksum string : '{}'", user_string);
    return checksum_all((const uint8_t *)user_string.c_str(),
                        user_string.size());
  }

  return 0;
}
