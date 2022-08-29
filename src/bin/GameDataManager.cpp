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

void GameDataManager::gameSettings::cache() {
	auto settings = RE::GameSettingCollection::GetSingleton();
	fDiffMultHPByPCVE = settings->GetSetting("fDiffMultHPByPCVE")->GetFloat();
	fDiffMultHPByPCE = settings->GetSetting("fDiffMultHPByPCE")->GetFloat();
	fDiffMultHPByPCN = settings->GetSetting("fDiffMultHPByPCN")->GetFloat();
	fDiffMultHPByPCH = settings->GetSetting("fDiffMultHPByPCH")->GetFloat();
	fDiffMultHPByPCVH = settings->GetSetting("fDiffMultHPByPCVH")->GetFloat();
	fDiffMultHPByPCL = settings->GetSetting("fDiffMultHPByPCL")->GetFloat();

	fDiffMultHPToPCVE = settings->GetSetting("fDiffMultHPToPCVE")->GetFloat();
	fDiffMultHPToPCE = settings->GetSetting("fDiffMultHPToPCE")->GetFloat();
	fDiffMultHPToPCN = settings->GetSetting("fDiffMultHPToPCN")->GetFloat();
	fDiffMultHPToPCH = settings->GetSetting("fDiffMultHPToPCH")->GetFloat();
	fDiffMultHPToPCVH = settings->GetSetting("fDiffMultHPToPCVH")->GetFloat();
	fDiffMultHPToPCL = settings->GetSetting("fDiffMultHPToPCL")->GetFloat();

	fCombatHitConeAngle = settings->GetSetting("fCombatHitConeAngle")->GetFloat();
}
