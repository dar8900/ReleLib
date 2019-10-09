#include "ReleLib.h"


void RELE_LIB::begin(uint8_t NumberOfRele)
{
	nRele = NumberOfRele;
	releStatus = new uint8_t [nRele];
	if(!releStatus)
	{
		return;
	}
	for(int ReleIndex = 0; ReleIndex < nRele; ReleIndex++)
		releStatus[ReleIndex] = 0;
	// releTimers = new uint32_t [nRele](0);
	// oldReleTimer = new uint32_t [nRele](0);
}

void RELE_LIB::setReleStatus(uint8_t WichRele, uint8_t Status)
{
	if((Status != STATUS_OFF && Status != STATUS_ON) || (WichRele >= nRele))
		return;
	else
	{
		releStatus[WichRele] = Status;
	}
}

void RELE_LIB::turnAllRele(uint8_t Status)
{
	if(Status != STATUS_OFF && Status != STATUS_ON)
		return;
	for(int ReleIndex = 0; ReleIndex < nRele; ReleIndex++)
	{
		releStatus[ReleIndex] = Status;
	}
}

uint8_t RELE_LIB::getReleStatus(uint8_t WichRele)
{
	if(WichRele >= nRele)
		return 0;
	else
		return releStatus[WichRele];
}

void RELE_LIB::getAllreleStatus(uint8_t *StatusArray)
{
	for(int ReleIndex = 0; ReleIndex < nRele; ReleIndex++)
	{
		if(StatusArray + ReleIndex != NULL)
		{
			StatusArray[ReleIndex] = releStatus[ReleIndex];
		}
		else 
			return;
	}
}

void RELE_LIB::pulseRele(uint8_t RelePin, uint16_t PulseDelayMs, uint8_t EndStatus)
{
	if(EndStatus != STATUS_OFF && EndStatus != STATUS_ON)
		return;
	else
	{
		if(EndStatus == STATUS_OFF)
			digitalWrite(RelePin, STATUS_ON);
		else
			digitalWrite(RelePin, STATUS_OFF);
		delay(PulseDelayMs);
		digitalWrite(RelePin, EndStatus);
	}
}