// Variable global

int last_error = 0;  // Variable para almacenar el último error calculado, utilizada para el término derivativo.

/**
 * @brief Calcula la señal de control utilizando un controlador PD simplificado para un seguidor de línea.
 * 
 * Esta función implementa un controlador PD básico, donde el setpoint se fija en 0 (el robot debe permanecer centrado en la línea).
 * El control se basa en el error de posición actual y la derivada de este error, lo que permite ajustar la dirección del robot
 * para mantenerlo sobre la línea.
 * 
 * @param pos La posición actual del robot con respecto a la línea (puede ser positiva o negativa).
 * @return int Señal de control calculada (potencia de giro) que se aplicará a los motores para corregir la dirección del robot.
 *         El valor está limitado entre -510 y 510.
 */
int PIDLambo(int pos) {
  int error = pos;                      // Calcula el error como la desviación de la posición actual respecto al setpoint (0).
  int derivative = error - last_error;  // Calcula la derivada del error (variación del error respecto a la última medida).
  last_error = error;                   // Actualiza el último error con el valor actual para la próxima iteración.

  // Calcula la señal de control (potencia de giro) utilizando los términos proporcional (kp) y derivativo (kd).
  int pot_giro = ((float)error * kp + (float)derivative * kd);

  // Limita la señal de control a un rango entre -510 y 510 para mantener valores válidos para los motores.
  return constrain(pot_giro, -510, 510);
}

/*
Proceso de calibración para el controlador PD de un seguidor de línea.

La calibración se realiza en dos fases: 
1. Una fase estática para determinar la ganancia proporcional (kp).
2. Una fase en movimiento para ajustar la ganancia derivativa (kd).

Fase 1: Calibración estática
- Durante esta etapa, se fija la velocidad base en 0 y la ganancia derivativa (kd) en 0.
- Se inicia el robot con la calibración habitual del sensor de línea y se posiciona el robot sobre la línea para comenzar.
- Con la velocidad base en 0, el robot permanecerá estático mientras intenta mantenerse centrado en la línea.
- Se realizan pequeños empujones al sensor frontal del robot para verificar que este corrige y vuelve a centrarse en la línea.
- Este proceso se repite iterativamente, incrementando ligeramente el valor de kp hasta que, al aplicar un empujón al sensor, el robot oscile sin llegar a centrarse.
- El valor de kp que provoca esta oscilación debe dividirse entre 2, y este será el valor de kp para el funcionamiento normal.

Fase 2: Calibración en movimiento
- En esta fase, se utiliza el valor de kp obtenido anteriormente y se define una velocidad base moderada.
- Durante la calibración, se deben observar dos comportamientos principales del robot:
  1. **Salida de curvas:** Con un kd bajo, el robot puede presentar oscilaciones amplias al salir de curvas cerradas.
  2. **Entrada de curvas:** Con un kd alto, puede producirse un sobreviraje en la entrada de curvas, lo que hace que la cola del robot se desplace hacia afuera como en un derrape.
  3. **Vibraciones en rectas:** Con un kd alto, en trayectorias rectas el robot podría generar vibraciones, un sonido de "claqueteo" y reducción de velocidad.
- Ajustando el valor de kd, se debe buscar un punto donde ninguno de estos comportamientos indeseados ocurra.
- Una vez calibrado a velocidad moderada, se puede incrementar la velocidad y reajustar el valor de kd si es necesario.
- **Nota:** A altas velocidades, especialmente si las ruedas no tienen buena tracción, el robot tenderá a sobrevirar. Por ello, la calibración debe hacerse a una velocidad moderada para evitar pérdida de tracción.

Consideraciones finales:
- Normalmente, los valores de kd son significativamente mayores que los de kp, con una proporción típica de 10:1 o más.
- Los parámetros kp y kd obtenidos son puntos de partida que pueden ajustarse según sea necesario para optimizar el rendimiento.

*/