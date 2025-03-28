#define PINBUZZER 10
#define PINBOTON 2
#define PINLED 13
#define PIN_Sensor_ON 11





void setup() {
  Serial.begin(115200);
  Peripherals_init();
  Sensors_init();

  digitalWrite(PINLED, LOW);
  delay(500);

  Serial.println("hola, vamos a calibrar a Open Lamborghino");
  Serial.println("Instrucciones:   ");


  Serial.println(" 1 .- Pon a Open Lamborghino sobre la pista");
  Serial.println(" 2 .- Presiona el botón de Open Lamborghino, y comienza a pasar el sensor de línea hasta que suene los 2 beeps");
  delay(500);


  WaitBoton();
  calibracion();

  digitalWrite(PINLED, HIGH);

  delay(3000);

  Serial.println("Open Lamborghino ya está calibrado. Presiona el botón nuevamente para comenzar a obtener la lectura de la posición");
  WaitBoton();
  delay(1000);
}


void loop() {
  int p = GetPos();

  Serial.println(p);
  delay(1);
}
