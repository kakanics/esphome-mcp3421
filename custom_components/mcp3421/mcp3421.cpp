// custom_components/mcp3421/mcp3421.cpp

#include "mcp3421.h"
#include "esphome/core/log.h"

namespace esphome {
namespace mcp3421 {

static const char *const TAG = "mcp3421.sensor";

void MCP3421Sensor::setup() {
  ESP_LOGCONFIG(TAG, "Setting up MCP3421 sensor...");
}

void MCP3421Sensor::update() {
  uint8_t buffer[3];

  if (!this->read(buffer, 3)) {
    ESP_LOGW(TAG, "Failed to read data from MCP3421");
    return;
  }

  int32_t value = ((int32_t)buffer[0] << 16) | ((int32_t)buffer[1] << 8) | buffer[2];
  value >>= 4;  // 18-bit resolution is in upper 18 bits

  float voltage = (value * 2.048) / 131072.0;  // 2.048V ref, 18-bit gain=1
  ESP_LOGD(TAG, "MCP3421 Raw: %d -> Voltage: %.5f V", value, voltage);

  if (sensor_ != nullptr)
    sensor_->publish_state(voltage);
}

}  // namespace mcp3421
}  // namespace esphome

