/*
 Codigo Diseñado por alx2404x Prohibido su uso sin previa autorizacion.Copyright 2022 alx2404x
 */

#include <Arduino.h>
/*
practica 1
control ON/OFF de un diodo led mediante un pulsador.
Control de luminosidad de un diodo led.
   
*/



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

void setup() {
Serial.begin(115200);                           //  depuración 
ledcSetup(PWM_canal, PWM_frec, PWM_resolucion); // configurar PWM
pinMode(pulsador,INPUT_PULLUP);                 // pulsador
pinMode(led_pulsador, OUTPUT);                  // led on/off
ledcAttachPin(led_PWM, PWM_canal);               // led dimmer

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
     if(brillo <= 0){
       brillo =  0;                                 //brillo minimo igual 0
     }
   }
  
   digitalWrite(led_pulsador, digitalRead(pulsador));

  Serial.println("Sensor 1 = " + String(sensor_1));
  Serial.println("Sensor 0 = " + String(sensor_0));
  Serial.println("Brillo = " + String(brillo));
  ledcWrite(PWM_canal, brillo);
  

  
  delay(500);


  

   
  

  
}