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

//Switch namespace if you want to use a different approach.
// using namespace ccrc::base; 
using namespace ccrc::fast;

static auto l_log = spdlog::stdout_color_mt("crc");
using my_crc = crc<uint16_t, 0xDEAD, 0xBEEF>;
/**
 * @brief      Macro print the checksum and give it a type name because I am lazy.
 */
#define EXAMPLE_HELPER(type, data)                                             \
  do {                                                                         \
    const auto r = type::checksum(data);                                       \
    l_log->info("{:>16} : {:#x}", #type, r);                                   \
  } while (0)

template <typename container> int checksum_all(container buffer) {
  EXAMPLE_HELPER(my_crc, buffer);
  EXAMPLE_HELPER(crc32_default_t, buffer);
  EXAMPLE_HELPER(bzip2_t, buffer);
  EXAMPLE_HELPER(crc32c_t, buffer);
  EXAMPLE_HELPER(crc32d_t, buffer);
  EXAMPLE_HELPER(mpeg2_t, buffer);
  EXAMPLE_HELPER(posix_t, buffer);
  EXAMPLE_HELPER(crc32q_t, buffer);
  EXAMPLE_HELPER(jamcrc_t, buffer);
  EXAMPLE_HELPER(xfer_t, buffer);
  EXAMPLE_HELPER(ccitt_t, buffer);
  EXAMPLE_HELPER(arc_t, buffer);
  EXAMPLE_HELPER(aug_ccitt_t, buffer);
  EXAMPLE_HELPER(buypass_t, buffer);
  EXAMPLE_HELPER(cdma2000_16_t, buffer);
  EXAMPLE_HELPER(dds_110_t, buffer);
  EXAMPLE_HELPER(dect_r_t, buffer);
  EXAMPLE_HELPER(dect_x_t, buffer);
  EXAMPLE_HELPER(dnp_t, buffer);
  EXAMPLE_HELPER(en_13757_t, buffer);
  EXAMPLE_HELPER(genibus_t, buffer);
  EXAMPLE_HELPER(maxim16_t, buffer);
  EXAMPLE_HELPER(mcrf4xx_t, buffer);
  EXAMPLE_HELPER(riello_t, buffer);
  EXAMPLE_HELPER(t10_dif_t, buffer);
  EXAMPLE_HELPER(teledisk_t, buffer);
  EXAMPLE_HELPER(tms37157_t, buffer);
  EXAMPLE_HELPER(usb_t, buffer);
  EXAMPLE_HELPER(crc16a_t, buffer);
  EXAMPLE_HELPER(kermit_t, buffer);
  EXAMPLE_HELPER(modbus_t, buffer);
  EXAMPLE_HELPER(x_25_t, buffer);
  EXAMPLE_HELPER(xmodem_t, buffer);
  EXAMPLE_HELPER(default8_t, buffer);
  EXAMPLE_HELPER(cdma2000_8_t, buffer);
  EXAMPLE_HELPER(darc_t, buffer);
  EXAMPLE_HELPER(dvb_s2_t, buffer);
  EXAMPLE_HELPER(ebu_t, buffer);
  EXAMPLE_HELPER(i_code_t, buffer);
  EXAMPLE_HELPER(itu_t, buffer);
  EXAMPLE_HELPER(maxim8_t, buffer);
  EXAMPLE_HELPER(rohc_t, buffer);
  EXAMPLE_HELPER(wcdma_t, buffer);

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
  }else  if (file_input_flag) {
    auto &filename = result["f"].as<std::string>();
    l_log->info("Attempting to checksum file : '{}'", filename);
    std::ifstream ifs(filename, std::ios::binary | std::ios::ate);
    std::ifstream::pos_type pos = ifs.tellg();
    std::vector<char> result(pos);
    ifs.seekg(0, std::ios::beg);
    ifs.read(&result[0], pos);
    l_log->info("{} bytes read", result.size());
    return checksum_all(result);
  }else if (string_input_flag) {
    auto &user_string = result["i"].as<std::string>();
    l_log->info("Attempting to checksum string : '{}'", user_string);
    return checksum_all(user_string);
  }

  return 0;
}
