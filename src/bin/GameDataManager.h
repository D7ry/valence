#pragma once
class GameDataManager
{
public:

	static GameDataManager* GetSingleton() {
		static GameDataManager singleton;
		return std::addressof(singleton);
	}
	/// <summary>
	/// Set all ward's magicka cost to 0.
	/// </summary>
	static void negateWardCost();

	class gameSettings
	{
	public:
		float fDiffMultHPByPCVE;
		float fDiffMultHPByPCE;
		float fDiffMultHPByPCN;
		float fDiffMultHPByPCH;
		float fDiffMultHPByPCVH;
		float fDiffMultHPByPCL;
		float fDiffMultHPToPCVE;
		float fDiffMultHPToPCE;
		float fDiffMultHPToPCN;
		float fDiffMultHPToPCH;
		float fDiffMultHPToPCVH;
		float fDiffMultHPToPCL;
		
		float fCombatHitConeAngle;

		void cache();
	};

	gameSettings _cachedGameSettings;

	
		
};
