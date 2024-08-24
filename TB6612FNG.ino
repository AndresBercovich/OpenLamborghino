/**
 * @brief Controla el funcionamiento de un motor utilizando el controlador TB6612FNG.
 *
 * @param PWM_value Valor PWM que controla la velocidad y dirección del motor. Un valor positivo mueve el motor hacia adelante, un valor negativo hacia atrás, y un valor de 0 detiene el motor.
 * @param en_brake Si es verdadero (true), activa el modo de frenado del motor (tanto IN1 como IN2 estarán en el mismo estado). Si es falso (false), desactiva el modo de frenado.
 * @param PWM_pin Pin del Arduino conectado a la entrada PWM del controlador del motor.
 * @param IN1_pin Pin del Arduino conectado a la entrada IN1 del controlador del motor.
 * @param IN2_pin Pin del Arduino conectado a la entrada IN2 del controlador del motor.
 */
void Motor(int PWM_value, bool en_brake, uint8_t PWM_pin, uint8_t IN1_pin, uint8_t IN2_pin) {
  if (PWM_value == 0) {
    // Si PWM_value es 0, el motor se detiene. Si en_brake es true, se activa el frenado.
    digitalWrite(IN1_pin, en_brake);
    digitalWrite(IN2_pin, en_brake);
    digitalWrite(PWM_pin, !en_brake);
  } else {
    if (PWM_value > 0) {
      // Si el valor es positivo, el motor gira hacia adelante.
      digitalWrite(IN1_pin, HIGH);
      digitalWrite(IN2_pin, LOW);
    } else {
      // Si el valor es negativo, el motor gira hacia atrás.
      digitalWrite(IN1_pin, LOW);
      digitalWrite(IN2_pin, HIGH);
    }
    
    // Se limita el valor absoluto de PWM_value a un rango de 0 a 255 y se envía al pin PWM.
    int PWM = constrain(abs(PWM_value), 0, 255);
    analogWrite(PWM_pin, PWM);
  }
}

/**
 * @brief Controla el motor izquierdo utilizando el controlador TB6612FNG.
 *
 * @param PWM_value Valor PWM que controla la velocidad y dirección del motor izquierdo.
 * @param en_brake Si es verdadero (true), activa el modo de frenado del motor izquierdo.
 */
void MotorIz(int PWM_value, bool en_brake) {
  Motor(PWM_value, en_brake, PIN_PWMA, PIN_AIN1, PIN_AIN2);
}

/**
 * @brief Controla el motor derecho utilizando el controlador TB6612FNG.
 *
 * @param PWM_value Valor PWM que controla la velocidad y dirección del motor derecho.
 * @param en_brake Si es verdadero (true), activa el modo de frenado del motor derecho.
 */
void MotorDe(int PWM_value, bool en_brake) {
  Motor(PWM_value, en_brake, PIN_PWMB, PIN_BIN1, PIN_BIN2);
}

/**
 * @brief Controla ambos motores (izquierdo y derecho) simultáneamente.
 *
 * @param left Valor PWM para el motor izquierdo.
 * @param right Valor PWM para el motor derecho.
 * @param en_brake Si es verdadero (true), activa el modo de frenado para ambos motores.
 */
void Set_Motores(int left, int right, bool en_brake) {
  MotorIz(left, en_brake);
  MotorDe(right, en_brake);
}

/**
 * @brief Detiene ambos motores y, si se desea, activa el modo de frenado.
 *
 * @param en_brake Si es verdadero (true), activa el modo de frenado para ambos motores.
 */
void Stop_Motores(bool en_brake) {
  MotorIz(0, en_brake);
  MotorDe(0, en_brake);
}
