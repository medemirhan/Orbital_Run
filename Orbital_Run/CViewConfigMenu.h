#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "CView.h"
#include "CModel.h"
#include "CConfigurationData.h"

class CViewConfigMenu : public CView {
	friend class CControllerConfigMenu;
private:
	INT32S CurrentSelection;
	BOOLEAN WaitingEntry;
	sf::String PlayerInput;
	sf::Text TxtNumOrbits, TxtNumMonsters, TxtVOrbitron, TxtVMonster, Text0, Text1, Text2, Text3, Text4, Text5;
	sf::Texture Texture, BackgroundTexture;
	sf::Sprite Sprite, BackgroundSprite;
	sf::Font Font;
public:
	CViewConfigMenu();
	CViewConfigMenu(CConfigurationData& config_data);
	~CViewConfigMenu();
	void SetSceneProperties();
	void PrintScreen(sf::RenderWindow& app, sf::Clock& flash_display_clock);
	void UpdateTextColors();
};