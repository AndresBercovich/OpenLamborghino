#include "config.h"

int base = 150;


//double Kprop = 2.0;
//double Kderiv = 0.0;
//double Kinte = 0.0;

double Kprop = 1.2;
double Kderiv = 7.5;
double Kinte = 0.0;

double pos;

int side_sensor_x[2]; //LEFT, RIGHT
int his_sensor_x[2][2]; //LEFT, RIGHT

bool state = 0;
int finish_count = 0;
bool curva_trigg = 0;
unsigned long ms = 0;

void setup() {
  Serial.begin(115200);
  pinMode(13, OUTPUT);
  
  pinMode(PINBOTON, INPUT);
  pinMode(PINBUZZER, OUTPUT);
  pinMode(PINLEDON, OUTPUT);
  digitalWrite(PINLEDON, LOW);

  tone(PINBUZZER, 1500, 50);
  delay(70);
  tone(PINBUZZER, 1500, 50);
  delay(70);

  digitalWrite(13, LOW);
  Serial.println("hola");
  Motores(0, 0);
  WaitBoton();

  digitalWrite(13, HIGH);

  tone(PINBUZZER, 2000, 100);
  digitalWrite(PINLEDON, HIGH);
  delay(1000);
  calibracion();

  digitalWrite(13, LOW);
  tone(PINBUZZER, 1500, 50);
  delay(70);
  tone(PINBUZZER, 1500, 50);
  delay(70);

  #ifdef MOTOR_TEST
    Motores(50, 50);
    delay(500);
    Motores(0, 0);
  #endif
  
}


void loop() {
  if(state || millis() - ms < finish_time){
    double line_position = GetPos();
    double Correction_power = PIDLambo(line_position, Kprop, Kderiv, Kinte);

    #ifdef PID
      Motores(base + Correction_power, base + -Correction_power);
    #endif

    #ifdef DEBUG 
      Serial.print(line_position);
      Serial.print("\t");
      Serial.println(Correction_power);
    #endif

    #ifdef HITS
      getGeo();
      if(finish_count >= 2){
        if(curva_trigg){
          finish_count = 1;
          curva_trigg = 0;
          state = true;
        }
        else{
          state = false;
        }
      }
      else{
        ms = millis();
      }
    #else
      ms = millis();
    #endif
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
    base += incremento;
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

void WaitBoton() {   // Entra en un bucle infinito de espera.
  while (!digitalRead(PINBOTON));  // Se sale del bucle cuando se aprieta el botón
  tone(PINBUZZER, 2000, 100);      // Cuando sale del bucle, suena el buzzer
}

double Dmap(double x, double in_min, double in_max, double out_min, double out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
