#ifndef RELE_LIB_H
#define	RELE_LIB_H

#include <Arduino.h>

#define STATUS_OFF	0
#define STATUS_ON	1

class RELE_LIB
{
	public:
		// uint32_t *releTimers;
		uint8_t *releStatus;
		void begin(uint8_t NumberOfRele = 1);
		void setReleStatus(uint8_t WichRele, uint8_t Status);
		void turnAllRele(uint8_t Status);
		uint8_t getReleStatus(uint8_t WichRele);
		void getAllreleStatus(uint8_t *StatusArray);
		void pulseRele(uint8_t RelePin, uint16_t PulseDelayMs, uint8_t EndStatus);
		void toggleStatusByTimer(void);
		
	private:
	uint8_t nRele;
	// uint32_t *oldReleTimer;
};









#endif