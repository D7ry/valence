#pragma once
#include "PCH.h"
#include "GameDataManager.h"
namespace Utils
{
	inline bool isEffectWardPower(RE::EffectSetting* a_effectSetting) {
		if (!a_effectSetting) {
			return false;
		}
		return a_effectSetting->data.primaryAV == RE::ActorValue::kWardPower;
	}

	/// <summary>
	/// Return the ward this actor is currently casting.
	/// </summary>
	/// <param name="a_actor"></param>
	/// <returns></returns>
	RE::SpellItem* getCastingWard(RE::Actor* a_actor) {
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
			
			for (auto mgef : spell->effects) {
				if (isEffectWardPower(mgef->baseEffect)) {
					return spell->As<RE::SpellItem>();
				}
			}
			
		}
		return nullptr;
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
