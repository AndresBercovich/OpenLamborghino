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

  Serial.println("hola, en esta tercera parte, nos aseguraremos que tenemos bien conectados los motores");
  Serial.println("Instrucciones:   ");
  Serial.println("");


  Serial.println("Cuando presiones el botón, los dos motores deberían ir hacia adelante.");
  Serial.println("");

  Serial.println("Si algún motor va hacia atrás, cambia la polaridad de conexión del motor, conectando el cable del motor al revés");
  Serial.println("");

  Serial.println("Ahora presiona el botón");


  delay(500);
  WaitBoton();

  Motores(50, 50);

  delay(1000);

  Serial.println("");
  Serial.println("");

  Serial.println("Presiona el botón nuevamente para detener los motores");
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("");
  WaitBoton();
  Motores(0, 0);
  delay(100);

  Serial.println("Si los dos motores se mueven hacia adelante, entonces los motores ya están listos para utilizarse");
  Serial.println("");

  Serial.println("Para utilizar la función motores(x,y), solo debes cambiar la x y la y, por un valor entre -255 y 255.");
  Serial.println("");

  Serial.println("cuando x = 255, el motor izquierdo irá a la máxima potencia hacia adelante");
  Serial.println("cuando x = -255, el motor izquierdo irá a la máxima potencia hacia atrás");
  Serial.println("cuando x = 0, la potencia del motor izquierdo se establecerá en 0");
  Serial.println("");


  Serial.println("anlálogamente, pasará lo mismo con el motor derecho si se modifica la variable y ");

  WaitBoton();


  delay(1000);
}


void loop() {

  delay(1);
  
}
