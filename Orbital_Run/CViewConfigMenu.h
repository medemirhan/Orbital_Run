#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <mutex>
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

	void SetCurrentSelection(INT32S selection);
	void SetWaitingEntry(BOOLEAN waiting_entry);
	void SetPlayerInput(sf::String input);
	void SetTxtNumOrbits(sf::Text txt);
	void SetTxtNumMonsters(sf::Text txt);
	void SetTxtVOrbitron(sf::Text txt);
	void SetTxtVMonster(sf::Text txt);
	void SetText0(sf::Text txt);
	void SetText1(sf::Text txt);
	void SetText2(sf::Text txt);
	void SetText3(sf::Text txt);
	void SetText4(sf::Text txt);
	void SetText5(sf::Text txt);
	void SetTexture(sf::Texture texture);
	void SetBackgroundTexture(sf::Texture texture);
	void SetSprite(sf::Sprite sprite);
	void SetBackgroundSprite(sf::Sprite sprite);
	void SetFont(sf::Font font);

	INT32S GetCurrentSelection() const;
	BOOLEAN GetWaitingEntry() const;
	sf::String GetPlayerInput() const;
	sf::Text GetTxtNumOrbits() const;
	sf::Text GetTxtNumMonsters() const;
	sf::Text GetTxtVOrbitron() const;
	sf::Text GetTxtVMonster() const;
	sf::Text GetText0() const;
	sf::Text GetText1() const;
	sf::Text GetText2() const;
	sf::Text GetText3() const;
	sf::Text GetText4() const;
	sf::Text GetText5() const;
	sf::Texture GetTexture() const;
	sf::Texture GetBackgroundTexture() const;
	sf::Sprite GetSprite() const;
	sf::Sprite GetBackgroundSprite() const;
	sf::Font GetFont() const;
};