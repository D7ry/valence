#pragma once
#include "PCH.h"
#include "include/API/ValhallaCombatAPI.h"

class APIManager
{
public:
	static APIManager* GetSingleton() 
	{
		static APIManager singleton;
		return std::addressof(singleton);
	}

	void init();
	
	bool isValhallaCombatAPIObtained();

	bool getIsPCTimedBlocking();

	bool getIsPCPerfectBlocking();

	void triggerPcTimedBlockSuccess();
	

private:
	VAL_API::IVVAL2* _ValhallaCombatAPI;
	bool _Obtained_ValhallaCombatAPI;

};
