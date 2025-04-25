# ESPHome MCP3421 Custom Component

This custom component supports the MCP3421 ADC via I2C using the ESPHome framework.

## Usage

```yaml
external_components:
  - source:
      type: git
      url: https://github.com/YOUR_USERNAME/esphome-mcp3421
      ref: main

sensor:
  - platform: mcp3421
    name: "pH Sensor Voltage"
    id: ph_raw
    update_interval: 10s