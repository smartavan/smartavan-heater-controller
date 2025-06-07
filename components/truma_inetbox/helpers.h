#pragma once

#include "TrumaEnums.h"
#include "TrumaEnumsAlde.h"
#include "esphome/core/helpers.h"

namespace esphome {
namespace truma_inetbox {
// 1. byte is service identifier and to be ignored.
// 5. byte is (max) length of StatusFrame. 11 + value = total max length of status frame. 
//   - Truma always x1E (DEC 30)
//   - Alde uses this field
// Last three bytes can be `xFF` or `x00` (see <https://github.com/Fabian-Schmidt/esphome-truma_inetbox/issues/25>).
const std::array<uint8_t, 11> truma_message_header = {0x00, 0x00, 0x1F, 0x00, 0x1E, 0x00,
                                                       0x00, 0x22, 0xFF, 0xFF, 0xFF};
uint8_t addr_parity(const uint8_t pid);
uint8_t data_checksum(const uint8_t *message, uint8_t length, uint16_t sum);
float temp_code_to_decimal(u_int16_t val, float zero = NAN);
float temp_code_to_decimal(TargetTemp val, float zero = NAN);
TargetTemp decimal_to_temp(uint8_t val);
TargetTemp decimal_to_temp(float val);
TargetTemp decimal_to_room_temp(uint8_t val);
TargetTemp decimal_to_room_temp(float val);
TargetTemp decimal_to_aircon_manual_temp(uint8_t val);
TargetTemp decimal_to_aircon_manual_temp(float val);
TargetTemp decimal_to_aircon_auto_temp(uint8_t val);
TargetTemp decimal_to_aircon_auto_temp(float val);
TargetTemp decimal_to_water_temp(uint8_t val);
TargetTemp decimal_to_water_temp(float val);
const std::string operating_status_to_str(OperatingStatus val);
ElectricPowerLevel decimal_to_el_power_level(u_int16_t val);

}  // namespace truma_inetbox
}  // namespace esphome
