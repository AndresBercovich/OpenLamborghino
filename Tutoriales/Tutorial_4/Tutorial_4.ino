#define PINBUZZER 10
#define PINBOTON 2
#define PINLED 13
#define PIN_Sensor_ON 11





void setup() {
  Serial.begin(115200);
  Peripherals_init();
  TB6612FNG_init();
  Sensors_init();

  digitalWrite(PINLED, LOW);
  delay(500);

  Motores(0, 0);

  Serial.println("hola, Cuarta parte del tutorial");
  Serial.println("Ahora combinaremos lo aprendido en los tutoriales pasados.");
  Serial.println("Para eso, primero calibraremos los sensores. Presiona el botón para calibrar...");




  delay(500);
  WaitBoton();
  calibracion();


  WaitBoton();
  Serial.println("ahora que tenemos el robot calibrado, intentaremos seguir una línea con el método de lego");
  Serial.println("Es decir, si el robot está muy a la derecha, haremos que el motore de la derecha vaya hacia adelante...");
  Serial.println("y si el robot está muy a la izquierda, haremos que el motor de la izquierda vaya hacia adelante");
  Serial.println();
  Serial.println();
  Serial.println();


  delay(1000);
}


void loop() {
  int p = GetPos();
  Serial.println(p);

  if (p < 0) {

    Motores(0, 100);
  }


  if (p > 0) {

    Motores(100, 0);
  }



  delay(1);
}
