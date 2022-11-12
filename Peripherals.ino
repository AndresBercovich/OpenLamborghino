#include "config.h"

void Peripherals_init() {
  pinMode(PINBOTON, INPUT);
  pinMode(PINBUZZER, OUTPUT);
}


void WaitBoton() {   // Entra en un bucle infinito de espera.
  while (!digitalRead(PINBOTON));  // Se sale del bucle cuando se aprieta el botón
  tone(PINBUZZER, 2000, 100);      // Cuando sale del bucle, suena el buzzer
}

void beep() {
  tone(PINBUZZER, 2000, 100);
  delay(200);
}
