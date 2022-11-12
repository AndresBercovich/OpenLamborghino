#include "config.h"
bool trigger[2] = {0, 0};

int umbral = 700;
int geo = 0;

bool HL, HR = 0;

bool trigger[3] = {0,0,0};
bool HL_T, HR_T = 0;

void readSideSensors() {
  #ifdef INV_sensor
    HR = map(analogRead(A0),0,1023,1023,0) < umbral;
    HL = map(analogRead(A7),0,1023,1023,0) < umbral;
  #else
    HR = analogRead(A0) < umbral;
    HL = analogRead(A7) < umbral;
  #endif
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

//esta funcion se ejecuta cada ves que se pase por las lineas 
//que indican el cambio de una curva/recta
void curve_sensor(){
  tone(PINBUZZER, 2500, 50);
  #ifdef DEBUG 
    Serial.print("linea de curva detectada");
  #endif
}

//esta funcion se ejecuta cada ves que se pase por las lineas 
//que indican el inicio o termino de la pista
void finish_sensor(){
  tone(PINBUZZER, 3000, 50);

  #ifdef DEBUG 
    Serial.print("linea de curva inicio/termino detectada");
  #endif
}