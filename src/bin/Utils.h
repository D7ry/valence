#pragma once
#include "PCH.h"
#include "GameDataManager.h"
namespace Utils
{
	inline bool isWardEffect(RE::EffectSetting* a_effectSetting) {
		if (!a_effectSetting) {
			return false;
		}
		return a_effectSetting->data.primaryAV == RE::ActorValue::kWardPower;
	}

	/// <summary>
	/// Return the ward data this actor is currently casting, if the actor is casting a ward.
	/// </summary>
	/// <param name="a_actor"></param>
	/// <returns></returns>
	RE::EffectSetting::EffectSettingData* getWardData(RE::Actor* a_actor) {
		if (a_actor->GetActorValue(RE::ActorValue::kWardPower) == 0) {
			return nullptr;  //rough filter
		}
		for (int i = 0; i < RE::Actor::SlotTypes::kTotal; i++) {
			auto& magicCaster = a_actor->magicCasters[i];
			if (!magicCaster) {
				continue;
			}
			auto spell = magicCaster->currentSpell;
			if (!spell) {
				continue;
			}

			if (!a_actor->IsCasting(spell)) {
				continue;
			}
			//iterate through spell's all effects, trying to find the ward effect.
			for (auto it = spell->effects.begin(); it != spell->effects.end(); it++) {
				RE::EffectSetting* baseEffect = (*it)->baseEffect;
				if (baseEffect && baseEffect->data.primaryAV == RE::ActorValue::kWardPower) {
					return &baseEffect->data;
				}
				it++;
			}
		}
		return nullptr;
	}

	bool isCastingWard(RE::Actor* a_actor) {
		return getWardData(a_actor) != nullptr;
	}

	inline float getWardPower(RE::Actor* a_actor) {
		return a_actor->GetActorValue(RE::ActorValue::kWardPower);
	}

	inline void setWardPower(RE::Actor* a_actor, float a_set) {
		a_actor->SetActorValue(RE::ActorValue::kWardPower, a_set);
	}

	inline void modWardPower(RE::Actor* a_actor, float a_mod) {
		a_actor->ModActorValue(RE::ActorValue::kWardPower, a_mod);
	}

	

}
