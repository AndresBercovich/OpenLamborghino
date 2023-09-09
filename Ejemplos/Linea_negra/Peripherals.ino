/* 

Los periféricos (en inglés Peripherals), tienen por objetivo servir como interfáz de Humano - Máquina. 

Vamos a comunicarnos con el robot utilizando los periféricos. En este caso, Open Lamborghino tiene:

- Un botón, conectado en el pin digital 2.
- Un Buzzer, conectado en el pin digital 10.
- Un LED, conectado en el pin 13, en la placa de Arduino.

En esta pestaña, hay funciones básicas para utilizar los periféricos. 

*/



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
}