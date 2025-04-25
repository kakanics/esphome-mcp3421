#ifndef _MCP3421_H_
#define _MCP3421_H_

#include <esphome/core/component.h>
#include <esphome/components/sensor/sensor.h>
#include <esphome/components/i2c/i2c.h>
#ifdef USE_POWER_SUPPLY
#include "esphome/components/power_supply/power_supply.h"
#endif

namespace esphome::mcp3421 {

class Mcp3421Sensor : public sensor::Sensor, public PollingComponent, public i2c::I2CDevice
{
public:
    Mcp3421Sensor(bool continuous, uint8_t width, uint8_t gain)
        : continuous_(continuous), width_(width), gain_(gain), max_(calc_max(width))
    {}

    void setup() override;
    void update() override;
    void dump_config() override;

#ifdef USE_POWER_SUPPLY
    void set_power_supply(power_supply::PowerSupply *power_supply) { this->power_.set_parent(power_supply); }
#endif

protected:
#ifdef USE_POWER_SUPPLY
    power_supply::PowerSupplyRequester power_;
#endif

    const bool continuous_;
    const uint8_t width_;
    const uint8_t gain_;
    const float max_;

    float calc_max(uint8_t width) const
    {
        int tmp = 10 + (this->width_ >> 1);
        return static_cast<float>(1 << tmp);
    }
};

}


#endif /*_MCP3421_H_*/