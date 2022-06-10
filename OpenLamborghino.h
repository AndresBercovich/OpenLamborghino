

 # ifndef OpenLamborghino_h
 # define OpenLamborghino_h
 # include "Arduino.h"
 # include "QTRSensors.h"
 # include "OpenTB6612FNG.h"

class OpenLamborghino {
	public:
	OpenLamborghino(int PINBOTON, int PINBUZZER);
	void WaitBoton();
	void beep();
	void IfBoton();

	long LineaNegra();
	long LineaBlanca();
	void calibracion();

	void funcionCruce();
	void funcionHitoIz();
	void funcionHitoDe();

	void EncoderIz();
	void EncoderDe();
	void vel();
	int controlador();
	void incomingByte(int a);
	
	
	void comunicacion();
	
	
	
	void PIDLambo(float kp, float kd, float ki);
	long PID(int POS, int setpoint, int base);

	void ReadSensors();
	void detecGeo();
	int change();
	void velocimetro();
	void datalogger();
	

	private:
	int velocid;
	int a;
	int POS;
	int setpoint;
	int base;
	float kp;
	float kd;
	float ki;
	long _PasosIz;
	long _PasosDe;
	int setv;
	int pow;
};

# endif
