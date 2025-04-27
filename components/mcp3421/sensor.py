import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c, power_supply, sensor
from esphome.const import ICON_EMPTY, UNIT_VOLT, CONF_POWER_SUPPLY

DEPENDENCIES = ["i2c"]

mcp3421_ns = cg.esphome_ns.namespace("mcp3421")
Mcp3421Sensor = mcp3421_ns.class_(
    "Mcp3421Sensor", sensor.Sensor, cg.PollingComponent, i2c.I2CDevice
)


def _sample_width(value):
    SAMPLE_WIDTHS = {
        12: 0x0,
        14: 0x4,
        16: 0x8,
        18: 0xC,
    }
    if (result := SAMPLE_WIDTHS.get(value)) is not None:
        return result
    raise cv.Invalid(f"Valid sample widths are 12, 14, 16, 18")


def _gain(value):
    GAINS = {
        1: 0x0,
        2: 0x1,
        4: 0x2,
        8: 0x3,
    }
    if (result := GAINS.get(value)) is not None:
        return result
    raise cv.Invalid(f"Valid gains are 1, 2, 4, 8")


CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.Optional(CONF_POWER_SUPPLY): cv.use_id(power_supply.PowerSupply),
            cv.Optional("continuous", default=True): cv.boolean,
            cv.Required("sample_width"): _sample_width,
            cv.Optional("gain", default=1): _gain,
        }
    )
    .extend(
        sensor.sensor_schema(
            Mcp3421Sensor,
            unit_of_measurement=UNIT_VOLT,
            icon=ICON_EMPTY,
            accuracy_decimals=5,
        )
    )
    .extend(cv.polling_component_schema("60s"))
    .extend(i2c.i2c_device_schema(0x68))
)


async def to_code(config):
    continuous = config["continuous"]
    sample_width = config["sample_width"]
    gain = config["gain"]
    var = await sensor.new_sensor(config, continuous, sample_width, gain)
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)

    if (power_supply_id := config.get(CONF_POWER_SUPPLY)) is not None:
        power_supply_ = await cg.get_variable(power_supply_id)
        cg.add(var.set_power_supply(power_supply_))