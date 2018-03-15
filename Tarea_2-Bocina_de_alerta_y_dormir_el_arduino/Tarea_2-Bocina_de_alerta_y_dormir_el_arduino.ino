/*
 ---------------------------------------------
Se desarrollara un programa que realice una simulacion de una
puerta que se abre debe sonar una alarma donde avice que una 
persona abrio la puerta y como algo extra que se le va poner un
led de alerta y tambien un potenciometro para ajustar el brillo y
otro potenciometro para ajustar la frecuencia del sonido de la bocina.
 ---------------------------------------------
*/
//Aqui traemos la libreria de LowPower para dormir el arduino
#include "LowPower.h"
//--------------------------------------------------
//Declarar puertos de entradas y salidas y variables
//--------------------------------------------------
int buzzer = 9;  //Pin del buzzer
int tono = 0;    //Pin del potenciometro para ajistar la frecuencia del sonido
int brillo = 1;  //Pin del potenciometro para ajustar el brillo del LED
int led = 8;     //Pin del led
const int pinSensor = 2; //para poder abrir o cerrar el circuito con el SWREED
//------------------------------------
//Funcion principal
//------------------------------------
void setup(){ // Se ejecuta cada vez que el Arduino se inicia
  // No se configuran parametros inciales, pero se
  //coloca la función setup()
  //Para inicializar el Pin del SWREED
  pinMode(pinSensor,INPUT_PULLUP);
}
 
//------------------------------------
//Funcion ciclicla
//------------------------------------
void loop(){ // Esta funcion se mantiene ejecutando
           //  cuando se da energia al Arduino
  //Variable donde se almacena el valor del SWREED
  int value = digitalRead(pinSensor);
  //Variable donde se almacena el valor del potenciometro para ajustar la frecuencia del sonido
  int sensor = analogRead(tono);
  //Variable donde se almacena el valor del potenciometro para ajustar el brillo del led
  int sensorLed = analogRead(brillo);
   
  //Variable donde se escala la frecuencia de 100 a 5000Hz
  int frecuencia = map(sensor,0,1023,100,5000);
  //Variable donde se escala la frecuencia de 0 a 255
  int potenciometroBrillo = map(sensorLed,0,1023,0,255);
  //Variable para guardar el tiempo
  int duracion = 250; 
  //En esta decision muestra que el circuito esta cerrado y entonces esta apagado el pin
  if(value == LOW){
        //Se apaga el led
        digitalWrite(led,LOW);
        //Se pone a dormir el arduino por un minuto. bucle de 15 periodos de 4 segundos para hacer un minuto
        for (int i = 0 ;  i  <  16 ; i++){
          LowPower.powerDown(SLEEP_4S, ADC_OFF, BOD_OFF);
        }        
    }
    else{
        //Funcion tone() que recibe:
        //  1ra posición: Pin del elemento sonoro
        //  2da posición: Frecuencia en Hz
        //  3ra posición: Duración del tono
        tone(buzzer, frecuencia, duracion);
        //1ra, va la Pin que va ser utilizada para el led
        //2da, va el ajuste de energia que va recibir el led
        analogWrite(led,potenciometroBrillo);    
      } 
  delay(100);
}
