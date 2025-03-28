// Variables globales

bool HL_flag = 0;  // Bandera para indicar que el sensor lateral izquierdo ha detectado un pad.
bool HR_flag = 0;  // Bandera para indicar que el sensor lateral derecho ha detectado un pad.

unsigned long flag_ms = 0;  // Almacena el tiempo en milisegundos desde la última detección de un pad.

/**
 * @brief Detecta y maneja los eventos basados en la lectura de los sensores laterales.
 * 
 * Esta función evalúa las lecturas de los sensores laterales (HL y HR) para determinar si el robot
 * ha pasado por un pad de curva, cruce, o un pad de inicio/fin de pista. Dependiendo del evento detectado,
 * se ejecuta una función específica.
 */
void GetGeo() {

  if (HL) {
    HL_flag = 1;         // Activa la bandera si el sensor lateral izquierdo detecta un pad.
    flag_ms = millis();  // Registra el tiempo actual.
  }

  if (HR) {
    HR_flag = 1;         // Activa la bandera si el sensor lateral derecho detecta un pad.
    flag_ms = millis();  // Registra el tiempo actual.
  }

  // Si ambos sensores dejaron de detectar pads y ambas banderas están activadas, es un cruce.
  if (!HL && !HR && HL_flag && HR_flag) {
    HL_flag = 0;
    HR_flag = 0;

    cruce_sensor();  // Llama a la función de manejo de cruces.
  }
  // Si solo el sensor izquierdo detectó un pad y luego dejó de detectarlo, es una curva o fin de pista.
  else if (!HL && !HR && HL_flag && !HR_flag) {
    if (millis() - flag_ms > 100) {  // Asegura un tiempo mínimo para confirmar la detección.
      HL_flag = 0;
      HR_flag = 0;

      curve_sensor();  // Llama a la función de manejo de curvas.
    }
  }
  // Si solo el sensor derecho detectó un pad y luego dejó de detectarlo, es una curva o fin de pista.
  else if (!HL && !HR && !HL_flag && HR_flag) {
    if (millis() - flag_ms > 100) {  // Asegura un tiempo mínimo para confirmar la detección.
      HL_flag = 0;
      HR_flag = 0;

      finish_sensor();  // Llama a la función de manejo de fin de pista.
    }
  }

  // Si alguna bandera está activa por mucho tiempo (más de 1000 ms), se restablecen.
  if (HL_flag || HR_flag) {
    if (millis() - flag_ms > 500) {
      HL_flag = 0;
      HR_flag = 0;
    }
  }
}

/**
 * @brief Se ejecuta cada vez que el robot pasa por un pad de curva.
 * 
 * Esta función emite un tono para indicar que se ha detectado un pad de curva y puede
 * incluir lógica adicional para manejar el evento de curva.
 */
void curve_sensor() {
  tone(PIN_BUZZER, 2000, 50);  // Emite un tono en el buzzer para indicar la detección de una curva.

#ifdef ENABLE_DEBUG
  Serial.println("Paso por pad de curva");  // Imprime un mensaje de depuración.
#endif
}

/**
 * @brief Se ejecuta cada vez que el robot pasa por un pad de inicio o fin de pista.
 * 
 * Esta función emite un tono y aumenta el contador de finalización de pista. Si el contador
 * llega a 2, el robot se detendrá.
 */
void finish_sensor() {
  tone(PIN_BUZZER, 3000, 50);  // Emite un tono en el buzzer para indicar la detección de un pad de fin de pista.
  finish_count++;              // Incrementa el contador de pads de inicio/fin de pista.

#ifdef ENABLE_DEBUG
  Serial.print("Paso por pad de inicio/termino finish_count = ");
  Serial.println(finish_count);  // Imprime el valor actual del contador de pads.
#endif
}

/**
 * @brief Se ejecuta cada vez que el robot pasa por un cruce.
 * 
 * Esta función emite un tono para indicar que se ha detectado un cruce y resetea el contador
 * de finalización de pista si es necesario.
 */
void cruce_sensor() {
  tone(PIN_BUZZER, 1000, 50);  // Emite un tono en el buzzer para indicar la detección de un cruce.

  if (finish_count >= 2)
    finish_count = 1;  // Resetea el contador si ha llegado a 2 para evitar que el robot se detenga.

#ifdef ENABLE_DEBUG
  Serial.print("Paso por cruce");  // Imprime un mensaje de depuración.
#endif
}
