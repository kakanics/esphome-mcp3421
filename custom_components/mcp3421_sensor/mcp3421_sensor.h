#include "esphome.h"

class MCP3421Sensor : public PollingSensorComponent, public I2CDevice {
 public:
  MCP3421Sensor(I2CComponent *parent, uint8_t address = 0x68)
      : PollingSensorComponent(1000), I2CDevice(parent, address) {}

  void setup() override {
    write_register(0x9C);  // Continuous conversion, 18-bit, gain = 1
  }

  void update() override {
    uint8_t data[4];
    if (!this->read_bytes(data, 4)) {
      ESP_LOGE("mcp3421", "Failed to read from MCP3421");
      publish_state(NAN);
      return;
    }

    long raw = ((long)data[0] << 16) | ((long)data[1] << 8) | data[2];
    if (raw & 0x020000) raw |= 0xFFFC0000;  // Sign extend

    float voltage = raw * (2.048 / 131072.0);  // VREF / 2^17
    publish_state(voltage);
  }

 private:
  void write_register(uint8_t value) {
    this->write(&value, 1);
  }
};
