// Definición de pines
#define PINBUZZER 10
#define PINBOTON 2
#define PINLED 13

// Función para esperar el botón
void WaitBoton() {
  // Entra en un bucle infinito de espera hasta que se presione el botón
  while (!digitalRead(PINBOTON)); // No hace nada dentro del bucle, solo espera
  beep(); // Se llama a la función beep() cuando se presiona el botón
}

// Función para emitir un sonido
void beep() {
  tone(PINBUZZER, 2000, 100); // Emite un tono de 2000 Hz durante 100 ms
  delay(200); // Espera 200 ms antes de continuar
}

void Peripherals_init() {
  // Configuración de pines
  pinMode(PINBOTON, INPUT); // El pin del botón se configura como entrada
  pinMode(PINBUZZER, OUTPUT); // El pin del buzzer se configura como salida
  pinMode(PINLED, OUTPUT); // El pin del LED se configura como salida
// Definición de pines
#define PINBUZZER 10
#define PINBOTON 2
#define PINLED 13

// Función para esperar el botón
void WaitBoton() {
  // Entra en un bucle infinito de espera hasta que se presione el botón
  while (!digitalRead(PINBOTON)); // No hace nada dentro del bucle, solo espera
  beep(); // Se llama a la función beep() cuando se presiona el botón
}

// Función para emitir un sonido
void beep() {
  tone(PINBUZZER, 2000, 100); // ReEmite un tono de 2000 Hz durante 100 ms
  delay(200); // Espera 200 ms antes de continuar
}

void Peripherals_init() {
  // Configuración de pines
  pinMode(PINBOTON, INPUT); // El pin del botón se configura como entrada
  pinMode(PINBUZZER, OUTPUT); // El pin del buzzer se configura como salida
  pinMode(PINLED, OUTPUT); // El pin del LED se configura como salida


}
