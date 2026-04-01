idf_component_register(
    SRCS "turbidez.c" "bh1750_luz.c" "DS18B20_temp.c"
    INCLUDE_DIRS "."
    REQUIRES driver gestor bh1750 ds18b20 onewire_bus
)