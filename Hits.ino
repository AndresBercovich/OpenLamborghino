bool trigger[2] = {0, 0};

int umbral = 700;
int geo = 0;

bool HL, HR = 0;

bool trigger[3] = {0,0,0};
bool HL_T, HR_T = 0;

void readSideSensors() {
  HR = analogRead(A0) < umbral;
  HL = analogRead(A7) < umbral;
}

void getGeo() {

  if ((HL == 0) && (HR == 0)) {
    geo = 0;
  }

  if(!HL){
    if(trigger[0]){
      trigger[0] = 0;
      HL_T = 1;
     }
  }
  else{
    trigger[0] = 1;
  }

}
