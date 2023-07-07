/*


En el tutorial 5, aprendimos a tener un control proporcional al error, para poder seguir la línea. El problema que tenemos ahora es que cuando 
aumentamos la velocidad base, el robot tiende a oscilar. 


Para poder corregir este problema, debemos sumarle una corrección de la potencia del motor, que sea proporcional a la derivada del error.
(No se asusten cuando hablamos de "derivada del error". En este caso, la derivada del error no es más que la razón de cambio del error a través
del tiempo. (error-error_pasado)/(delta_tiempo). Esta "derivada" del error, la multiplicaremos por una constante llamada Kderiv, 
que modifica la amplitud de la corrección derivativa.

quedando entonces:

correction_power = Kprop*error + kderiv* (error - error_pasado)/(delta_tiempo). 

En este caso, como estamos utilizando un microcontrolador donde todos los ciclos son iguales (en el void loop), delta_tiempo sería una constante
que puede quedar expresada dentro de la constante Kderiv.

por lo tanto:

correction_power = Kprop*error + kderiv* (error - error_pasado). 

La corrección derivativa nos ayuda a amortiguar las oscilaciones provocadas por la corrección proporcional.
 
*/








#define PINBUZZER 10
#define PINBOTON 2
#define PINLED 13

int posicion_ideal = 0;

//cómo modificar el kprop: Comenzar con valores con valores bajos, y aumentar de a poco, hasta que siga la linea y quede oscilando.
//cómo modificar el kderiv: Comenzar con valores con valores bajos, y aumentar de a poco, hasta que el robot deje de oscilar.

//cuando el robot deje de oscilar, puedes subirle la velocidad nuevamente, y comenzar nuevamente a modificar el Kprop y el Kderiv.

float Kprop = 1.0;  
float Kderiv = 6.0;

int base = 80;
int error_pasado = 0;


void setup() {
  Serial.begin(115200);
  Peripherals_init();
  TB6612FNG_init();

  digitalWrite(PINLED, LOW);
  delay(500);

  Motores(0, 0);

  Serial.println("hola, Quinta y penúltima parte del tutorial");

  delay(500);
  WaitBoton();
  calibracion();


  WaitBoton();


  delay(1000);
}


void loop() {

  int p = GetPos();
  int error = p - posicion_ideal;
  int d_error = error - error_pasado;
  int correction_power = int(Kprop * error) + int(Kderiv * (d_error));


  if (correction_power > 255) {
    correction_power = 255;

  }

  else if (correction_power < -255) {
    correction_power = -255;
  }





  Motores(base + correction_power, base + -correction_power);
  error_pasado = error;


  delay(1);
}
ok 10