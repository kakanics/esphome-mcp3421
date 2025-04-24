// custom_components/mcp3421/mcp3421_sensor.cpp

#include "mcp3421.h"
#include "esphome/core/log.h"

namespace esphome {
namespace mcp3421 {

static const char *const TAG = "mcp3421";

MCP3421Sensor *mcp3421_sensor = nullptr;

void MCP3421Sensor::dump_config() {
  ESP_LOGCONFIG(TAG, "MCP3421:");
  LOG_I2C_DEVICE(this);
}

}  // namespace mcp3421
}  // namespace esphome
