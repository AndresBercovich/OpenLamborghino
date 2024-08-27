// Variable global

int last_error = 0;  // Variable para almacenar el último error calculado, utilizada para el término derivativo.

/**
 * @brief Calcula la señal de control utilizando un controlador PID simplificado para un seguidor de línea.
 * 
 * Esta función implementa un controlador PID básico, donde el setpoint se fija en 0 (el robot debe estar centrado en la línea).
 * El control se basa en el error de posición actual y la derivada de este error, lo que permite ajustar la dirección del robot
 * para mantenerlo sobre la línea.
 * 
 * @param pos La posición actual del robot con respecto a la línea (puede ser positivo o negativo).
 * @return int Señal de control calculada (potencia de giro) que se aplicará a los motores para corregir la dirección del robot.
 *         El valor está limitado entre -255 y 255.
 */
int PIDLambo(int pos) {
  int error = pos;  // Calcula el error como la desviación de la posición actual respecto al setpoint (0).
  int derivative = error - last_error;  // Calcula la derivada del error (variación del error respecto a la última medida).
  last_error = error;  // Actualiza el último error con el valor actual para la próxima iteración.

  // Calcula la señal de control (potencia de giro) utilizando los términos proporcional (kp) y derivativo (kd).
  int pot_giro = ((float)error * kp + (float)derivative * kd);

  // Constriñe la señal de control a un rango entre -255 y 255 para limitar la salida a valores válidos para los motores.
  return constrain(pot_giro, -255, 255);
}
