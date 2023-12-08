#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/uart/uart.h"
#include "esphome.h"

namespace esphome {
namespace xl_tanksensor_wr {

class XlTanksensorWrComponent : public sensor::Sensor, public Component, public uart::UARTDevice {
 public:
  XlTanksensorWrComponent(esphome::uart::UARTComponent *parent);

  float get_setup_priority() const override;
  void setup() override;
  void loop() override;
  void dump_config() override;

 protected:
  void check_buffer_();

  std::string buffer_;
};

} // namespace end
} // namespace end