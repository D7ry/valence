#pragma once
#include "SKSE/Trampoline.h"
#include "PCH.h"
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

	void install() 
	{
		logger::info("hooking...");
		h_MoveObjectRefrHavok::install();
		logger::info("...success");
	}
}
