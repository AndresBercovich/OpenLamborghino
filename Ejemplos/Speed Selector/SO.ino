int cont = 0;
int tiempo = 0;
long ahora = 0;



int flagR = 0;



void change() {

  digitalWrite(PINDRON, LOW);

  if (analogRead(A0) < umbral) {

    ahora = millis();
    flagR = 1;

    while (analogRead(A0) < umbral + 40) {
      if (tiempo > 2000) {
        setSpeed();
        Serial.println("Set velocidad ");
        Serial.println("\t");
        Serial.println(base);


        for (int i = 1; i <= cont; i++) {

          tone(PINBUZZER, 4000, 50);
          delay(500);

        }
        delay(1000);
        tiempo = 0;
        flagR = 0;
        return;

      } else {
        tiempo = millis() - ahora;
      }
    }
  }

  if ((analogRead(A0) > umbral) && (flagR == 1) ) {
    flagR = 0;
    cont++;
    tone(PINBUZZER, 3500, 50);
    delay(250);
    Serial.println(cont);

  }

  if (analogRead(A7) < umbral) {

    cont--;
    tone(PINBUZZER, 3000, 50);
    delay(250);
    Serial.println(cont);

  }


}


void setSpeed() {

  base = cont * 10;

}