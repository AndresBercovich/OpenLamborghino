#include "config.h"

void TB6612FNG_init() {
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
}

void MotorIz(int value) {
  value = constrain(value,-255,255);
  if(value == 0){
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
  }
  else if (value > 0) {
    // si valor positivo vamos hacia adelante
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
  } else {
    // si valor negativo vamos hacia atras
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
  }

  // Setea Velocidad
  analogWrite(PWMA, abs(value));
}


void MotorDe(int value) {
  value = constrain(value,-255,255);
  if(value == 0){
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW);
  }
  else if (value > 0) {
    // si valor positivo vamos hacia adelante
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
  } else {
    // si valor negativo vamos hacia atras
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
  }

  // Setea Velocidad
  analogWrite(PWMB, abs(value));
}


void Motores(int left, int right) {
  MotorIz(left);
  MotorDe(right);
}
