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

  //trigger especificao HL
  if(HL){
    if(!trigger[0]){
      trigger[0] = 1;
     }
  }
  else{
    if(trigger[0]){
      trigger[0] = 0;
      if(!trigger[2]){
        //codigo funcional del trigger
        curve_sensor();
      }
     }
  }

  if(HR){
    if(!trigger[1]){
      trigger[1] = 1;
     }
  }
  else{
    if(trigger[1]){
      trigger[1] = 0;
      if(!trigger[2]){
        //codigo funcional del trigger
        finish_sensor();
      }
     }
  }

  //trigger general
  if(HL && HR){
    if(!trigger[2]){
      trigger[2] = 1;
     }
  }
  else if (!HL && !HR)
  {
    trigger[2] = 0;
  }
}

void curve_sensor(){
  tone(PINBUZZER, 2500, 50);
  //esta funcion se ejecuta cada ves que se pase por las lineas 
  //que indican el cambio de una curva/recta
}

void finish_sensor(){
  tone(PINBUZZER, 3000, 50);
  //esta funcion se ejecuta cada ves que se pase por las lineas 
  //que indican el inicio o termino de la pista
}