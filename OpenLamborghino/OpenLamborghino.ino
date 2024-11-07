/*
Conexión de los sensores analógicos

HR -> A0    // Sensor lateral derecho
D2 -> A1    // Sensor de línea 2
D3 -> A2    // Sensor de línea 3
D4 -> A3    // Sensor de línea 4
D5 -> A4    // Sensor de línea 5
D6 -> A5    // Sensor de línea 6
D7 -> A6    // Sensor de línea 7
HL -> A7    // Sensor lateral izquierdo

Los D2 a D7 corresponden a los sensores de línea en el frontal del robot.
Cabe resaltar que solo se están utilizando 6 de los 8 sensores en la regleta.
Esto es debido a que el Arduino Nano solo tiene 8 entradas analógicas, y se requieren 2 entradas para los sensores laterales.
*/

#define PIN_BUZZER 10     // Pin conectado al buzzer.
#define PIN_BOTON 2       // Pin conectado al botón de inicio.
#define PIN_LED 13        // Pin conectado al LED indicador.
#define PIN_Sensor_ON 11  // Pin para activar los sensores.

// Canal A del TB6612, conectado al Motor Izquierdo
#define PIN_AIN1 7  // Pin 1 de dirección del Motor Izquierdo.
#define PIN_AIN2 4  // Pin 2 de dirección del Motor Izquierdo.
#define PIN_PWMA 5  // Pin PWM del Motor Izquierdo.

// Canal B del TB6612, conectado al Motor Derecho
#define PIN_BIN1 8  // Pin 1 de dirección del Motor Derecho.
#define PIN_BIN2 9  // Pin 2 de dirección del Motor Derecho.
#define PIN_PWMB 6  // Pin PWM del Motor Derecho.

#define kp 0.07  // Constante proporcional para el control PID.
#define kd 0.8   // Constante derivativa para el control PID.

// Define para habilitar o deshabilitar los mensajes de depuración
// #define ENABLE_DEBUG

// Define para habilitar la función de detección de hits
#define ENABLE_HITS

int base_speed = 70;  // Velocidad base del robot.

bool linea = 0;   // 1 para línea negra, 0 para línea blanca.
bool online = 0;  // Indica si el robot está detectando la línea.

bool HL = 0;  // Estado del sensor lateral izquierdo.
bool HR = 0;  // Estado del sensor lateral derecho.

bool state = 0;               // Flag que indica el estado de actividad del robot.
int finish_count = 0;         // Contador de vueltas completadas.
unsigned long finish_ms = 0;  // Contador de tiempo desde el cruce por meta.

/**
 * @brief Configura los pines, calibra los sensores y prepara el robot para iniciar.
 *
 * Esta función se ejecuta una vez al inicio y realiza la configuración inicial de los pines,
 * además de guiar al usuario a través del proceso de calibración de los sensores.
 */
void setup() {
#ifdef ENABLE_DEBUG
  Serial.begin(115200);  // Inicializa la comunicación serial para depuración.
#endif

  // Configura los pines como entradas o salidas
  pinMode(PIN_BOTON, INPUT_PULLUP);
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_Sensor_ON, OUTPUT);

  pinMode(PIN_AIN1, OUTPUT);
  pinMode(PIN_AIN2, OUTPUT);
  pinMode(PIN_PWMA, OUTPUT);
  pinMode(PIN_BIN1, OUTPUT);
  pinMode(PIN_BIN2, OUTPUT);
  pinMode(PIN_PWMB, OUTPUT);

  digitalWrite(PIN_LED, LOW);
  delay(500);

  Stop_Motores(false);  // Detiene los motores al inicio.

  blick();  // Parpadea el LED.
  beep();   // Emite un beep.

#ifdef ENABLE_DEBUG
  Serial.println("hola, vamos a calibrar a Open Lamborghino, para leer la línea negra");
  Serial.println("Instrucciones:   ");
  Serial.println(" 1 .- Pon a Open Lamborghino sobre la pista");
  Serial.println(" 2 .- Presiona el botón de Open Lamborghino, y comienza a pasar el sensor de línea y laterales hasta que suene los 2 beeps");
  Serial.println(" Consejos para la calibracion:");
  Serial.println(" - Asegurate de que el robot no se levante durante la calibracion");
  Serial.println(" - El movimiento debe ser hacia adelante y hacia atras, a una velocidad moderadamente rapida");
  Serial.println(" - Los sensores laterales tambien son parte de la calibracion, por esto tambien deben pasar por la linea");
#endif

  WaitBoton();         // Espera a que el usuario presione el botón para iniciar la calibración.
  Calibracion();       // Realiza la calibración de los sensores.
  Stop_Motores(true);  // Detiene los motores después de la calibración.

#ifdef ENABLE_DEBUG
  Serial.println(" 1 .- Pon a Open Lamborghino sobre la pista, pero fuera de la linea");
  Serial.println(" 2 .- Presiona el botón de Open Lamborghino, procura que el robot no se levante en esto");
  Serial.println(" Con esto el robot detectara el color de la lista");
#endif

  WaitBoton();          // Espera a que el usuario presione el botón para detectar el color de la pista.
  Calibracion_Color();  // Realiza la calibración de color.

  delay(1000);

#ifdef ENABLE_DEBUG
  Serial.println("Open Lamborghino ya está calibrado. Presiona el botón nuevamente para comenzar");
#endif
}

/**
 * @brief Bucle principal del robot que se ejecuta continuamente.
 *
 * Esta función contiene la lógica principal del robot para seguir la línea y manejar
 * eventos como la detección de pads o el cruce de la línea de meta.
 */
void loop() {
  if (state) {                             // Verifica si el robot está en estado activo o si ha cruzado recientemente la línea de meta.
    int pos = GetPos();                    // Obtiene la posición del robot respecto a la línea.
    int Correction_power = PIDLambo(pos);  // Calcula la corrección necesaria usando el controlador PID.

    // Ajusta la velocidad de los motores en función de la corrección calculada.
    Set_Motores(base_speed + Correction_power, base_speed + -Correction_power, false);

    GetGeo();  // Verifica la detección de pads o cruces.

#ifdef ENABLE_HITS
    if (finish_count == 2) {  // Si el robot ha completado dos vueltas, se detiene.
      finish_ms = millis();   // Actualiza el tiempo del último cruce por meta.
      finish_count = 3;
    } else if (finish_count == 3) {
      if (millis() - finish_ms > 300)
        state = false;
    }
#endif

    if (!digitalRead(PIN_BOTON))  // Si se presiona el botón, el robot se detiene.
      state = false;

    // Enciende el LED si el robot está online y no detecta ningún pad.
    digitalWrite(PIN_LED, !HL && !HR);

#ifdef ENABLE_DEBUG
    // Imprime información de depuración.
    Serial.print(pos);
    Serial.print("\t");
    Serial.print(Correction_power);
    Serial.print("\t");
    Serial.print(online);
    Serial.print("\t");
    Serial.print(HR);
    Serial.print("\t");
    Serial.println(HL);
#endif
  } else {  // Si el robot no está activo, se detiene y espera el botón.
    digitalWrite(PIN_LED, LOW);
    digitalWrite(PIN_Sensor_ON, LOW);
    Stop_Motores(true);  // Detiene los motores.

    // Emite una serie de beeps para indicar que el robot está en modo de espera.
    tone(PIN_BUZZER, 4000, 50);
    delay(70);
    tone(PIN_BUZZER, 4000, 50);
    delay(70);
    tone(PIN_BUZZER, 4000, 50);
    delay(70);
    tone(PIN_BUZZER, 4000, 50);
    delay(70);

    WaitBoton();  // Espera a que se presione el botón para reiniciar.
    delay(1000);
    digitalWrite(PIN_LED, HIGH);
    digitalWrite(PIN_Sensor_ON, HIGH);
    state = true;
    finish_count = 0;
    //base_speed += 5;       // Incrementa la velocidad base después de cada inicio.
  }
}

/**
 * @brief Espera a que se presione el botón.
 *
 * Esta función mantiene el robot en un bucle hasta que el usuario presione el botón,
 * lo que es útil para pausar o iniciar el robot manualmente.
 */
void WaitBoton() {  // Entra en un bucle infinito de espera.
  while (digitalRead(PIN_BOTON))
    ;  // Se sale del bucle cuando se presiona el botón.
  while (!digitalRead(PIN_BOTON))
    ;  // Espera hasta que se suelte el botón si está presionado.
}

/**
 * @brief Emite un sonido en el buzzer.
 *
 * Esta función emite un tono de 2000 Hz durante 100 ms, seguido de un pequeño retraso,
 * lo que es útil para proporcionar retroalimentación auditiva al usuario.
 */
void beep() {
  tone(PIN_BUZZER, 2000, 100);  // Emite un tono de 2000 Hz durante 100 ms.
  delay(200);                   // Espera 200 ms antes de continuar.
}

/**
 * @brief Parpadea el LED conectado al robot.
 *
 * Esta función enciende y apaga el LED conectado al robot, útil para proporcionar
 * señales visuales durante el proceso de calibración o para indicar el estado del robot.
 */
void blick() {
  digitalWrite(PIN_LED, HIGH);
  delay(100);
  digitalWrite(PIN_LED, LOW);
  delay(100);
}
