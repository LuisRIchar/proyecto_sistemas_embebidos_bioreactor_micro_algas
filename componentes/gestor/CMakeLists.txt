idf_component_register(
    SRCS "gestor_datos.c" "i2c_bus_compartido.c"
    INCLUDE_DIRS "."
    REQUIRES driver
)