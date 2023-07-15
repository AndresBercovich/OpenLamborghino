/*

Este tutorial inicia cuando ya tenemos nuestro robot armado. 

Lo primero que debemos aprender, es a comunicarnos con el robot a través de su interfáz Humano-Máquina.
Para esto, Open Lamborghino tiene los siguientes periféricos: 

- Un botón conectado al pin digital 2 de Arduino Nano.
- Un buzzer conectado en el pin digital 10 de Arduino Nano
- Un led conectado al pin digital 13, conectado en la placa de Arduino.

Con estos periféricos podremos operar el robot y navegar por sus sistemas.


Para esto crearemos las siguientes funciones:

WaitBoton(): El robot queda a la espera de que se presione el botón.
beep(): El buzzer hace bip.

*Puedes revisar estas funciones en la pestaña de Peripherals

*/



#define PINBUZZER 10
#define PINBOTON 2
#define PINLED 13
#define PIN_Sensor_ON 11



void setup() {
  Serial.begin(115200);
  Peripherals_init();
  digitalWrite(PINLED, LOW);



  Serial.println("Hola, ahora estás en el void setup()");

  WaitBoton();
  digitalWrite(PINLED, HIGH);
}


void loop() {


  Serial.println("Ahora estás en el void loop()");
  delay(1000);
}
