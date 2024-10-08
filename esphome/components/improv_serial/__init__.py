import esphome.codegen as cg
from esphome.components import improv_base
from esphome.components.esp32 import get_esp32_variant
from esphome.components.esp32.const import VARIANT_ESP32S3
from esphome.components.logger import USB_CDC
import esphome.config_validation as cv
from esphome.const import CONF_BAUD_RATE, CONF_HARDWARE_UART, CONF_ID, CONF_LOGGER
from esphome.core import CORE
import esphome.final_validate as fv

AUTO_LOAD = ["improv_base"]
CODEOWNERS = ["@esphome/core"]
DEPENDENCIES = ["logger", "wifi"]

improv_serial_ns = cg.esphome_ns.namespace("improv_serial")

ImprovSerialComponent = improv_serial_ns.class_("ImprovSerialComponent", cg.Component)

CONFIG_SCHEMA = (
    cv.Schema({cv.GenerateID(): cv.declare_id(ImprovSerialComponent)})
    .extend(improv_base.IMPROV_SCHEMA)
    .extend(cv.COMPONENT_SCHEMA)
)


def validate_logger(config):
    logger_conf = fv.full_config.get()[CONF_LOGGER]
    if logger_conf[CONF_BAUD_RATE] == 0:
        raise cv.Invalid("improv_serial requires the logger baud_rate to be not 0")
    if CORE.using_esp_idf:
        if (
            logger_conf[CONF_HARDWARE_UART] == USB_CDC
            and get_esp32_variant() == VARIANT_ESP32S3
        ):
            raise cv.Invalid(
                "improv_serial does not support the selected logger hardware_uart"
            )
    return config


FINAL_VALIDATE_SCHEMA = validate_logger


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await improv_base.setup_improv_core(var, config)
