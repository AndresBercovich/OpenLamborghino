int setpoint = 0;
int last_error = 0;
int pot_limite = 250;
float integrative = 0;

int PIDLambo(int POS, float Kp, float Kd, float Ki)
{
  int error = POS - setpoint;
  int derivative = error - last_error;
  integrative += float(error) * Ki;
  last_error = error;
  int pot_giro = (error * Kp + derivative * Kd + integrative);

  if (pot_giro > pot_limite)
    pot_giro = pot_limite;
  else if (pot_giro < -pot_limite)
    pot_giro = -pot_limite;
  return pot_giro;
}
