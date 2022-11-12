bool trigger[2] = {0, 0};

int umbral = 700;
int geo = 0;

bool HL, HR = 0;

void readSideSensors() {
  HR = analogRead(A0) < umbral;
  HL = analogRead(A7) < umbral;
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
