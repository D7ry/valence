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


	
		
};
