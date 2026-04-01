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

#include "bh1750_luz.h"

#include "stdio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c_master.h"
#include "esp_log.h"
#include "bh1750.h"
#include "i2c_bus_compartido.h"  
#include "gestor_datos.h"

static const char* TAG = "Sensor_de_luz";

static luz_t bh_sensor;

void medir_luz(void* pv){

    luz_t* sensor = (luz_t*)pv;

    // Ya NO se crea un bus nuevo — se pide el handle ya inicializado
    i2c_master_bus_handle_t bus_handle = i2c_bus_get_handle();

    bh1750_handle_t bh1750;
    bh1750_create(bus_handle,BH1750_I2C_ADDRESS_DEFAULT,&bh1750);
    bh1750_set_measure_mode(bh1750,BH1750_CONTINUE_1LX_RES);

    float luz=0;

    //Nivel bajo  1000 a 3000 lux
    //nivel medio útil: 3000 a 10000 lux
    //Alto 10000 a 20000+ lux
    while(1){ 
        bh1750_get_data(bh1750,&luz);
        ESP_LOGI(TAG,"Luz recibida: %.2f lux",luz);
        set_lux(luz);
        vTaskDelay(pdMS_TO_TICKS(500));
    }

}

void Init_sensor_luz(uint8_t sda,uint8_t scl){

    ESP_LOGI(TAG,"Sensor de luz iniciado\n");
    bh_sensor.sda = sda;
    bh_sensor.scl = scl;

    xTaskCreatePinnedToCore(medir_luz,"sensor_luz",5000,&bh_sensor,2,NULL,0);
}
