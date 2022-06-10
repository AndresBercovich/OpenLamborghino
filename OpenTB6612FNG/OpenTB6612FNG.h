

 # ifndef OpenTB6612FNG_h
 # define OpenTB6612FNG_h
 # include "Arduino.h"

class OpenTB6612FNG{
	public:
	OpenTB6612FNG(int TP);

	void MotorIz(int value);
	void MotorDe(int value);
	void Motores(int left, int righ);
	void Frenos(boolean left, boolean righ, int value);
	void ACTFrenoIz(int value);
	void ACTFrenoDe(int value);
	void PASFrenoIz(int value);
	void PASFrenoDe(int value);
	private:

	long duration;
	long distance_cm;
};

# endif
