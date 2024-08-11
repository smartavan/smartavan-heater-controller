#pragma once

#include "TrumaEnums.h"
#include "TrumaEnumsAlde.h"

namespace esphome {
namespace truma_inetbox {

// Length 14 (0x0E) - MSG x0B
struct StatusFrameAldeDevice {  // NOLINT(altera-struct-pack-align)
  u_int8_t device_count;
  u_int8_t device_id;
  TRUMA_DEVICE_STATE state;
  // 0x00
  u_int8_t unknown_1;
  u_int16_t hardware_revision_major;
  u_int8_t hardware_revision_minor;
  // `software_revision[0].software_revision[1].software_revision[2]`
  // software_revision[0] -> TRUMA_DEVICE
  u_int8_t software_revision[3];
  // 0xAD, 0x0B on CPplus with Combi4 or 0x66 on CPplus with Vario Heat Comfort ohne E
  // 0x00 on Combi4, Vario Heat
  // 0x10 on Alde Paneel
  // 0x6D on Alde Compact 3020 HE
  u_int8_t unknown_2;
  // 0x10, 0x12 on CPplus
  // 0x00 on Combi4, Vario Heat
  // 0x00 on Alde Paneel & Alde Compact 3020 HE
  u_int8_t unknown_3;
  u_int8_t unknown_4;
  u_int8_t unknown_5;
} __attribute__((packed));

// Length 28 (0x1C) - MSG x51
struct StatusFrameAldeStatus {  // NOLINT(altera-struct-pack-align)
  HeaterAlde heater_mode;
  u_int8_t unknown_01;  // x00
  TargetTemp target_temp_room;
  u_int16_t unknown_04;  // xFFFE
  WaterTempAlde water_mode;
  ElectricPowerLevelAlde el_mode;
  GasModeAlde gas_mode;
  HeaterPriorityAlde heater_prio;
  u_int8_t unknown_10;  // x00
  u_int8_t unknown_11;  // x64
  u_int8_t unknown_12;  // xFF
  u_int8_t unknown_13;  // xFF
  u_int8_t unknown_14;  // xFF
  u_int8_t message_counter;
  TargetTemp current_temp_inside;
  u_int16_t unknown_18;  // xFFFE
  TargetTemp current_temp_outside;
  u_int8_t unknown_22;   // x00
  u_int8_t unknown_23;   // x1E
  u_int16_t unknown_24;  // xFFFF
  u_int16_t unknown_26;  // xFFFF
} __attribute__((packed));

// Length 16 (0x10) - MSG x50
struct StatusFrameAldeStatusResponse {  // NOLINT(altera-struct-pack-align)
  HeaterAlde heater_mode;
  u_int8_t unknown_01;  // x00
  TargetTemp target_temp_room;
  u_int16_t unknown_04;  // xFFFF
  WaterTempAlde water_mode;
  ElectricPowerLevelAlde el_mode;
  GasModeAlde gas_mode;
  HeaterPriorityAlde heater_prio;
  u_int8_t unknown_10;  // x00
  u_int8_t unknown_11;  // x64
  u_int8_t unknown_12;  // xFF
  u_int8_t unknown_13;  // xFF
  u_int8_t unknown_14;  // xFF
  u_int8_t message_counter;
} __attribute__((packed));

// Length 36 (0x24) - MSG x53
struct StatusFrameAldeAddon {  // NOLINT(altera-struct-pack-align)
  u_int8_t unknown_00[15];
  TempSensorUsageAlde temp_sensor;
  u_int8_t unknown_16[3];  // xFF
  u_int8_t message_counter;
  u_int8_t unknown_20[16];
} __attribute__((packed));

// Length 12 (0x0C) - MSG x55
struct StatusFrameAldeHeaterNight {  // NOLINT(altera-struct-pack-align)
  TargetTemp target_temp_room;
  u_int16_t mode_start_time;  // 0x03DE - 990/60 -> 16.5 -> 16:30
  u_int16_t mode_end_time;    // 0x01C2 - 450/60 -> 07.5 -> 07:30
  WeekDayAlde weekday_start;
  WeekDayAlde weekday_end;
  u_int8_t bits;        // 17 sensor bett, 7 sensor paneel / auto with night mode, 6 Night mode off, 3 hot water, 1
  u_int8_t unknown_09;  // x03, x02, x01
  u_int8_t unknown_10;  // 0xFF
  u_int8_t message_counter;
} __attribute__((packed));

// Length 12 (0x0C) - MSG x57
struct StatusFrameAldeHeaterDay {  // NOLINT(altera-struct-pack-align)
  TargetTemp target_temp_room;
  u_int16_t mode_start_time;  // 0x03DE - 990/60 -> 16.5 -> 16:30
  u_int16_t mode_end_time;    // 0x04CE - 1230/60 -> 20.5 -> 20:30
  WeekDayAlde weekday_start;
  WeekDayAlde weekday_end;
  u_int8_t bits;
  u_int8_t unknown_09;  // 0x00
  u_int8_t unknown_10;  // 0xFF
  u_int8_t message_counter;
} __attribute__((packed));

// ALDE direct heater message structs

// ex: 5E.0B.00.FF.FF.FF.FF.FF
// ex: 40.0B.00
struct Heater_Alde_PID_03 {  // NOLINT(altera-struct-pack-align)
  TargetTemp temp;           // 15-18°C
  u_int8_t unknown_02;       // 0x00
} __attribute__((packed));

// ex: AA.0A.FF.FF.FF.FF.FF.FF
struct Heater_Alde_PID_04 {  // NOLINT(altera-struct-pack-align)
  TargetTemp temp;           // 0°C
} __attribute__((packed));

// ex: 01.08.90.FF.FF.FF.FF.FF
// ex: 00.08.90
struct Heater_Alde_PID_05 {  // NOLINT(altera-struct-pack-align)
  u_int8_t unknown_00;       // 0x01 - ? On or Off
  u_int8_t unknown_01;       // 0x08
  u_int8_t unknown_02;       // 0x90
} __attribute__((packed));

// ex: 00.00.2F.F5.FF.FF.FF.FF
// ex: 00.00.2F.F5
struct Heater_Alde_PID_06 {  // NOLINT(altera-struct-pack-align)
  u_int8_t unknown_00;       // 0x00
  u_int8_t unknown_01;       // 0x00
  u_int16_t unknown_02;      // 0xF52F
} __attribute__((packed));

// ex: 58.0B.FF.FF.2B.00.20.44
// ex: 57.0B.FF.FF.2B.00.20.44
// ex: 55.0B.FF.FF.2B.00.20.44
// ex: 56.0B.FF.FF.2B.00.20.44
// ex: B8.0B.FF.FF.2B.00.20.44
struct Heater_Alde_PID_07 {  // NOLINT(altera-struct-pack-align)
  TargetTemp temp;           // 17.4-27-28.2°C
  u_int16_t unknown_02;      // 0xFFFF
  u_int8_t unknown_04;       // 0x2B
  u_int8_t unknown_05;       // 0x00
  u_int8_t unknown_06;       // 0x20
  u_int8_t unknown_07;       // 0x44
} __attribute__((packed));

// ex: EE.0C.04.FF.FF.FF.FF.FF
// ex: DA.0C.04.FF.FF.FF.FF.FF
// ex: D0.0C.04.FF.FF.FF.FF.FF
// ex: E4.0C.04.FF.FF.FF.FF.FF
// ex: E0.0B.00
struct Heater_Alde_PID_13 {  // NOLINT(altera-struct-pack-align)
  TargetTemp temp;           // 30-31-56 - 58°C
  u_int8_t unknown_02;       // 0x04
} __attribute__((packed));

// ex: 00.00.2F.F5.04.0B.FF.FF
// ex: 00.00.2F.F5.0E.0B.FF.FF
// ex: 00.00.2F.F5.C2.0B
struct Heater_Alde_PID_15 {  // NOLINT(altera-struct-pack-align)
  u_int8_t unknown_00;       // 0x00
  u_int8_t unknown_01;       // 0x00
  u_int16_t unknown_02;      // 0xF52F
  TargetTemp temp;           // 9-10-28°C
} __attribute__((packed));

// ex: D0.0C.FF.7F.FF.7F.6D.00
// ex: DA.0C.FF.7F.FF.7F.6D.00
// ex: DA.0C.FF.7F.FF.7F.45.00
// ex: D6.0B.FF.7F.FF.7F.00.00
struct Heater_Alde_PID_1B {  // NOLINT(altera-struct-pack-align)
  TargetTemp temp;           // 30-55-57°C
  u_int16_t unknown_02;      // 0x7FFF
  u_int16_t unknown_04;      // 0x7FFF
  u_int8_t unknown_06;       // 0x6D x45
  u_int8_t unknown_07;       // 0x00
} __attribute__((packed));

}  // namespace truma_inetbox
}  // namespace esphome