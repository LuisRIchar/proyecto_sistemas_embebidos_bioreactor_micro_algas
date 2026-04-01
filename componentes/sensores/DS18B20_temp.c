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

#include "DS18B20_temp.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "stdio.h"
#include "esp_log.h"

#include "onewire_bus.h"
#include "ds18b20.h"
#include "gestor_datos.h"

static const char* TAG ="sensor_temperatura";
static temp_t pin_temp;

void ds18b20_leer_temperatura(void* pv){

    temp_t* TEMP = (temp_t*) pv; 

    onewire_bus_handle_t bus;
    onewire_bus_config_t bus_cfg = {
        .bus_gpio_num = TEMP->one_wire_pin_temp,
        .flags = {
            .en_pull_up =true,
        }
    };

    onewire_bus_rmt_config_t rmt_cfg = {
        .max_rx_bytes =10
    };
    onewire_new_bus_rmt(&bus_cfg,&rmt_cfg,&bus);

    onewire_device_iter_handle_t iter;
    onewire_new_device_iter(bus,&iter);

    onewire_device_t dev;
    onewire_device_iter_get_next(iter,&dev);

    ds18b20_device_handle_t sensor;
    ds18b20_config_t ds_conf ={};
    ds18b20_new_device_from_enumeration(&dev,&ds_conf,&sensor);

    float temperatura=0;

    while(1){
        ds18b20_trigger_temperature_conversion(sensor);
        ds18b20_get_temperature(sensor,&temperatura);
        ESP_LOGI(TAG,"Temperatura: %.2f",temperatura);
        set_temp(temperatura);
        vTaskDelay(pdMS_TO_TICKS(300));
    }
}

void Init_sensor_temp(uint8_t gpio_temp){
    ESP_LOGI(TAG,"Sensor de temperatura inicializado");
    pin_temp.one_wire_pin_temp = gpio_temp;

    xTaskCreatePinnedToCore(ds18b20_leer_temperatura,"Temperatura",5000,&pin_temp,2,NULL,1);
}
