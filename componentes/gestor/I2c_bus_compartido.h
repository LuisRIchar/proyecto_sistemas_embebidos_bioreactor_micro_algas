/*
 * Copyright 2026 Luis Ricardo Serrano Dzib
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once

#include "driver/i2c_master.h"

/*
 * Inicializa el bus I2C compartido una sola vez.
 * Llama esto en app_main ANTES de Init_pantalla e Init_sensor_luz.
 */
void i2c_bus_init(uint8_t sda, uint8_t scl);

/*
 * Devuelve el handle del bus ya creado.
 * Úsalo para agregar devices sin crear un nuevo bus.
 */
i2c_master_bus_handle_t i2c_bus_get_handle(void);