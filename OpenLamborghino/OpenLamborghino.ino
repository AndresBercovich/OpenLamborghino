#define PINBUZZER 10
#define PINBOTON 2
#define PINLED 13
#define PIN_Sensor_ON 11


int base = 0;
float Kprop = 1.2;
float Kderiv = 7.5;


void setup() {
  Serial.begin(115200);
  Peripherals_init();
  TB6612FNG_init();
  Sensors_init();
  digitalWrite(PINLED, LOW);

  Serial.println("hola");
  Motores(0, 0);
  WaitBoton();
  digitalWrite(PINLED, HIGH);
 
  delay(2000);
  calibracion();
  digitalWrite(PINLED, LOW);


  WaitBoton();
  delay(1000);
  digitalWrite(PINLED, HIGH);
}


void loop() {

  int line_position = GetPos();
  int Correction_power = PIDLambo(line_position, Kprop, Kderiv);
  Motores(base + Correction_power, base + -Correction_power);
  Serial.print(line_position);
  Serial.print("\t");
  Serial.println(Correction_power);
}
