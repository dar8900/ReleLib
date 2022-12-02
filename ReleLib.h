#ifndef RELE_LIB_H
#define	RELE_LIB_H

#include <Arduino.h>

#define RELE_OFF	false
#define RELE_ON		true

class ReleLib
{
	public:
		void setup(int RelePin = -1);
		void switchStatus(bool NewStatus);
		void toggleStatus();
		bool getStatus();
		uint32_t getOnTime();
		uint32_t getOffTime();
		void setDelayedSwitch(uint16_t Delay, bool NewStatus);
		void runEngine();
		
	private:
		bool _setupDone = false;
		int _relePin = -1;
		bool _releStatus = RELE_OFF;
		const uint16_t _ENGINE_CYCLE = 100; // in ms
		uint32_t _cycleTimer = 0;
		uint32_t _onTimer = 0;
		uint32_t _offTimer = 0;
		uint32_t _delayedSwitchTimer = 0;
		uint16_t _delaySwitchTimeout = 0;
		bool _delayedSwitchEnabled = false;
		bool _delayedSwitchNewStatus = RELE_OFF;
		void _switchRele(bool Status);
};









#endif