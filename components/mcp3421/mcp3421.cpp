#include <esphome/core/log.h>
#include "mcp3421.h"

namespace esphome::mcp3421 {

using ::std::size_t;

static const char *TAG = "mcp3421.sensor";

void Mcp3421Sensor::setup() {
    if (continuous_) {
        uint8_t config = 0x90 | this->width_ | this->gain_;
        I2CDevice::write(&config, sizeof(config));
    }
}

void Mcp3421Sensor::update() {
#ifdef USE_POWER_SUPPLY
    PowerGuard guard{power_};
#endif
    uint8_t data[4];
    size_t length = (this->width_ == 0xc) ? 4 : 3;

    if (!continuous_) {
        uint8_t config = 0x80 | this->width_ | this->gain_;
        I2CDevice::write(&config, sizeof(config));
    }

    do {
        I2CDevice::read(data, length);
    } while (data[length-1] & 0x80);

    int32_t value = static_cast<int16_t>((this->width_ == 0x0c)
        ? ((data[0] << 16) | (data[1] << 8) | data[2])
        : ((data[0] << 8) | data[1])
    );
    ESP_LOGD(TAG, "Raw bytes: 0x%02X%02X%02X", data[0], data[1], (this->width_ == 0x0c) ? data[2] : 0);
    ESP_LOGD(TAG, "Calculated value: %f/%f", value, max_);
    float result = 7.0 - static_cast<float>(value) / 59.17;
    this->publish_state(result);
}

void Mcp3421Sensor::dump_config() {
    LOG_I2C_DEVICE(this);
}

} /* namespace esphome::mcp3421 */