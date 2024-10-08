#include "esphome/core/defines.h"
#if defined(USE_HOST) && defined(USE_MDNS)

#include "esphome/components/network/ip_address.h"
#include "esphome/components/network/util.h"
#include "esphome/core/log.h"
#include "mdns_component.h"

namespace esphome {
namespace mdns {

void MDNSComponent::setup() { this->compile_records_(); }

void MDNSComponent::on_shutdown() {}

}  // namespace mdns
}  // namespace esphome

#endif
