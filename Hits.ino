#include "config.h"

int umbral = 400;
int geo = 0;

bool HL, HR = 0;

bool trigger[3] = {0, 0, 0};
bool HL_T, HR_T = 0;

unsigned long side_sensor_acum[2];
int n_sensor_acum = 0;
unsigned long ms_sensor = 0;

void readSideSensors() {
  #ifdef INV_sensor
    HR = analogRead(A0) > his_sensor_x[0][HR];
    HL = analogRead(A7) > his_sensor_x[1][HL];
  #else
    HR = analogRead(A0) < his_sensor_x[0][HR];
    HL = analogRead(A7) < his_sensor_x[1][HL];
  #endif
}

void getGeo() {
  readSideSensors();
  //trigger especificao HL
  if (HL) {
    if (!trigger[0]) {
      trigger[0] = 1;
    }
  }
  else {
    if (trigger[0]) {
      trigger[0] = 0;
      if (!trigger[2]) {
        //codigo funcional del trigger
        curve_sensor();
      }
    }
  }

  if (HR) {
    if (!trigger[1]) {
      trigger[1] = 1;
    }
  }
  else {
    if (trigger[1]) {
      trigger[1] = 0;
      if (!trigger[2]) {
        //codigo funcional del trigger
        finish_sensor();
      }
    }
  }

  //trigger general
  if (HL && HR) {
    if (!trigger[2]) {
      trigger[2] = 1;
      tone(PINBUZZER, 3500, 50);
    }
  }
  else if (!HL && !HR)
  {
    trigger[2] = 0;
  }
}

//esta funcion se ejecuta cada ves que se pase por las lineas
//que indican el cambio de una curva/recta
void curve_sensor() {
  tone(PINBUZZER, 2500, 50);
  curva_trigg = true;
#ifdef DEBUG
  Serial.println("linea de curva detectada");
#endif
}

//esta funcion se ejecuta cada ves que se pase por las lineas
//que indican el inicio o termino de la pista
void finish_sensor() {
  tone(PINBUZZER, 3000, 50);
  finish_count++;
#ifdef DEBUG
  Serial.println("linea de curva inicio/termino detectada");
#endif
}
