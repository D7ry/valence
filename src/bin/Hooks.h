#pragma once
#include "SKSE/Trampoline.h"
#include "PCH.h"
#include "Utils.h"
#include "include/Utils/DtryUtils.h"
#include "Ward.h"
namespace Hooks
{
	class h_MoveObjectRefrHavok
	{
	public:
		static void install() 
		{
			logger::info("h_moveObjectRefrHavok");
			REL::Relocation<std::uintptr_t> objectRefrVtbl{ RE::VTABLE_TESObjectREFR[0] };
			_moveHavok = objectRefrVtbl.write_vfunc(0x3F, moveHavok);
		}

	private:
		static void moveHavok(RE::TESObjectREFR* a_this, bool a_bool) {
			if (!a_this) {
				_moveHavok(a_this, a_bool);
			}
			auto name = a_this->GetName();
			if (name) {
				logger::info("name: {}", name);
			}

			_moveHavok(a_this, a_bool);

		}
		
		static inline REL::Relocation<decltype(moveHavok)> _moveHavok;
			
	};

	class h_MeleeCollision
	{
	public:
		static void install()
		{
			logger::info("h_MeleeCollision");
			REL::Relocation<uintptr_t> hook{ RELOCATION_ID(37650, 38603) };  //SE:627930 + 38B AE:64D350 +  45A
			auto& trampoline = SKSE::GetTrampoline();

			_processMeleeCollision = trampoline.write_call<5>(hook.address() + RELOCATION_OFFSET(0x38B, 0x45A), processMeleeCollision);
		}

	private:

		static void processMeleeCollision(RE::Actor* a_aggressor, RE::Actor* a_victim, std::int64_t a_int1, bool a_bool, void* a_unkptr) {
			if (Ward::GetSingleton()->processMeleeWardBlock(a_victim, a_aggressor)) {
				return;
			}
			_processMeleeCollision(a_aggressor, a_victim, a_int1, a_bool, a_unkptr);
		}

		static inline REL::Relocation<decltype(processMeleeCollision)> _processMeleeCollision;
	};

	void install() 
	{
		logger::info("hooking...");
		SKSE::AllocTrampoline(1 << 5);
		//h_MoveObjectRefrHavok::install();
		h_MeleeCollision::install();
		logger::info("...success");
	}
}
