#pragma once

#include "TrumaStausFrameResponseStorage.h"
#include "TrumaStructs.h"
#include "TrumaStructsAlde.h"

namespace esphome {
namespace truma_inetbox {

class TrumaiNetBoxAppAldeStatus : public TrumaStausFrameResponseStorage<StatusFrameAldeStatus, StatusFrameAldeStatusResponse> {
 public:
  StatusFrameAldeStatusResponse *update_prepare() override;
  void create_update_data(StatusFrame *response, u_int8_t *response_len, u_int8_t command_counter) override;
  void dump_data() const override;
  bool can_update() override;

  bool action_heater_room(u_int8_t temperature);
  // bool action_heater_water(u_int8_t temperature);
  // bool action_heater_water(TargetTemp temperature);
  // bool action_heater_electric_power_level(u_int16_t value);
  // bool action_heater_energy_mix(EnergyMix energy_mix,
  //                               ElectricPowerLevel el_power_level = ElectricPowerLevel::ELECTRIC_POWER_LEVEL_0);
};

}  // namespace truma_inetbox
}  // namespace esphome
