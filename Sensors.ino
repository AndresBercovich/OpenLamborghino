#include "config.h"

int v_s_min[8] = {1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023};
int v_s_max[8] = {0, 0, 0, 0, 0, 0, 0, 0};
double s_p[6];
bool online;
int l_pos;

void calibracion() {

  int v_s[8];

  for (int j = 0; j < 100; j++) {
    delay(10);
    v_s[0] = analogRead(A6);
    v_s[1] = analogRead(A5);
    v_s[2] = analogRead(A4);
    v_s[3] = analogRead(A3);
    v_s[4] = analogRead(A2);
    v_s[5] = analogRead(A1);
    v_s[6] = analogRead(A0); //HR
    v_s[7] = analogRead(A7); //HL

    #ifdef DEBUG 
      for (int i = 0; i < 8; i++) {
        Serial.print(v_s[i]);
        Serial.print("\t");
      }
      Serial.println();
    #endif

    for (int i = 0; i < 8; i++) {
      if (v_s[i] < v_s_min[i]) {
        v_s_min[i] = v_s[i];
      }
    }

    for (int i = 0; i < 8; i++) {
      if (v_s[i] > v_s_max[i]) {
        v_s_max[i] = v_s[i];
      }
    }
      side_sensor_x[0] = (v_s_max[6] + v_s_min[6]) / 2; //A0
      side_sensor_x[1] = (v_s_max[7] + v_s_min[7]) / 2; //A7

      his_sensor_x[0][0] = side_sensor_x[0] - histeresis;
      his_sensor_x[0][1] = side_sensor_x[0] + histeresis;

      his_sensor_x[1][0] = side_sensor_x[1] - histeresis;
      his_sensor_x[1][1] = side_sensor_x[1] + histeresis;
  }

  tone(PINBUZZER, 2000, 100);
  delay(200);
  tone(PINBUZZER, 2000, 100);
  delay(200);

  #ifdef DEBUG 
    Serial.println();
    Serial.print("Mínimos ");
    Serial.print("\t");
  
    for (int i = 0; i < 8; i++) {
      Serial.print(v_s_min[i]);
      Serial.print("\t");
    }
    Serial.println();
    Serial.print("Máximos ");
    Serial.print("\t");

    for (int i = 0; i < 8; i++) {
      Serial.print(v_s_max[i]);
      Serial.print("\t");
    }
    Serial.println();
    Serial.println();
    Serial.println();
  #endif
}

void readSensors() {
  volatile int s[6];
  s[0] = analogRead(A6);
  s[1] = analogRead(A5);
  s[2] = analogRead(A4);
  s[3] = analogRead(A3);
  s[4] = analogRead(A2);
  s[5] = analogRead(A1);

  for (int i = 0; i < 6; i++) {
    s[i] = constrain(s[i], v_s_min[i], v_s_max[i]);
    #ifdef INV_sensor
      s_p[i] = Dmap(s[i], v_s_min[i], v_s_max[i], 0, 100);
    #else
      s_p[i] = Dmap(s[i], v_s_min[i], v_s_max[i], 100, 0);
    #endif
  }

  double sum = s_p[0] + s_p[1] + s_p[2] + s_p[3] + s_p[4] + s_p[5];
  if (sum > 100.0) {
    online = 1;
  } else {
    online = 0;
    sum = 100;
  }

  #ifdef DEBUG 
    if (online) {
      for (int i = 0; i < 6; i++) {
        Serial.print(s_p[i]);
        Serial.print("\t");
      }
      //Serial.println();
    }
  #endif
}

double GetPos() {
  readSensors();
  double prom = -2.5 * s_p[0] - 1.5 * s_p[1] - 0.5 * s_p[2] + 0.5 * s_p[3] + 1.5 * s_p[4] + 2.5 * s_p[5];
  double sum = s_p[0] + s_p[1] + s_p[2] + s_p[3] + s_p[4] + s_p[5];

  if (online) {
    pos = 100.0 * prom / sum;
  } 
  else {
    if (l_pos < 0) {
      pos = -255;
    }
    if (l_pos >= 0) {
      pos = 255;
    }
  }
  l_pos = pos;
  return pos;
}
