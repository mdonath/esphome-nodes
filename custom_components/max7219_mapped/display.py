import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import display, spi
from esphome.const import CONF_ID, CONF_INTENSITY, CONF_LAMBDA, CONF_NUM_CHIPS, CONF_INDEX

# AUTO_LOAD = ["max7219"]

DEPENDENCIES = ["spi"]

max7219_ns = cg.esphome_ns.namespace("max7219")
MAX7219MappedComponent = max7219_ns.class_(
    "MAX7219MappedComponent", cg.PollingComponent, spi.SPIDevice
)
MAX7219MappedComponentRef = MAX7219MappedComponent.operator("ref")

CONF_REVERSE_ENABLE = "reverse_enable"

CONFIG_SCHEMA = (
    display.BASIC_DISPLAY_SCHEMA.extend(
        {
            cv.GenerateID(): cv.declare_id(MAX7219MappedComponent),
            cv.Optional(CONF_NUM_CHIPS, default=1): cv.int_range(min=1, max=255),
            cv.Optional(CONF_INTENSITY, default=15): cv.int_range(min=0, max=15),
            cv.Optional(CONF_REVERSE_ENABLE, default=False): cv.boolean,
            cv.Optional(CONF_INDEX): cv.All([cv.int_], cv.Length(min=16, max=16)),
        }
    )
    .extend(cv.polling_component_schema("1s"))
    .extend(spi.spi_device_schema())
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await spi.register_spi_device(var, config)
    await display.register_display(var, config)

    cg.add(var.set_num_chips(config[CONF_NUM_CHIPS]))
    cg.add(var.set_intensity(config[CONF_INTENSITY]))
    cg.add(var.set_reverse(config[CONF_REVERSE_ENABLE]))
    if CONF_INDEX in config:
        cg.add(var.set_mapping(config[CONF_INDEX]))

    if CONF_LAMBDA in config:
        lambda_ = await cg.process_lambda(
            config[CONF_LAMBDA], [(MAX7219MappedComponentRef, "it")], return_type=cg.void
        )
        cg.add(var.set_writer(lambda_))
