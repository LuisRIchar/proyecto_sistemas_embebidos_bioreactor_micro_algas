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

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

typedef struct{
    float ntu;
    SemaphoreHandle_t turbidez_mutex;
}datos_turbidez_t;

typedef struct{
    float lux;
    SemaphoreHandle_t lux_mutex;
}datos_lux_t;

typedef struct{
    float val_temp;
    SemaphoreHandle_t temp_mutex;
}datos_temp_t;

 float get_turbidez(void);
 void set_turbidez(float ntu);
 float get_lux(void);
 void set_lux(float lux);
 float get_temp(void);
 void set_temp(float temperatura_sensor);
 void Init_gestor_datos(void);