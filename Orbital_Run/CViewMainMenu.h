#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <mutex>
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

	void SetCurrentSelection(INT32S selection);
	void SetTexture(sf::Texture texture);
	void SetGameLogoTexture(sf::Texture texture);
	void SetBackgroundTexture(sf::Texture texture);
	void SetSprite(sf::Sprite sprite);
	void SetGameLogo(sf::Sprite sprite);
	void SetBackgroundSprite(sf::Sprite sprite);
	void SetFont(sf::Font font);
	void SetHeader(sf::Text text);
	void SetMenuOptionStartGame(sf::Text text);
	void SetMenuOptionConfigMenu(sf::Text text);
	void SetMenuOptionExit(sf::Text text);

	INT32S GetCurrentSelection() const;
	sf::Texture GetTexture() const;
	sf::Texture GetGameLogoTexture() const;
	sf::Texture GetBackgroundTexture() const;
	sf::Sprite GetSprite() const;
	sf::Sprite GetGameLogo() const;
	sf::Sprite GetBackgroundSprite() const;
	sf::Font GetFont() const;
	sf::Text GetHeader() const;
	sf::Text GetMenuOptionStartGame() const;
	sf::Text GetMenuOptionConfigMenu() const;
	sf::Text GetMenuOptionExit() const;
};