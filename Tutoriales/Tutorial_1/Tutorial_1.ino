
#define PINBUZZER 10
#define PINBOTON 2
#define PINLED 13




void setup() {
  Serial.begin(115200);
  Peripherals_init();

  digitalWrite(PINLED, LOW);

  Serial.println("hola, estamos en void setup()");
  WaitBoton();
  digitalWrite(PINLED, HIGH);
}


void loop() {


  Serial.println("Ahora estamos en void loop()");
  delay(1000);


  
}
