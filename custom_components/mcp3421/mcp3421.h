// custom_components/mcp3421/mcp3421.h

#pragma once

#include "esphome/core/component.h"
#include "esphome/components/i2c/i2c.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace mcp3421 {

class MCP3421Sensor : public PollingComponent, public i2c::I2CDevice {
 public:
  MCP3421Sensor() : PollingComponent(10000) {}  // Default polling every 10s

  void set_sensor(sensor::Sensor *sensor) { sensor_ = sensor; }

  void setup() override;
  void update() override;

 protected:
  sensor::Sensor *sensor_{nullptr};
};

}  // namespace mcp3421
}  // namespace esphome

