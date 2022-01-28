// Copyright 2022 alx2404x
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
/*
practica 1
control ON/OFF de un diodo led mediante un pulsador.
Control de luminosidad de un diodo led.
   
*/
#include <Arduino.h>

//           - DECLACION DE CTES Y VARIABLES-
const uint8_t PWM_canal =0;                     //seleccion del canal PWM (0 A 15)
const int PWM_frec =     5000;                  //5KHz PWM
const byte PWM_resolucion = 8;                  //ciclo de trabajo de 0 a 255 
const uint8_t pulsador = 2;                    //pulsador
const uint8_t led_pulsador = 12;               //lED ON/OFF
const uint8_t led_PWM = 14;                    //led dimmer
int sensor_0 = 0 , sensor_1 = 0;
const uint8_t umbral_tactil = 20;              //Sensibilidad del sensor
int brillo = 0;
volatile bool bandera = false;
static portMUX_TYPE mutex = portMUX_INITIALIZER_UNLOCKED;
bool conmutador=false;


// Declaracion de Funciones
void IRAM_ATTR conmutar();

void setup() {
Serial.begin(115200);                           //  depuración 
ledcSetup(PWM_canal, PWM_frec, PWM_resolucion); // configurar PWM
pinMode(pulsador,INPUT_PULLUP);                 // pulsador
pinMode(led_pulsador, OUTPUT);                  // led on/off
ledcAttachPin(led_PWM, PWM_canal); // led dimmer

attachInterrupt(digitalPinToInterrupt(pulsador),conmutar, FALLING);              

}


void loop() {

   sensor_0 = touchRead(T4);  //Leer sensores tactiles
   sensor_1 = touchRead(T3);

   if (sensor_0 < umbral_tactil && sensor_0 !=0){
     
     brillo = brillo+5; //aumentar brillo
     if (brillo >= 255){
       brillo = 255 ; //brillo maximo 255

     }

     

   }

   if (sensor_1 <  umbral_tactil && sensor_1 != 0){
     brillo = brillo - 5;
     if(brillo <= 0)
       brillo =  0;                                 //brillo minimo igual 0
     
   }
  
   //digitalWrite(led_pulsador, digitalRead(pulsador));
   if(bandera){
     portENTER_CRITICAL(&mutex);
     bandera = false;
     portEXIT_CRITICAL(&mutex);
     delay(1);
    if(!digitalRead(pulsador)){
      conmutador=!conmutador;
      digitalWrite(led_pulsador, conmutador);
      }
    }

  Serial.println("Sensor 1 = " + String(sensor_1));
  Serial.println("Sensor 0 = " + String(sensor_0));
  Serial.println("Brillo = " + String(brillo));
  ledcWrite(PWM_canal, brillo);
  


  delay(40);


}

// Mas funciones

void IRAM_ATTR conmutar(){

  portENTER_CRITICAL_ISR(&mutex);    //Proteger Bandera
  bandera = true;                    // aviso boton pulsado
  portEXIT_CRITICAL_ISR(&mutex);

  

}