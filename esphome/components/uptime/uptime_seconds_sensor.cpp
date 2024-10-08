#include "uptime_seconds_sensor.h"

#include "esphome/core/hal.h"
#include "esphome/core/helpers.h"
#include "esphome/core/log.h"

namespace esphome {
namespace uptime {

static const char *const TAG = "uptime.sensor";

void UptimeSecondsSensor::update() {
  const uint32_t ms = millis();
  const uint64_t ms_mask = (1ULL << 32) - 1ULL;
  const uint32_t last_ms = this->uptime_ & ms_mask;
  if (ms < last_ms) {
    this->uptime_ += ms_mask + 1ULL;
    ESP_LOGD(TAG, "Detected roll-over \xf0\x9f\xa6\x84");
  }
  this->uptime_ &= ~ms_mask;
  this->uptime_ |= ms;

  // Do separate second and milliseconds conversion to avoid floating point division errors
  // Probably some IEEE standard already guarantees this division can be done without loss
  // of precision in a single division, but let's do it like this to be sure.
  const uint64_t seconds_int = this->uptime_ / 1000ULL;
  const float seconds = float(seconds_int) + (this->uptime_ % 1000ULL) / 1000.0f;
  this->publish_state(seconds);
}
std::string UptimeSecondsSensor::unique_id() { return get_mac_address() + "-uptime"; }
float UptimeSecondsSensor::get_setup_priority() const { return setup_priority::HARDWARE; }
void UptimeSecondsSensor::dump_config() {
  LOG_SENSOR("", "Uptime Sensor", this);
  ESP_LOGCONFIG(TAG, "  Type: Seconds");
}

}  // namespace uptime
}  // namespace esphome
