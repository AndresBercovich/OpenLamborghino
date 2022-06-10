

 # include "Arduino.h"
 # include "OpenTB6612FNG.h"




 # define AIN1 9    // pin 1 de dirección del Motor Izquierdo
 # define AIN2 4    // pin 2 de dirección del Motor Izquierdo
 # define PWMA 5    // pin PWM del Motor Izquierdo
 # define BIN1 8   // pin 1 de dirección del Motor Derecho
 # define BIN2 7   // pin 2 de dirección del Motor Derecho
 # define PWMB 6    // pin PWM del Motor Derecho

OpenTB6612FNG::OpenTB6612FNG(int TP) {

	pinMode(AIN1, OUTPUT);
	pinMode(AIN2, OUTPUT);
	pinMode(PWMA, OUTPUT);
	pinMode(BIN1, OUTPUT);
	pinMode(BIN2, OUTPUT);
	pinMode(PWMB, OUTPUT);
	
}

void OpenTB6612FNG::MotorIz(int value) {
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

void OpenTB6612FNG::MotorDe(int value) {
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

void OpenTB6612FNG::Motores(int left, int righ) {
	MotorIz(left);
	MotorDe(righ);
}

void OpenTB6612FNG::Frenos(boolean left, boolean righ, int value) {
	// pin STAND BY


	if (left) {
		// pines LEFT motor

		digitalWrite(AIN1, HIGH);
		digitalWrite(AIN2, HIGH);
		analogWrite(PWMA, value);
	}

	if (righ) {
		// pines RIGH motor

		digitalWrite(BIN1, HIGH);
		digitalWrite(BIN2, HIGH);
		analogWrite(PWMB, value);
	}
}

void OpenTB6612FNG::ACTFrenoIz(int value) {


	digitalWrite(AIN1, LOW);
	digitalWrite(AIN2, LOW);
	analogWrite(PWMA, value);

}

void OpenTB6612FNG::ACTFrenoDe(int value) {


	digitalWrite(BIN1, LOW);
	digitalWrite(BIN2, LOW);
	analogWrite(PWMB, value);

}

void OpenTB6612FNG::PASFrenoIz(int value) {


	digitalWrite(AIN1, HIGH);
	digitalWrite(AIN2, HIGH);
	analogWrite(PWMA, value);

}

void OpenTB6612FNG::PASFrenoDe(int value) {


	digitalWrite(BIN1, HIGH);
	digitalWrite(BIN2, HIGH);
	analogWrite(PWMB, value);

}
