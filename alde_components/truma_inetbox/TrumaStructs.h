#pragma once

#include "TrumaEnums.h"
#include "TrumaStructsAlde.h"

namespace esphome {
namespace truma_inetbox {

#define LIN_SID_RESPONSE 0x40
#define LIN_SID_READ_STATE_BUFFER 0xBA
#define LIN_SID_FIll_STATE_BUFFFER 0xBB

// Response to init are the following frames:
// - 2/3 STATUS_FRAME_DEVICES
// - STATUS_FRAME_HEATER
// - STATUS_FRAME_TIMER
// - STAUTS_FRAME_CONFIG
// - STATUS_FRAME_CLOCK
#define STATUS_FRAME_RESPONSE_INIT_REQUEST 0x0A
#define STATUS_FRAME_DEVICES 0x0B
#define STATUS_FRAME_DEVICES_ALDE 0x0C
#define STATUS_FRAME_RESPONSE_ACK 0x0D
#define STATUS_FRAME_CLOCK_RESPONSE (STATUS_FRAME_CLOCK - 1)
#define STATUS_FRAME_CLOCK 0x15
// TODO: Documentation and testing of config response.
#define STAUTS_FRAME_CONFIG_RESPONSE (STAUTS_FRAME_CONFIG - 1)
#define STAUTS_FRAME_CONFIG 0x17
#define STATUS_FRAME_HEATER_RESPONSE (STATUS_FRAME_HEATER - 1)
#define STATUS_FRAME_HEATER 0x33
#define STATUS_FRAME_AIRCON_MANUAL_RESPONSE (STATUS_FRAME_AIRCON_MANUAL - 1)
#define STATUS_FRAME_AIRCON_MANUAL 0x35
#define STATUS_FRAME_AIRCON_AUTO_RESPONSE (STATUS_FRAME_AIRCON_AUTO - 1)
#define STATUS_FRAME_AIRCON_AUTO 0x37
#define STATUS_FRAME_TIMER_RESPONSE (STATUS_FRAME_TIMER - 1)
#define STATUS_FRAME_TIMER 0x3D
#define STATUS_FRAME_AIRCON_MANUAL_INIT_RESPONSE (STATUS_FRAME_AIRCON_MANUAL_INIT - 1)
#define STATUS_FRAME_AIRCON_MANUAL_INIT 0x3F
#define STATUS_FRAME_AIRCON_AUTO_INIT_RESPONSE (STATUS_FRAME_AIRCON_AUTO_INIT - 1)
#define STATUS_FRAME_AIRCON_AUTO_INIT 0x41
#define STATUS_FRAME_ALDE_STATUS_RESPONSE (STATUS_FRAME_ALDE_STATUS - 1)
#define STATUS_FRAME_ALDE_STATUS 0x51
#define STATUS_FRAME_ALDE_ADDON_RESPONSE (STATUS_FRAME_ALDE_ADDON - 1)
#define STATUS_FRAME_ALDE_ADDON 0x53
#define STATUS_FRAME_ALDE_HEATER_NIGHT_RESPONSE (STATUS_FRAME_ALDE_HEATER_NIGHT - 1)
#define STATUS_FRAME_ALDE_HEATER_NIGHT 0x55
#define STATUS_FRAME_ALDE_HEATER_DAY_RESPONSE (STATUS_FRAME_ALDE_HEATER_DAY - 1)
#define STATUS_FRAME_ALDE_HEATER_DAY 0x57

// ALDE
// SID<---------PREAMBLE---------->|<---MSG_HEAD---->|
// STATUS_FRAME_ALDE_HEATER_51_RESPONSE (STATUS_FRAME_ALDE_HEATER_51 - 1)
// STATUS_FRAME_ALDE_HEATER_51 0x51
// BB.00.1F.00.22.00.00.22.FF.FF.FF.54.01.1C.51.00.86.01.00.5E.0B.FE.FF.00.00.37.01.00.64.FF.FF.FF.12.71.0B.FE.FF.FA.0A.00.1E.FF.FF.FF.FF
// (45) STATUS_FRAME_ALDE_HEATER_53_RESPONSE (STATUS_FRAME_ALDE_HEATER_53 - 1) STATUS_FRAME_ALDE_HEATER_53 0x53
// BB.00.1F.00.2A.00.00.22.FF.FF.FF.54.01.24.53.00.36.00.00.00.00.FD.FD.00.00.02.00.00.00.01.FD.FD.00.FF.FF.FF.01.FD.FF.00.00.00.00.00.01.02.00.FF.FF.FF.FF.FF.FF
// (53) STATUS_FRAME_ALDE_HEATER_55_RESPONSE (STATUS_FRAME_ALDE_HEATER_55 - 1) STATUS_FRAME_ALDE_HEATER_55 0x55
// BB.00.1F.00.12.00.00.22.FF.FF.FF.54.01.0C.55.00.FD.5E.0B.DE.03.C2.01.07.07.17.03.FF.14 (29)
// STATUS_FRAME_ALDE_HEATER_57_RESPONSE (STATUS_FRAME_ALDE_HEATER_57 - 1)
// STATUS_FRAME_ALDE_HEATER_57 0x55
// BB.00.1F.00.12.00.00.22.FF.FF.FF.54.01.0C.57.00.15.63.0B.DE.03.CE.04.07.07.00.00.FF.01 (29)

struct StatusFrameHeader {  // NOLINT(altera-struct-pack-align)
  // sid
  u_int8_t service_identifier;
  u_int8_t header[10];
  u_int8_t header_2;  // x54 - 'T'
  u_int8_t header_3;  // x01
  // after checksum
  u_int8_t message_length;
  u_int8_t message_type;
  u_int8_t command_counter;
  u_int8_t checksum;
} __attribute__((packed));

// Length 20 (0x14) - MSG x33
struct StatusFrameHeater {  // NOLINT(altera-struct-pack-align)
  TargetTemp target_temp_room;
  // Room
  HeatingMode heating_mode;
  ElectricPowerLevel el_power_level_a;
  TargetTemp target_temp_water;
  ElectricPowerLevel el_power_level_b;
  EnergyMix energy_mix_a;
  // Ignored by response
  EnergyMix energy_mix_b;
  u_int16_t current_temp_water;
  u_int16_t current_temp_room;
  OperatingStatus operating_status;
  u_int8_t error_code_low;
  u_int8_t error_code_high;
  u_int8_t heater_unknown_2;
} __attribute__((packed));

// Length 12 (0x0C) - MSG x32
struct StatusFrameHeaterResponse {  // NOLINT(altera-struct-pack-align)
  TargetTemp target_temp_room;
  // Room
  HeatingMode heating_mode;
  ElectricPowerLevel el_power_level_a;
  TargetTemp target_temp_water;
  ElectricPowerLevel el_power_level_b;
  EnergyMix energy_mix_a;
  // Ignored?
  EnergyMix energy_mix_b;
} __attribute__((packed));

// Length 24 (0x18) - x3D
struct StatusFrameTimer {  // NOLINT(altera-struct-pack-align)
  TargetTemp timer_target_temp_room;
  HeatingMode timer_heating_mode;
  ElectricPowerLevel timer_el_power_level_a;
  TargetTemp timer_target_temp_water;
  ElectricPowerLevel timer_el_power_level_b;
  EnergyMix timer_energy_mix_a;
  EnergyMix timer_energy_mix_b;
  // used by timer response message
  u_int8_t unused[5];
  u_int8_t timer_unknown_3;
  u_int8_t timer_unknown_4;
  TimerActive timer_active;
  u_int8_t timer_start_minutes;
  u_int8_t timer_start_hours;
  u_int8_t timer_stop_minutes;
  u_int8_t timer_stop_hours;
} __attribute__((packed));

// Length 13 (0x0D) - x3C
struct StatusFrameTimerResponse {  // NOLINT(altera-struct-pack-align)
  TargetTemp timer_target_temp_room;
  HeatingMode timer_heating_mode;
  ElectricPowerLevel timer_el_power_level_a;
  TargetTemp timer_target_temp_water;
  ElectricPowerLevel timer_el_power_level_b;
  EnergyMix timer_energy_mix_a;
  EnergyMix timer_energy_mix_b;
  // set by response message to active timer
  TimerActive timer_resp_active;
  // set by response message to active timer
  u_int8_t timer_resp_start_minutes;
  // set by response message to active timer
  u_int8_t timer_resp_start_hours;
  // set by response message to active timer
  u_int8_t timer_resp_stop_minutes;
  // set by response message to active timer
  u_int8_t timer_resp_stop_hours;
} __attribute__((packed));

// Length 2 (0x02) - MSG x0D
struct StatusFrameResponseAck {  // NOLINT(altera-struct-pack-align)
  ResponseAckResult error_code;
  u_int8_t unknown;
} __attribute__((packed));

// Length 10 (0x0A) - MSG x15
struct StatusFrameClock {  // NOLINT(altera-struct-pack-align)
  u_int8_t clock_hour;
  u_int8_t clock_minute;
  u_int8_t clock_second;
  // Truma: MUST be 0x1, 0x2, 0x3..? (lower than 0x9)
  // Alde: 0xFF
  u_int8_t display_1;
  // Truma: MUST be 0x1
  // Alde: 0xFF
  u_int8_t display_2;
  // Alde: 0xFF
  u_int8_t display_3;
  ClockMode clock_mode;
  ClockSource clock_source;
  // Alde: Day - x4 Friday
  u_int8_t display_4;
  // Alde: 0xFF
  u_int8_t display_5;
} __attribute__((packed));

// Length 10 (0x0A) - MSG 17
struct StatusFrameConfig {  // NOLINT(altera-struct-pack-align)
  // 0x01 .. 0x0A
  u_int8_t display_brightness;
  Language language;
  // Mit „AC SET“ wird ein Offset zwischen Kühlen und Heizen eingestellt.
  // Die Einstellung ist in Schritten von 0,5 °C im Bereich von 0 °C bis +5 °C möglich.
  TargetTemp ac_offset;
  TargetTemp temp_offset;
  OperatingUnits temp_units;
  u_int8_t unknown_6;
  u_int8_t unknown_7;
  u_int8_t unknown_8;
} __attribute__((packed));

// Length 12 (0x0C) - MSG x0B
struct StatusFrameDevice {  // NOLINT(altera-struct-pack-align)
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
} __attribute__((packed));

// Length 18 (0x12) - MSG x35
// TODO
struct StatusFrameAirconManual {  // NOLINT(altera-struct-pack-align)
  AirconMode mode;
  // 0x00
  u_int8_t unknown_02;
  AirconOperation operation;
  EnergyMix energy_mix;
  TargetTemp target_temp_aircon;
  // 0x00
  u_int8_t unknown_07;
  // 0x00
  u_int8_t unknown_08;
  // No idea why two current_temp
  TargetTemp current_temp_aircon;
  // 0x00
  u_int8_t unknown_11;
  // 0x00
  u_int8_t unknown_12;
  ElectricPowerLevel el_power_level;
  // 0x00
  u_int8_t unknown_15;
  // 0x00
  u_int8_t unknown_16;
  TargetTemp current_temp_room;
} __attribute__((packed));

struct StatusFrameAirconManualResponse {  // NOLINT(altera-struct-pack-align)
  AirconMode mode;
  // 0x00
  u_int8_t unknown_02;
  AirconOperation operation;
  EnergyMix energy_mix;
  TargetTemp target_temp_aircon;
} __attribute__((packed));

// Length 22 (0x16) - MSG x3F
// TODO
struct StatusFrameAirconManualInit {  // NOLINT(altera-struct-pack-align)
  u_int8_t unknown_01;                // 0x00
  u_int8_t unknown_02;                // 0x00
  AirconOperation operation;
  EnergyMix energy_mix;
  u_int8_t unknown_05;  // 0x00
  u_int8_t unknown_06;  // 0x00
  u_int8_t unknown_07;  // 0x00
  u_int8_t unknown_08;  // 0x00
  u_int8_t unknown_09;  // 0x00
  u_int8_t unknown_10;  // 0x00
  u_int8_t unknown_11;  // 0x00
  u_int8_t unknown_12;  // 0x00
  u_int8_t unknown_13;  // 0x00
  u_int8_t unknown_14;  // 0x00
  u_int8_t unknown_15;  // 0x00
  u_int8_t unknown_16;  // 0x00
  u_int8_t unknown_17;  // 0x00
  u_int8_t unknown_18;  // 0x00
  u_int8_t unknown_19;  // 0x00
  u_int8_t unknown_20;  // 0x00
  u_int8_t unknown_21;  // 0x00
  u_int8_t unknown_22;  // 0x00
} __attribute__((packed));

// Length 18 (0x12) - MSG x37
// TODO
struct StatusFrameAirconAuto {  // NOLINT(altera-struct-pack-align)
  EnergyMix energy_mix_a;
  u_int8_t unknown_02;  // 0x00
  EnergyMix energy_mix_b;
  u_int8_t unknown_04;  // 0x00
  u_int8_t unknown_05;  // 0x00
  u_int8_t unknown_06;  // 0x00
  TargetTemp target_temp_aircon_auto;
  ElectricPowerLevel el_power_level_a;
  u_int8_t unknown_11;  // 0x00
  u_int8_t unknown_12;  // 0x00
  ElectricPowerLevel el_power_level_b;
  TargetTemp current_temp;
  TargetTemp target_temp;
} __attribute__((packed));

// TODO
struct StatusFrameAirconAutoResponse {  // NOLINT(altera-struct-pack-align)
  EnergyMix energy_mix_a;
  u_int8_t unknown_02;  // 0x00
  EnergyMix energy_mix_b;
  u_int8_t unknown_04;  // 0x00
  u_int8_t unknown_05;  // 0x00
  u_int8_t unknown_06;  // 0x00
  TargetTemp target_temp_aircon_auto;
  ElectricPowerLevel el_power_level_a;
  u_int8_t unknown_11;  // 0x00
  u_int8_t unknown_12;  // 0x00
  ElectricPowerLevel el_power_level_b;
} __attribute__((packed));

// Length 20 (0x14)
// TODO
struct StatusFrameAirconAutoInit {  // NOLINT(altera-struct-pack-align)
  EnergyMix energy_mix_a;
  u_int8_t unknown_02;  // 0x00
  EnergyMix energy_mix_b;
  u_int8_t unknown_04;  // 0x00
  u_int8_t unknown_05;  // 0x00
  u_int8_t unknown_06;  // 0x00
  u_int8_t unknown_07;  // 0x00
  u_int8_t unknown_08;  // 0x00
  u_int8_t unknown_09;  // 0x00
  u_int8_t unknown_10;  // 0x00
  u_int8_t unknown_11;  // 0x00
  u_int8_t unknown_12;  // 0x00
  u_int8_t unknown_13;  // 0x00
  u_int8_t unknown_14;  // 0x00
  u_int8_t unknown_15;  // 0x00
  u_int8_t unknown_16;  // 0x00
  u_int8_t unknown_17;  // 0x00
  u_int8_t unknown_18;  // 0x00
  u_int8_t unknown_19;  // 0x00
  u_int8_t unknown_20;  // 0x00
} __attribute__((packed));

union StatusFrame {  // NOLINT(altera-struct-pack-align)
  u_int8_t raw[54];
  struct {  // NOLINT(altera-struct-pack-align)
    StatusFrameHeader genericHeader;
    union {  // NOLINT(altera-struct-pack-align)
      StatusFrameHeater heater;
      StatusFrameHeaterResponse heaterResponse;
      StatusFrameTimer timer;
      StatusFrameTimerResponse timerResponse;
      StatusFrameResponseAck responseAck;
      StatusFrameClock clock;
      StatusFrameConfig config;
      StatusFrameDevice device;
      StatusFrameAirconManual airconManual;
      StatusFrameAirconManualResponse airconManualResponse;
      StatusFrameAirconManualInit airconManualInit;
      StatusFrameAirconAuto airconAuto;
      StatusFrameAirconAutoResponse airconAutoResponse;
      StatusFrameAirconAutoInit airconAutoInit;
      StatusFrameAldeDevice aldeDevice;
      StatusFrameAldeStatusResponse aldeStatusResponse;
      StatusFrameAldeStatus aldeStatus;
      StatusFrameAldeAddon aldeAddon;
      StatusFrameAldeHeaterNight aldeHeaterNight;
      StatusFrameAldeHeaterDay aldeHeaterDay;
    } __attribute__((packed));
  };
} __attribute__((packed));

// Ex AA.AA.AA.FA.00.01.E0.0F
struct Heater_Combi_PID_20 {  // NOLINT(altera-struct-pack-align)
  u_int8_t unknown[8];
} __attribute__((packed));

// Ex
// 5F.1B.B4.28.00.01.F0.0F
// 60.3B.B4.28.00.01.F0.0F
struct Heater_Combi_PID_21 {  // NOLINT(altera-struct-pack-align)
  u_int8_t unknown[8];
} __attribute__((packed));

// Ex 84.00.10.04.FF.FF.FF.FF
struct Heater_Combi_PID_22 {  // NOLINT(altera-struct-pack-align)
  u_int8_t unknown[4];
} __attribute__((packed));

}  // namespace truma_inetbox
}  // namespace esphome