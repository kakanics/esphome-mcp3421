import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import CONF_ID, UNIT_VOLT, ICON_FLASH, DEVICE_CLASS_VOLTAGE

CODEOWNERS = ["@your-github"]

mcp3421_ns = cg.esphome_ns.namespace("mcp3421")
MCP3421Sensor = mcp3421_ns.class_("MCP3421Sensor", sensor.Sensor, cg.Component)

CONFIG_SCHEMA = sensor.sensor_schema(
    unit_of_measurement=UNIT_VOLT,
    icon=ICON_FLASH,
    accuracy_decimals=3
).extend({
    cv.GenerateID(): cv.declare_id(MCP3421Sensor),
})

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    yield sensor.register_sensor(var, config)
