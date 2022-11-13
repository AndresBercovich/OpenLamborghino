#include "config.h"

int base = 100;
float Kprop = 1.2;
float Kderiv = 7.5;
float Kinte = 0.0;
int pos;

int side_sensor_x[2]; //LEFT, RIGHT
int his_sensor_x[2][2]; //LEFT, RIGHT

bool state = 0;
int finish_count = 0;
unsigned long ms = 0;

void setup() {
  Serial.begin(115200);
  pinMode(13, OUTPUT);
  
  pinMode(PINLEDON, OUTPUT);
  digitalWrite(PINLEDON, HIGH);

  digitalWrite(13, LOW);
  Serial.println("hola");
  Motores(0, 0);
  WaitBoton();
  digitalWrite(13, HIGH);
  Peripherals_init();

  beep();
  delay(1000);
  calibracion();

  digitalWrite(13, LOW);
  tone(PINBUZZER, 1500, 50);
  delay(70);
  tone(PINBUZZER, 1500, 50);
  delay(70);

  
}


void loop() {
  if(state || millis() - ms < 300){
    int line_position = GetPos();
    int Correction_power = PIDLambo(line_position, Kprop, Kderiv, Kinte);
    #ifdef PID
    Motores(base + Correction_power, base + -Correction_power);
    #endif
    #ifdef DEBUG 
      Serial.print(line_position);
      Serial.print("\t");
      Serial.println(Correction_power);
    #endif

    getGeo();
    if(finish_count >= 2){
      state = false;
    }
    else{
      ms = millis();
    }
  }
  else{
    digitalWrite(13, LOW);
    Motores(0,0);
    tone(PINBUZZER, 4000, 50);
    delay(70);
    tone(PINBUZZER, 4000, 50);
    delay(70);
    tone(PINBUZZER, 4000, 50);
    delay(70);
    tone(PINBUZZER, 4000, 50);
    delay(70);
    WaitBoton();
    delay(1000);
    digitalWrite(13, HIGH);
    state = true;
    finish_count = 0;
    base += 25;
    ms = millis();
  }
  
/*
  Serial.print(analogRead(A7));
  Serial.print("\t");
  Serial.print(analogRead(A6));
  Serial.print(" / ");
  Serial.print(analogRead(A5));
  Serial.print(" / ");
  Serial.print(analogRead(A4));
  Serial.print(" / ");
  Serial.print(analogRead(A3));
  Serial.print(" / ");
  Serial.print(analogRead(A2));
  Serial.print(" / ");
  Serial.print(analogRead(A1));
  Serial.print("\t");
  Serial.println(analogRead(A0));
*/
}
