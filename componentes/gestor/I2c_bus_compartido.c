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

#include "i2c_bus_compartido.h"
#include "driver/i2c_master.h"

static i2c_master_bus_handle_t bus_handle = NULL;

void i2c_bus_init(uint8_t sda, uint8_t scl) {
    if (bus_handle != NULL) return; // ya fue inicializado

    i2c_master_bus_config_t bus_cfg = {
        .i2c_port                     = I2C_NUM_0,
        .sda_io_num                   = sda,
        .scl_io_num                   = scl,
        .clk_source                   = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt            = 7,
        .flags.enable_internal_pullup = true,
    };
    i2c_new_master_bus(&bus_cfg, &bus_handle);
}

i2c_master_bus_handle_t i2c_bus_get_handle(void) {
    return bus_handle;
}