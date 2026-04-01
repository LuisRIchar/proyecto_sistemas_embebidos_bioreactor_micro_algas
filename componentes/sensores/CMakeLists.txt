idf_component_register(
    SRCS "turbidez.c" "bh1750_luz.c"
    INCLUDE_DIRS "."
    REQUIRES driver gestor bh1750
)