// Variables globales

int s[8];  // Arreglo para almacenar las lecturas directas de los sensores analógicos.

int v_s_min[8] = { 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023 };  // Valores mínimos de calibración para cada sensor.
int v_s_max[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };                          // Valores máximos de calibración para cada sensor.

int s_l[8];  // Arreglo para almacenar las lecturas limitadas al rango de calibración.
int s_n[8];  // Arreglo para almacenar las lecturas normalizadas de los sensores (rango de 0 a 500).

int l_pos;  // Última posición calculada de la línea.

const int his_sensor[2] = { 325, 150 };  // Histéresis para los sensores laterales, usada para detección de pads.


/**
 * @brief Lee los valores de los sensores infrarrojos conectados a los pines analógicos del Arduino.
 */
void LeerSensores() {
  s[0] = analogRead(A7);  // Sensor HL (lateral izquierdo)
  s[1] = analogRead(A6);  // Sensor D7
  s[2] = analogRead(A5);  // Sensor D6
  s[3] = analogRead(A4);  // Sensor D5
  s[4] = analogRead(A3);  // Sensor D4
  s[5] = analogRead(A2);  // Sensor D3
  s[6] = analogRead(A1);  // Sensor D2
  s[7] = analogRead(A0);  // Sensor HR (lateral derecho)
}

/**
 * @brief Realiza la calibración de los sensores infrarrojos para determinar los valores mínimos y máximos.
 * 
 * Esta función es fundamental para ajustar los rangos de los sensores de acuerdo al entorno y condiciones actuales,
 * permitiendo así una lectura precisa de la línea y los pads laterales.
 */
void Calibracion() {
  digitalWrite(PIN_LED, HIGH);  // Enciende un LED indicador para mostrar que la calibración está en proceso.

  beep();  // Indica el inicio de la calibración con un sonido.

  digitalWrite(PIN_Sensor_ON, HIGH);  // Activa los sensores.

  for (int j = 0; j < 1500; j++) {
    LeerSensores();  // Lee los valores de los sensores.

    for (int i = 0; i < 8; i++) {
      if (s[i] < v_s_min[i]) {
        v_s_min[i] = s[i];  // Actualiza el valor mínimo si se encuentra un valor más bajo.
      }

      if (s[i] > v_s_max[i]) {
        v_s_max[i] = s[i];  // Actualiza el valor máximo si se encuentra un valor más alto.
      }
    }

#ifdef ENABLE_DEBUG
    for (int i = 0; i < 8; i++) {
      Serial.print(s[i]);
      Serial.print("\t");
    }
    Serial.println();
#else
    delay(1);  // Pequeña pausa entre lecturas para evitar ruido en la señal.
#endif
  }

  digitalWrite(PIN_Sensor_ON, LOW);  // Desactiva los sensores.

  // Ajusta los valores máximos y mínimos para dejar un margen de seguridad.
  for (int i = 0; i < 8; i++) {
    v_s_max[i] *= 0.9;
    v_s_min[i] *= 1.1;
  }

  beep();  // Indica el fin de la calibración con dos sonidos.
  beep();
  blick();  // Parpadea un LED para indicar la finalización de la calibración.
  blick();
  blick();

#ifdef ENABLE_DEBUG
  Serial.println();
  Serial.println();

  Serial.print("Minimos");
  Serial.print("\t");
  for (int i = 0; i < 8; i++) {
    Serial.print(v_s_min[i]);
    Serial.print("\t");
  }
  Serial.println();

  Serial.print("Maximos");
  Serial.print("\t");
  for (int i = 0; i < 8; i++) {
    Serial.print(v_s_max[i]);
    Serial.print("\t");
  }
  Serial.println();
#endif
}

/**
 * @brief Realiza la calibración de color para determinar si la pista es blanca con línea negra o negra con línea blanca.
 * 
 * Esta función decide la polaridad de la línea, es decir, si el robot está siguiendo una línea negra sobre fondo blanco
 * o una línea blanca sobre fondo negro.
 */
void Calibracion_Color() {
  blick();  // Parpadeo de un LED para indicar que la calibración de color está en proceso.
  beep();   // Sonido para indicar el inicio.

  digitalWrite(PIN_Sensor_ON, HIGH);  // Activa los sensores.

  LeerSensores();      // Lee los valores actuales de los sensores.
  NormalisarSensor();  // Normaliza las lecturas basadas en los valores calibrados.

  digitalWrite(PIN_Sensor_ON, LOW);  // Desactiva los sensores.

  int8_t black_and_white = 0;
  for (int i = 0; i < 8; i++) {
    if (s_n[i] > 250) {
      black_and_white++;
    } else {
      black_and_white--;
    }
  }
  if (black_and_white > 0)
    linea = !linea;  // Cambia la polaridad de la línea si se detecta una diferencia en el color.

#ifdef ENABLE_DEBUG
  if (linea)
    Serial.println("- Pista blanca con linea negra");
  else
    Serial.println("- Pista negra con linea blanca");
#endif

  delay(500);  // Espera un momento para asegurar que la calibración se registre correctamente.

  blick();  // Indica la finalización de la calibración de color con parpadeos y sonidos.
  beep();
  blick();
  beep();
  blick();
}

/**
 * @brief Normaliza las lecturas de los sensores basándose en los valores de calibración.
 * 
 * Esta función convierte las lecturas de los sensores al rango normalizado de 0 a 500,
 * permitiendo un análisis más sencillo y preciso de la posición de la línea.
 */
void NormalisarSensor() {
  for (int i = 0; i < 8; i++) {
    s_l[i] = constrain(s[i], v_s_min[i], v_s_max[i]);  // Limita el valor del sensor al rango de calibración.

    if (linea)  // Si la línea es negra, normaliza de 0 a 500.
      s_n[i] = map(s_l[i], v_s_min[i], v_s_max[i], 0, 500);
    else  // Si la línea es blanca, normaliza de 500 a 0.
      s_n[i] = map(s_l[i], v_s_min[i], v_s_max[i], 500, 0);
  }
}

/**
 * @brief Calcula la posición de la línea con respecto al robot.
 * 
 * Esta función utiliza las lecturas normalizadas de los sensores frontales para determinar
 * la posición relativa de la línea, lo que es crucial para el control de dirección del robot.
 * 
 * @return int Posición de la línea en un rango de -2500 a 2500.
 */
int GetPos() {
  LeerSensores();      // Lee los valores actuales de los sensores.
  NormalisarSensor();  // Normaliza las lecturas basadas en los valores calibrados.

  long prom = 5 * (long)(s_n[4] - s_n[3]) + 15 * (long)(s_n[5] - s_n[2]) + 25 * (long)(s_n[6] - s_n[1]);
  long sum = s_n[1] + s_n[2] + s_n[3] + s_n[4] + s_n[5] + s_n[6];

  long pos = 0;

  if (sum > 400) {
    online = true;  // Indica que el robot está sobre la línea.

    pos = (long)(100 * prom) / sum;  // Calcula la posición de la línea.
    l_pos = (int)pos;

    HR = s_n[0] > his_sensor[HR];  // Detecta si el sensor lateral derecho está sobre un pad.
    HL = s_n[7] > his_sensor[HL];  // Detecta si el sensor lateral izquierdo está sobre un pad.

  } else {
    online = false;  // Indica que el robot no está sobre la línea.

    if (l_pos < 0) {
      pos = -2500;  // Si estaba a la izquierda, asume que sigue a la izquierda.
    }
    if (l_pos > 0) {
      pos = 2500;  // Si estaba a la derecha, asume que sigue a la derecha.
    }

    HR = false;
    HL = false;
  }

  return (int)pos;  // Retorna la posición de la línea.
}
