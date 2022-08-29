#pragma once
#include <PCH.h>

class Ward
{
public:
	static Ward* GetSingleton() {
		static Ward singleton;
		return std::addressof(singleton);
	}

	bool processPhysicalWardBlock(RE::Actor* a_blocker, RE::Actor* a_aggressor);

	bool processProjectileWardBlock(RE::Actor* a_blocker, RE::Actor* a_aggressor);
	
private:
		
};
