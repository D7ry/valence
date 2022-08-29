#pragma once
#include <PCH.h>
#include "APIManager.h"
class Effects
{
	
	
public:
	enum class EffectType
	{
		Regular,
		Timed,
		Perfect
	};

	static Effects* GetSingleton()
	{
		static Effects singleton;
		return std::addressof(singleton);
	}
	
	
	void playWardBlockEffects(RE::EffectSetting::EffectSettingData* a_wardEffect, RE::Actor* a_blocker, RE::Actor* a_aggressor, EffectType a_effectType)
	{
		playWardBlockSFX(a_wardEffect, a_blocker, a_aggressor, a_effectType);
		playWardBlockVFX(a_wardEffect, a_blocker, a_aggressor, a_effectType);
	}

private:
	void playWardBlockSFX(RE::EffectSetting::EffectSettingData* a_wardEffect, RE::Actor* a_blocker, RE::Actor* a_aggressor, EffectType a_effectType) 
	{
		switch (a_effectType) {
		case EffectType::Regular:
			break;
		}
	}

	void playWardBlockVFX(RE::EffectSetting::EffectSettingData* a_wardEffect, RE::Actor* a_blocker, RE::Actor* a_aggressor, EffectType a_effectType)
	{
		switch (a_effectType) {
		case EffectType::Regular:
			a_blocker->InstantiateHitArt(a_wardEffect->hitEffectArt, 1, a_blocker, false, false);
		}
	}
};


class Ward
{
public:
	static Ward* GetSingleton() {
		static Ward singleton;
		return std::addressof(singleton);
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="a_blocker"></param>
	/// <param name="a_aggressor"></param>
	/// <returns></returns>
	bool processMeleeWardBlock(RE::Actor* a_blocker, RE::Actor* a_aggressor) {
		if (!Utils::isInBlockAngle(a_blocker, a_aggressor)) {
			return false;
		}

		auto ward = Utils::getWardData(a_blocker);
		
		if (!ward) {
			return false;
		}

		float damage = Utils::calculateHitDamage(a_aggressor, a_blocker);
		APIManager* API = APIManager::GetSingleton();
		if (API->isValhallaCombatAPIObtained()) { //proc timed block
			if (API->getIsPCTimedBlocking()) {
				Effects::GetSingleton()->playWardBlockEffects(ward, a_blocker, a_aggressor, Effects::EffectType::Timed);
				API->triggerPcTimedBlockSuccess();
				return true;
			}
			
		}
		
		if (damage > Utils::getWardPower(a_blocker)) {
			Utils::modWardPower(a_blocker, damage);
			a_aggressor->NotifyAnimationGraph("recoillargestart");
			Effects::GetSingleton()->playWardBlockEffects(ward, a_blocker, a_aggressor, Effects::EffectType::Regular);
			return true;
		} else {
			logger::info("not enough ward power to block");
			Utils::modWardPower(a_blocker, damage);
			a_blocker->NotifyAnimationGraph("staggerStart");
		}

		return false;
	}

	/// <summary>
	/// Process a projectile ward block. Projectile can be physical(arrow/bolts) and magical(spells
	/// If the blocker is doing timed block, projectiles are blocked without losing ward health.
	/// else, magical projectiles will be processed by the game's native code, while physical projectiles
	/// go through an extra process to be determined if it can be blocked.
	/// </summary>
	/// <param name="a_blocker"></param>
	/// <param name="a_aggressor"></param>
	/// <returns>Whether the projectile is either:
	/// 1. Timed blocked OR
	/// 2. A physical projectile and blocked by ward</returns>
	bool processProjectileWardBlock(RE::Actor* a_blocker, RE::Projectile* a_projectile, RE::hkpAllCdPointCollector* a_AllCdPointCollector);
	
private:
		
};
