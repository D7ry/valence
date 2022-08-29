#include "APIManager.h"

void APIManager::init()
{
	logger::info("Initializing API fetch...");
	_ValhallaCombatAPI = reinterpret_cast<VAL_API::IVVAL2*>(VAL_API::RequestPluginAPI(VAL_API::InterfaceVersion::V2));
	if (_ValhallaCombatAPI) {
		_Obtained_ValhallaCombatAPI = true;
		logger::info("Valhalla Combat API Obtained");
	}
	logger::info("API fetch complete.");
}

bool APIManager::isValhallaCombatAPIObtained()
{
	return _Obtained_ValhallaCombatAPI;
}

bool APIManager::getIsPCTimedBlocking()
{
	return _ValhallaCombatAPI->getIsPCTimedBlocking();
}

bool APIManager::getIsPCPerfectBlocking()
{
	return _ValhallaCombatAPI->getIsPCPerfectBlocking();
}

void APIManager::triggerPcTimedBlockSuccess()
{
	_ValhallaCombatAPI->triggerPcTimedBlockSuccess();
}
