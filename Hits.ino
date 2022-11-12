boolean trigger[2] = {0, 0}

int umbral = 700;
int geo = 0;

int HL, HR = 0;

void readSideSensors() {

  HL = analogRead(A7);
  HR = analogRead(A0);

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

  if(analogRead(A7) > side_sensor_x[0]){
    if(trigger[0]){
      trigger[0] = 0;
      leftSensorCounter++;
     }
  }
  else{
    trigger[0] = 1;
  }

}
