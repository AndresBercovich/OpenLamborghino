#include <OpenLamborghino.h>


#define BOTON  12
#define BUZZER  10

OpenLamborghino OpenLamborghino(BOTON, BUZZER);

void setup() {
  Serial.begin(9600);
  OpenLamborghino.WaitBoton();
  delay(1000);
}
void loop() {


}
