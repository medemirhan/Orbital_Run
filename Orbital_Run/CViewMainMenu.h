#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "CView.h"
#include "CModel.h"
#include "CConfigurationData.h"
//#include "type_definitions.h"

class CViewMainMenu : public CView {
	friend class CControllerMainMenu;
private:
	INT32S CurrentSelection;
	sf::Texture Texture, GameLogoTexture, BackgroundTexture;
	sf::Sprite Sprite, GameLogo, BackgroundSprite;
	sf::Font Font;
	sf::Text Header, MenuOptionStartGame, MenuOptionConfigMenu, MenuOptionExit;
public:
	CViewMainMenu();
	~CViewMainMenu();
	void SetSceneProperties();
	void PrintScreen(sf::RenderWindow& app);
	void UpdateTextColors();
};