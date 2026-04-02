idf_component_register(SRCS "pantalla_oled.c" "u8g2_esp32_hal.c" "calentador_relay.c" "tira_led_roja.c"
                       INCLUDE_DIRS "."
                       REQUIRES u8g2 gestor)