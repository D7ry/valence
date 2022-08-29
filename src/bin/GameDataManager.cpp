#include "GameDataManager.h"

void GameDataManager::negateWardCost()
{
	auto data = RE::TESDataHandler::GetSingleton();
	if (!data) {
		logger::error("Error: GameDataManager::negateWardCost: TESDataHandler::GetSingleton() failed");
		return;
	}
	
	auto& spells = data->GetFormArray<RE::SpellItem>();
	
	logger::info("Re-adjusting ward magicka costs...");
	auto it = spells.begin();
	while (it != spells.end()) {
		RE::SpellItem*& spell = *it;
			auto& effects = spell->effects;
			auto it2 = effects.begin();
			while (it2 != effects.end()) {
				RE::Effect*& effect = *it2;
				if (effect) {
					RE::EffectSetting*& effectSetting = effect->baseEffect;
					if (effectSetting) {
						auto data = &effectSetting->data;
						if (data->primaryAV == RE::ActorValue::kWardPower) {
							logger::info("Overriding cost: {}", spell->GetName());
							spell->data.costOverride = 0;
							spell->data.flags.set(RE::SpellItem::SpellFlag::kCostOverride);
						}
					}
				}
				it2++;
			}
		it++;
	}
}
