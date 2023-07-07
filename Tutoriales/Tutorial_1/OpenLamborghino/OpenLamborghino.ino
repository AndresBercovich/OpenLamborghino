
#define PINBUZZER 10
#define PINBOTON 2
#define PINLED 13




void setup() {
  Serial.begin(115200);
  Peripherals_init();

  digitalWrite(PINLED, LOW);

  Serial.println("hola, estamos ejecutando void Setup()");


  WaitBoton();

  digitalWrite(PINLED, HIGH);
}


void loop() {

Seriall.println("Estamos en el el void loop()");

}
