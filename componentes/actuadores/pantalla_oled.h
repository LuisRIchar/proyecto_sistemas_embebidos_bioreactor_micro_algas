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

#ifndef PANTALLA_OLED_H
#define PANTALLA_OLED_H

#define ADDR_PANTALLA 0x3c<<1 //Pantalla ssd1306

typedef struct {
    uint8_t SDA;
    uint8_t SCK;
}i2c_pantalla_t;

void pantalla_principal(void* pv);
void Init_pantalla(uint8_t sda,uint8_t sck);
#endif