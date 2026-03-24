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

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "stdio.h"

//Librerias externas
#include "pantalla_oled.h"
#include "u8g2_esp32_hal.h"
#include "u8g2.h"

static i2c_pantalla_t oled;

void pantalla_principal(void* pv){

    i2c_pantalla_t* pantalla_t = (i2c_pantalla_t *) pv;

    u8g2_esp32_hal_t hal =  U8G2_ESP32_HAL_DEFAULT;
    hal.bus.i2c.scl = pantalla_t->SCK;
    hal.bus.i2c.sda = pantalla_t->SDA;

    u8g2_esp32_hal_init(hal);

    u8g2_t u8g2_lib;

    u8g2_Setup_sh1106_i2c_128x64_noname_f(
    &u8g2_lib,U8G2_R0,u8g2_esp32_i2c_byte_cb,u8g2_esp32_gpio_and_delay_cb);
    u8g2_SetI2CAddress(&u8g2_lib.u8x8,ADDR_PANTALLA);

    u8g2_InitDisplay(&u8g2_lib);
    u8g2_SetPowerSave(&u8g2_lib,0);

    static uint8_t phValor = 0;
    static char buffer[30];

    while(1){
    u8g2_ClearBuffer(&u8g2_lib); 
    
    u8g2_SetBitmapMode(&u8g2_lib, 1);
    u8g2_SetFontMode(&u8g2_lib, 1);

    u8g2_SetFont(&u8g2_lib, u8g2_font_t0_12b_tr);
    u8g2_DrawStr(&u8g2_lib, 29, 21, "Nivel de pH:");

    u8g2_DrawFrame(&u8g2_lib, 30, 28, 69, 26);

    sprintf(buffer,"%d.4 pH",phValor);
    u8g2_DrawStr(&u8g2_lib, 49, 44, buffer);

    u8g2_SendBuffer(&u8g2_lib); 

    vTaskDelay(pdMS_TO_TICKS(100));

    phValor++;
    if(phValor == 10) phValor =0;
    }
}

void Init_pantalla(uint8_t sda,uint8_t sck){
    
    oled.SCK = sck;
    oled.SDA = sda;

    xTaskCreatePinnedToCore(pantalla_principal,"oled_pantalla",8192,&oled,1,NULL,0);
}