/*
Como vimos anteriormente, un control como el del tutorial 4,  si bien es cierto ayuda a seguir la línea, deja el robot oscilando
debido a que la respuesta de corrección del motor no está amortiguada. Además el robot no tiene la capacidad de modificar 
la velocidad de seguimiento de la línea.


Para corregir esto, debemos debemos utilizar un algoritmo de control que pueda corregir el movimiento de los motores, y
de manera proporcional al error. Es decir, si el error de posición es grande, entonces, que los motores corrijan con mayor potencia. 
Análogamente, si el error es pequeño, necesitamos que la corrección sea con una potencia menor.

para eso haremos que la respuesta del motor sea proporcional al error. Siendo el error = posición_actual - posición_ideal

luego este error lo multiplicaremos por una constante llamada kprop, que modifica la amplitud de la corrección proporcional al error.

Con este sencillo paso, el robot podrá corregir su posición sin moverse de su lugar. 


También pueden agregarle una velocidad base, que se sumará a la velocidad de corrección, para que el robot vaya hacia adelante.

*/



#define PINBUZZER 10
#define PINBOTON 2
#define PINLED 13
#define PIN_Sensor_ON 11


int posicion_ideal = 0;

float Kprop = 1.0;

//int base = 40;


void setup() {
  Serial.begin(115200);
  Peripherals_init();
  TB6612FNG_init();
  Sensors_init();

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
  int correction_power = int(Kprop * error);




    Motores(correction_power, -correction_power);


  //Motores(base + correction_power, base + -correction_power);


  delay(1);
}
