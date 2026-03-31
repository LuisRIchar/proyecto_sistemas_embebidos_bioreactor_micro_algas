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
#include "stdlib.h"
#include "time.h"

//Librerias externas
#include "pantalla_oled.h"
#include "u8g2_esp32_hal.h"
#include "u8g2.h"
#include "gestor_datos.h"

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

    static char buffer[20];
    static const uint8_t image_alga_bits[] = {0x80,0x01,0x00,0xf0,0x3e,0x00,0x0c,0x30,0x00,0xc6,0x37,0x00,0x73,0x38,0x00,0x1d,0xf0,0x01,0x07,0x30,0x06,0x00,0x30,0x0c,0x00,0x70,0x18,0x00,0xfc,0x10,0x00,0x3c,0x13,0x00,0x0c,0x1e,0xc0,0x0f,0x00,0x70,0x1c,0x00,0x18,0x6c,0x00,0x08,0xcc,0x03,0x04,0x1f,0x0e,0xc3,0x3c,0x18,0x61,0x6c,0x10,0x31,0xcc,0x1b,0x0f,0x0c,0x0c,0x00,0xfc,0x00,0x00,0xbc,0x03,0x00,0x30,0x3e,0x00,0x30,0x20,0x00,0xf0,0x20,0x00,0xb0,0x21,0x00,0x30,0x2f,0x00,0x30,0x30,0x00,0xfe,0x00,0x00,0xba,0x07,0xc0,0x33,0x0c,0x60,0x30,0x08,0x30,0x70,0x08,0x90,0xfd,0x0d,0xf0,0x33,0x07,0x00,0x30,0x00,0x00,0x30,0x00,0x00,0x30,0x00,0x00,0x30,0x00,0x00,0x30,0x00,0x00,0x30,0x00};
    static const uint8_t image_bbl1_bits[] = {0x0e,0x11,0x11,0x11,0x0e};

    //Animacion algas
    static uint8_t coordenadas[4][2] = {{29,17},{4,12},{10,0},{23,6}};
    srand(time(NULL)); //Para generar nueva semilla de secuencias

    static int8_t ran[4]; //4 por el numero de burbujas

    while(1){

    for(int i=0;i<4;i++){
        //ran[i] = (rand() %6) +1; //de 0 a 6
        ran[i] = -4 +(rand() %10); //de -4 a 5
    }

    float turb = get_turbidez();

    u8g2_ClearBuffer(&u8g2_lib); 

    u8g2_SetBitmapMode(&u8g2_lib, 1);
    u8g2_SetFontMode(&u8g2_lib, 1);

    u8g2_SetFont(&u8g2_lib, u8g2_font_t0_12b_tr);
    u8g2_DrawStr(&u8g2_lib, 49, 26, "Nivel de ntu:");

    u8g2_DrawFrame(&u8g2_lib, 41, 30, 81, 21);
    
    sprintf(buffer," %.2f ntu",turb);
    u8g2_DrawStr(&u8g2_lib, 46, 45, buffer);

    u8g2_DrawXBM(&u8g2_lib, 8, 22, 22, 42, image_alga_bits);

    u8g2_DrawXBM(&u8g2_lib, coordenadas[0][0]+ran[0], coordenadas[0][1], 5, 5, image_bbl1_bits);

    u8g2_DrawXBM(&u8g2_lib, coordenadas[1][0]+ran[1], coordenadas[1][1], 5, 5, image_bbl1_bits);

    u8g2_DrawXBM(&u8g2_lib, coordenadas[2][0]+ran[2], coordenadas[2][1], 5, 5, image_bbl1_bits);

    u8g2_DrawXBM(&u8g2_lib, coordenadas[3][0]+ran[3], coordenadas[3][1], 5, 5, image_bbl1_bits);

    u8g2_SendBuffer(&u8g2_lib); 

    vTaskDelay(pdMS_TO_TICKS(200));

    }
}

void Init_pantalla(uint8_t sda,uint8_t sck){
    
    oled.SCK = sck;
    oled.SDA = sda;

    xTaskCreatePinnedToCore(pantalla_principal,"oled_pantalla",8192,&oled,1,NULL,0);
}