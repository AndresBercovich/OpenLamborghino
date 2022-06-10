#include <OpenTB6612FNG.h>
#include <OpenLamborghino.h>

#define BOTON  12
#define BUZZER  10

int setpoint = 0;
int gyroSpeed = 80;
int base = 40;


float Kprop = 1.1;
float Kderiv = 0.9;
float Kinte = 0.1;

OpenLamborghino OpenLamborghino(BOTON, BUZZER);
OpenTB6612FNG OpenTB6612FNG(0);

void setup() {
  Serial.begin(9600);
  OpenLamborghino.WaitBoton();
  OpenLamborghino.calibracion();
  OpenLamborghino.WaitBoton();
  delay(1000);
}
void loop() {

  Serialin();
  int pos =  OpenLamborghino.LineaNegra();
  OpenLamborghino.PIDLambo(Kprop, Kderiv, Kinte);
  int Power = OpenLamborghino.PID(pos, setpoint, gyroSpeed);
  OpenTB6612FNG.Motores(base - Power, base + Power );

}


void Serialin() {

  if (Serial.available() > 0) {

    tone(BUZZER, 1300, 100);
    base = Serial.parseInt();
    Kprop = Serial.parseInt() / 10.0;
    Kderiv = Serial.parseInt() / 10.0;
    Kinte = Serial.parseInt() / 10.0;
    setpoint = Serial.parseInt();

    if (Serial.readString() == ('\n')) {
      Serial.flush();
    }
  }
}
