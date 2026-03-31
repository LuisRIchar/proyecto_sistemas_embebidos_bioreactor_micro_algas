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
#include "gestor_datos.h"
#include "stdio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"

typedef struct{
    float ntu;
    SemaphoreHandle_t turbidez_mutex;

}datos_turbidez_t;

static datos_turbidez_t turbidez;

float get_turbidez(void){

    xSemaphoreTake(turbidez.turbidez_mutex,portMAX_DELAY);
    float turb = turbidez.ntu;
    xSemaphoreGive(turbidez.turbidez_mutex);
    return turb;
}

void set_turbidez(float ntu){
    xSemaphoreTake(turbidez.turbidez_mutex,portMAX_DELAY);
    turbidez.ntu = ntu;
    xSemaphoreGive(turbidez.turbidez_mutex);
}

void Init_gestor_datos(void){

    turbidez.turbidez_mutex = xSemaphoreCreateMutex();
}