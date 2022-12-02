#include "ReleLib.h"

/**
 * @brief Modifica lo stato del gpio
 * 
 */
void ReleLib::_switchRele()
{
	if(_setupDone)
	{
		_releStatus == RELE_ON ? digitalWrite(_relePin, HIGH) : digitalWrite(_relePin, LOW);
	}
}

/**
 * @brief Inizializza il gpio e la libria
 * 
 * @param int RelePin 
 */
void ReleLib::setup(int RelePin)
{
	if(RelePin > 0)
	{
		_relePin = RelePin;
		pinMode(_relePin, OUTPUT);
		_setupDone = true;
	}
}

/**
 * @brief Modifica il valore logico e fisico del relè
 * 
 * @param bool NewStatus 
 */
void ReleLib::switchStatus(bool NewStatus)
{
	if(_setupDone)
	{
		if(NewStatus != _releStatus)
		{
			_releStatus = NewStatus;
			_switchRele();
			_releStatus == RELE_ON ? _offTimer = 0 : _onTimer = 0;
		}
	}
}

/**
 * @brief Modifica il valore logico e fisico del relè impostando il valore contrario 
 * 			al valore attuale
 * 
 */
void ReleLib::toggleStatus()
{
	if(_setupDone)
	{
		_releStatus = !_releStatus;
		_switchRele();
		_releStatus == RELE_ON ? _offTimer = 0 : _onTimer = 0;
	}
}

/**
 * @brief Ritorna il valore logico e fisico del relè
 * 
 * @return true 
 * @return false 
 */
bool ReleLib::getStatus()
{
	bool ReleStat = false;
	if(_setupDone)
	{
		ReleStat = _releStatus;		
	}
	return ReleStat;
}

/**
 * @brief Ritorna il tempo in secondi in cui il relè rimane in stato eccitato,
 * 			viene azzerato al cambio di stato
 * 
 * @return uint32_t OnTime
 */
uint32_t ReleLib::getOnTime()
{
	return (_onTimer / (1000 / _ENGINE_CYCLE));
}

/**
 * @brief Ritorna il tempo in secondi in cui il relè rimane in stato diseccitato,
 * 			viene azzerato al cambio di stato
 * 
 * @return uint32_t OffTime
 */
uint32_t ReleLib::getOffTime()
{
	return (_offTimer / (1000 / _ENGINE_CYCLE));
}

/**
 * @brief Imposta il cambio di stato dopo x ms 
 * 
 * @param uint16_t Delay 
 * @param bool NewStatus 
 */
void ReleLib::setDelayedSwitch(uint16_t Delay, bool NewStatus)
{
	if(_setupDone)
	{
		if(Delay >= _ENGINE_CYCLE && Delay != _delaySwitchTimeout)
		{
			_delaySwitchTimeout = Delay;
			_delayedSwitchTimer = 0;
			_delayedSwitchEnabled = true;
			_delayedSwitchNewStatus = NewStatus;
		}
	}
}

/**
 * @brief Engine che si occupa di raccogliere i tempi dei timer e 
 * 			gestisce lo switch con delay
 * 
 */
void ReleLib::runEngine()
{
	if(_setupDone)
	{
		if(_cycleTimer == 0)
		{
			_cycleTimer = millis();
		}
		if(millis() - _cycleTimer >= _ENGINE_CYCLE)
		{
			_cycleTimer = 0;
			if(_releStatus == RELE_ON)
			{
				_onTimer++;
			}
			else
			{
				_offTimer++;
			}
			if(_delayedSwitchEnabled)
			{
				if(_delayedSwitchTimer == 0)
				{
					_delayedSwitchTimer = millis();
				}
				if(millis() - _delayedSwitchTimer >= _delaySwitchTimeout)
				{
					switchStatus(_delayedSwitchNewStatus);
					_delayedSwitchEnabled = false;
				}
			}
		}
	}
}
