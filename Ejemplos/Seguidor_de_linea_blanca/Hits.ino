


int umbral = 700;
int geo = 0;

int HL, HR = 0;

void ReadSensors() {

  HL = analogRead(A7);
  HR = analogRead(A0);

  if (HL > umbral) {
    HL = 0;
  } else {
    HL = 1;
  }

  if (HR > umbral) {
    HR = 0;
  } else {
    HR = 1;
  }
}

void getGeo() {

  if ((HL == 0) && (HR == 0)) {
    geo = 0;
  }



}
