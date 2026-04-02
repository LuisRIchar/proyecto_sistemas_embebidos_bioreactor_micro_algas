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
#include "calentador_relay.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "gestor_datos.h"

static const char* TAG ="Relay_calentador";

static relay_pin_t pin_relay;

void logica_relay(void* pv){
    relay_pin_t* relay = (relay_pin_t*)pv;

    gpio_config_t relay_cfg = {
        .pin_bit_mask = (1ULL<<relay->gpio_relay),
        .mode = GPIO_MODE_OUTPUT,
    };
    gpio_config(&relay_cfg);

    float temperatura;

    //El relay ocupado funciona con logica invertida
    // 0 = encendido, 1 = apagado

    while(1){

        temperatura = get_temp();

        if(temperatura>=24.0f){
            gpio_set_level(relay->gpio_relay,1);
        }else{
            gpio_set_level(relay->gpio_relay,0);
        }

        vTaskDelay(pdMS_TO_TICKS(500));

    }
}

void Init_relay_calentador(gpio_num_t num){
    ESP_LOGI(TAG,"logica relay inicializado");

    pin_relay.gpio_relay = num;

    xTaskCreatePinnedToCore(logica_relay,"relay",4096,&pin_relay,3,NULL,1);

}
