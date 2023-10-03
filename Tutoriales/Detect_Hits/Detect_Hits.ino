


#define PINBUZZER 10
#define PINBOTON 2
#define PINLED 13
#define PIN_Sensor_ON 11



int velocidad_1 = 50;
int velocidad_2 = 80;
int velocidad_3 = 100;
int velocidad_4 = 120;
int velocidad_5 = 150;

int posicion_ideal = 0;


float Kprop = 1.0;
float Kderiv = 6.0;

int base = 50;
int error_pasado = 0;


void setup() {
  Serial.begin(115200);
  Peripherals_init();
  TB6612FNG_init();
  Sensors_init();

  digitalWrite(PINLED, LOW);
  delay(500);

  Motores(0, 0);

  Serial.println("Programa Básico");

  delay(500);
  WaitBoton();
  calibracion();


  WaitBoton();

  base = velocidad_1;
  delay(1000);
}


void loop() {

  int p = GetPos();

  detectGeo();

  int error = p - posicion_ideal;
  int d_error = error - error_pasado;
  int correction_power = int(Kprop * error) + int(Kderiv * (d_error));


  if (correction_power > 255) {
    correction_power = 255;

  }

  else if (correction_power < -255) {
    correction_power = -255;
  }





  Motores(base + correction_power, base + -correction_power);
  error_pasado = error;
}
