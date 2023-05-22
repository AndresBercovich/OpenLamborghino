double setpoint = 0.0;
double last_error = 0.0;
double pot_limite = 255.0;
double integrative = 0.0;

double PIDLambo(double POS, double Kp, double Kd, double Ki)
{
  double error = POS - setpoint;
  double derivative = error - last_error;
  integrative += error * Ki;
  last_error = error;
  double pot_giro = (error * Kp + derivative * Kd + integrative);

  return constrain(pot_giro,-pot_limite,pot_limite);
}
