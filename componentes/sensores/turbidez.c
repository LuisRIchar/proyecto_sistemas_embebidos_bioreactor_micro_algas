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


#include "turbidez.h"
#include "stdio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "stdint.h"
#include "driver/adc.h"
#include "math.h"
#include "gestor_datos.h"

static pin_turbidez_t turbidez_pin;
static float factor_divisor = 1.51;

uint16_t crudoADC(void){
    return adc1_get_raw(turbidez_pin.pin);
}

void sensor_turbidez(void* pv){
    uint16_t crudos = 0;
    while(1){
        crudos = crudoADC();
        float voltaje_esp = (crudos * 3.3) / 4095.0; 
        
        //Reconstruyes el voltaje que ENTREGÓ el sensor (0 a 5V)
        float voltaje_real = voltaje_esp * factor_divisor;

        // Aplicas la fórmula (Cuidado: el voltaje_real no debe ser > 4.2)
        //NTU significa Nephelometric Turbidity Units (Unidades Nefelométricas de Turbidez).
        //Mide cuánta luz se dispersa en el agua por partículas en suspensión 
        //0–1 NTU: agua muy clara.
        //1–5 NTU: ligera turbidez, aún puede verse clara.
        //5–25 NTU: turbidez moderada, ya se nota opacidad.
        //25–100 NTU: turbidez alta, agua bastante turbia.
        //>100 NTU: turbidez muy alta, agua muy cargada de sólidos.
        float ntu = 0;
        if(voltaje_real >= 4.2){
            ntu = 0;
        } else if(voltaje_real <= 2.5){
            ntu = 3000;
        } else {
            ntu = -1120.4 * pow(voltaje_real, 2) + 5742.3 * voltaje_real - 4353.8;
        }

        printf("V_ESP: %.2f | V_Real: %.2f | NTU: %.2f\n", voltaje_esp, voltaje_real, ntu);
        set_turbidez(ntu);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void Init_sensor_turbidez(adc1_channel_t gpio){
    turbidez_pin.pin = gpio;

    adc1_config_width(ADC_WIDTH_BIT_12);//4096
    adc1_config_channel_atten(turbidez_pin.pin,ADC_ATTEN_DB_12);

    xTaskCreatePinnedToCore(sensor_turbidez,"sensor_turbidez",5000,&turbidez_pin,2,NULL,1);
}
