import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c, sensor
from esphome.const import (
    CONF_ID,
    CONF_UPDATE_INTERVAL,
    UNIT_VOLT,
    ICON_FLASH,
    DEVICE_CLASS_VOLTAGE,
)

DEPENDENCIES = ["i2c", "sensor"]

mcp3421_ns = cg.esphome_ns.namespace("mcp3421")
MCP3421Sensor = mcp3421_ns.class_("MCP3421Sensor", sensor.Sensor, cg.PollingComponent, i2c.I2CDevice)

CONFIG_SCHEMA = (
    sensor.sensor_schema(
        unit_of_measurement=UNIT_VOLT,
        accuracy_decimals=3,
        device_class=DEVICE_CLASS_VOLTAGE,
        icon=ICON_FLASH,
    )
    .extend({
        cv.GenerateID(): cv.declare_id(MCP3421Sensor),
        cv.Optional(CONF_UPDATE_INTERVAL, default="10s"): cv.update_interval,
    })
    .extend(i2c.i2c_device_schema(default_address=0x68))
)

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    yield i2c.register_i2c_device(var, config)
    yield sensor.register_sensor(var, config)
