import esphome.codegen as cg
from esphome.components import sensor, spi
import esphome.config_validation as cv
from esphome.const import (
    CONF_MAINS_FILTER,
    CONF_THERMOCOUPLE_TYPE,
    DEVICE_CLASS_TEMPERATURE,
    STATE_CLASS_MEASUREMENT,
    UNIT_CELSIUS,
)

max31856_ns = cg.esphome_ns.namespace("max31856")
MAX31856Sensor = max31856_ns.class_(
    "MAX31856Sensor", sensor.Sensor, cg.PollingComponent, spi.SPIDevice
)

MAX31865ConfigFilter = max31856_ns.enum("MAX31856ConfigFilter")
FILTER = {
    50: MAX31865ConfigFilter.FILTER_50HZ,
    60: MAX31865ConfigFilter.FILTER_60HZ,
}
MAX31856ThermocoupleType = max31856_ns.enum("MAX31856ThermocoupleType")
THERMOCOUPLE_TYPE = {
    "B": MAX31856ThermocoupleType.MAX31856_TCTYPE_B,
    "E": MAX31856ThermocoupleType.MAX31856_TCTYPE_E,
    "J": MAX31856ThermocoupleType.MAX31856_TCTYPE_J,
    "K": MAX31856ThermocoupleType.MAX31856_TCTYPE_K,
    "N": MAX31856ThermocoupleType.MAX31856_TCTYPE_N,
    "R": MAX31856ThermocoupleType.MAX31856_TCTYPE_R,
    "S": MAX31856ThermocoupleType.MAX31856_TCTYPE_S,
    "T": MAX31856ThermocoupleType.MAX31856_TCTYPE_T,
}

CONFIG_SCHEMA = (
    sensor.sensor_schema(
        MAX31856Sensor,
        unit_of_measurement=UNIT_CELSIUS,
        accuracy_decimals=1,
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
    )
    .extend(
        {
            cv.Optional(CONF_MAINS_FILTER, default="60Hz"): cv.All(
                cv.frequency, cv.enum(FILTER, int=True)
            ),
        }
    )
    .extend(
        {
            cv.Optional(CONF_THERMOCOUPLE_TYPE, default="K"): cv.enum(
                THERMOCOUPLE_TYPE, upper=True, space=""
            ),
        }
    )
    .extend(cv.polling_component_schema("60s"))
    .extend(spi.spi_device_schema())
)


async def to_code(config):
    var = await sensor.new_sensor(config)
    await cg.register_component(var, config)
    await spi.register_spi_device(var, config)
    cg.add(var.set_filter(config[CONF_MAINS_FILTER]))
    cg.add(var.set_thermocouple_type(config[CONF_THERMOCOUPLE_TYPE]))
