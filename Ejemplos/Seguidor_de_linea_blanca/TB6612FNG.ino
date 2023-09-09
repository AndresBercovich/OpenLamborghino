


# define AIN1 8    // pin 1 de dirección del Motor Izquierdo
# define AIN2 9    // pin 2 de dirección del Motor Izquierdo
# define PWMA 5    // pin PWM del Motor Izquierdo


# define BIN1 4    // pin 1 de dirección del Motor Derecho
# define BIN2 7    // pin 2 de dirección del Motor Derecho
# define PWMB 6    // pin PWM del Motor Derecho


void TB6612FNG_init() {

  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);

}

void MotorIz(int value) {
  if (value >= 0) {
    // si valor positivo vamos hacia adelante

    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
  } else {
    // si valor negativo vamos hacia atras

    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    value *= -1;
  }

  // Setea Velocidad

  analogWrite(PWMA, value);
}


void MotorDe(int value) {
  if (value >= 0) {
    // si valor positivo vamos hacia adelante

    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
  } else {
    // si valor negativo vamos hacia atras

    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    value *= -1;
  }

  // Setea Velocidad

  analogWrite(PWMB, value);
}


void Motores(int left, int right) {
  MotorIz(left);
  MotorDe(right);
}
