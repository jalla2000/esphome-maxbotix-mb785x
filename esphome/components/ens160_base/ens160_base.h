#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace ens160_base {

class ENS160Component : public PollingComponent, public sensor::Sensor {
 public:
  void set_co2(sensor::Sensor *co2) { co2_ = co2; }
  void set_tvoc(sensor::Sensor *tvoc) { tvoc_ = tvoc; }
  void set_aqi(sensor::Sensor *aqi) { aqi_ = aqi; }

  void set_humidity(sensor::Sensor *humidity) { humidity_ = humidity; }
  void set_temperature(sensor::Sensor *temperature) { temperature_ = temperature; }

  void setup() override;
  void update() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::DATA; }

 protected:
  void send_env_data_();

  enum ErrorCode {
    NONE = 0,
    COMMUNICATION_FAILED,
    INVALID_ID,
    VALIDITY_INVALID,
    READ_FAILED,
    WRITE_FAILED,
    STD_OPMODE_FAILED,
  } error_code_{NONE};

  enum ValidityFlag {
    NORMAL_OPERATION = 0,
    WARMING_UP,
    INITIAL_STARTUP,
    INVALID_OUTPUT,
  } validity_flag_;

  bool warming_up_{false};
  bool initial_startup_{false};

  virtual bool read_byte(uint8_t a_register, uint8_t *data) = 0;
  virtual bool write_byte(uint8_t a_register, uint8_t data) = 0;
  virtual bool read_bytes(uint8_t a_register, uint8_t *data, size_t len) = 0;
  virtual bool write_bytes(uint8_t a_register, uint8_t *data, size_t len) = 0;

  uint8_t firmware_ver_major_{0};
  uint8_t firmware_ver_minor_{0};
  uint8_t firmware_ver_build_{0};

  sensor::Sensor *co2_{nullptr};
  sensor::Sensor *tvoc_{nullptr};
  sensor::Sensor *aqi_{nullptr};

  sensor::Sensor *humidity_{nullptr};
  sensor::Sensor *temperature_{nullptr};
};

}  // namespace ens160_base
}  // namespace esphome
