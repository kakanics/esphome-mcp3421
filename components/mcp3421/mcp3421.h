#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/i2c/i2c.h"

// Define the MCP3421 class
namespace esphome{
namespace mcp3421{
  
  class MCP3421Sensor : public PollingComponent, public sensor::Sensor, public i2c::I2CDevice{
 public:
 MCP3421Sensor() {}

 void setup();

  void update();

  float read_ph_value() {  // Correct placement of read_ph_value()
    // Add the logic to read the pH value from the sensor
    float ph = 7.0;  // Replace with actual reading logic
    return ph;
  }

 protected:
 // Add any required member variables here (e.g., I2C interface, sensor address)
};
}
}
