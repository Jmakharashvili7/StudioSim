#pragma once


class HUD
{
public:
	HUD();
	~HUD();

	void DrawCharacterHP(bool hidden);
	void DrawBossHP(bool hidden);
	void UpdateCharacterHP();
	void UpdateBossHP();
};

