#include "CViewConfigMenu.h"

#define FLASH_TEXT_START_MSEC    500
#define FLASH_TEXT_STOP_MSEC     1000

CViewConfigMenu::CViewConfigMenu()
{
	this->CurrentSelection = 0;
	this->WaitingEntry = false;
}

CViewConfigMenu::~CViewConfigMenu()
{

}

void CViewConfigMenu::SetSceneProperties()
{
	this->Texture.setSmooth(true);
	this->Sprite.setTexture(this->Texture);
	this->Sprite.setColor(sf::Color(255, 255, 255));
	this->Font.loadFromFile("SlopeOpera.ttf");

	this->BackgroundTexture.loadFromFile("background.png");
	this->BackgroundTexture.setSmooth(true);
	this->BackgroundSprite.setTexture(this->BackgroundTexture);

	this->Text0.setFont(this->Font);
	this->Text0.setCharacterSize(30);
	this->Text0.setString("            Number of Orbits");
	this->Text0.setPosition({ 300.f, 220.f });
	this->TxtNumOrbits.setFont(this->Font);
	this->TxtNumOrbits.setCharacterSize(30);
	this->TxtNumOrbits.setString("");
	this->TxtNumOrbits.setPosition({ 750.f, 220.f });

	this->Text1.setFont(this->Font);
	this->Text1.setCharacterSize(30);
	this->Text1.setString("   Number of Monsters");
	this->Text1.setPosition({ 300.f, 290.f });
	this->TxtNumMonsters.setFont(this->Font);
	this->TxtNumMonsters.setCharacterSize(30);
	this->TxtNumMonsters.setString("");
	this->TxtNumMonsters.setPosition({ 750.f, 290.f });

	this->Text2.setFont(this->Font);
	this->Text2.setCharacterSize(30);
	this->Text2.setString("                Orbitron Speed");
	this->Text2.setPosition({ 300.f, 360.f });
	this->TxtVOrbitron.setFont(this->Font);
	this->TxtVOrbitron.setCharacterSize(30);
	this->TxtVOrbitron.setString("");
	this->TxtVOrbitron.setPosition({ 750.f, 360.f });

	this->Text3.setFont(this->Font);
	this->Text3.setCharacterSize(30);
	this->Text3.setString("                Monster Speed");
	this->Text3.setPosition({ 300.f, 430.f });
	this->TxtVMonster.setFont(this->Font);
	this->TxtVMonster.setCharacterSize(30);
	this->TxtVMonster.setString("");
	this->TxtVMonster.setPosition({ 750.f, 430.f });

	this->Text4.setFont(this->Font);
	this->Text4.setCharacterSize(30);
	this->Text4.setString("                         START GAME");
	this->Text4.setPosition({ 300.f, 550.f });

	this->Text5.setFont(this->Font);
	this->Text5.setCharacterSize(30);
	this->Text5.setString("                             MAIN MENU");
	this->Text5.setPosition({ 300.f, 620.f });
}

void CViewConfigMenu::PrintScreen(sf::RenderWindow& app, sf::Clock& flash_display_clock)
{
	app.clear();
	app.draw(this->BackgroundSprite);
	app.draw(this->Sprite);

	if (!this->WaitingEntry) {
		app.draw(this->Text0);
		app.draw(this->Text1);
		app.draw(this->Text2);
		app.draw(this->Text3);
		app.draw(this->TxtNumOrbits);
		app.draw(this->TxtNumMonsters);
		app.draw(this->TxtVOrbitron);
		app.draw(this->TxtVMonster);
	}
	else if (this->CurrentSelection == 0) {
		app.draw(this->Text1);
		app.draw(this->Text2);
		app.draw(this->Text3);
		app.draw(this->TxtNumMonsters);
		app.draw(this->TxtVOrbitron);
		app.draw(this->TxtVMonster);
		if (flash_display_clock.getElapsedTime().asMilliseconds() > FLASH_TEXT_START_MSEC && flash_display_clock.getElapsedTime().asMilliseconds() <= FLASH_TEXT_STOP_MSEC) {
			app.draw(this->Text0);
			app.draw(this->TxtNumOrbits);
		}
	}
	else if (this->CurrentSelection == 1) {
		app.draw(this->Text0);
		app.draw(this->Text2);
		app.draw(this->Text3);
		app.draw(this->TxtNumOrbits);
		app.draw(this->TxtVOrbitron);
		app.draw(this->TxtVMonster);
		if (flash_display_clock.getElapsedTime().asMilliseconds() > FLASH_TEXT_START_MSEC && flash_display_clock.getElapsedTime().asMilliseconds() <= FLASH_TEXT_STOP_MSEC) {
			app.draw(this->Text1);
			app.draw(this->TxtNumMonsters);
		}
	}
	else if (this->CurrentSelection == 2) {
		app.draw(this->Text0);
		app.draw(this->Text1);
		app.draw(this->Text3);
		app.draw(this->TxtNumOrbits);
		app.draw(this->TxtNumMonsters);
		app.draw(this->TxtVMonster);
		if (flash_display_clock.getElapsedTime().asMilliseconds() > FLASH_TEXT_START_MSEC && flash_display_clock.getElapsedTime().asMilliseconds() <= FLASH_TEXT_STOP_MSEC) {
			app.draw(this->Text2);
			app.draw(this->TxtVOrbitron);
		}
	}
	else if (this->CurrentSelection == 3) {
		app.draw(this->Text0);
		app.draw(this->Text1);
		app.draw(this->Text2);
		app.draw(this->TxtNumOrbits);
		app.draw(this->TxtNumMonsters);
		app.draw(this->TxtVOrbitron);
		if (flash_display_clock.getElapsedTime().asMilliseconds() > FLASH_TEXT_START_MSEC && flash_display_clock.getElapsedTime().asMilliseconds() <= FLASH_TEXT_STOP_MSEC) {
			app.draw(this->Text3);
			app.draw(this->TxtVMonster);
		}
	}
	if (flash_display_clock.getElapsedTime().asMilliseconds() > FLASH_TEXT_STOP_MSEC) {
		flash_display_clock.restart();
	}
	app.draw(this->Text4);
	app.draw(this->Text5);
	app.display();
}

void CViewConfigMenu::UpdateTextColors()
{
	this->Sprite.setColor(sf::Color(255, 255, 255));
	switch (this->CurrentSelection) {
	case 0:
		this->Text0.setFillColor(sf::Color(255, 0, 0));
		this->Text1.setFillColor(sf::Color(255, 255, 255));
		this->Text2.setFillColor(sf::Color(255, 255, 255));
		this->Text3.setFillColor(sf::Color(255, 255, 255));
		this->Text4.setFillColor(sf::Color(255, 255, 255));
		this->Text5.setFillColor(sf::Color(255, 255, 255));
		this->TxtNumOrbits.setFillColor(sf::Color(255, 0, 0));
		this->TxtNumMonsters.setFillColor(sf::Color(255, 255, 255));
		this->TxtVOrbitron.setFillColor(sf::Color(255, 255, 255));
		this->TxtVMonster.setFillColor(sf::Color(255, 255, 255));
		break;
	case 1:
		this->Text0.setFillColor(sf::Color(255, 255, 255));
		this->Text1.setFillColor(sf::Color(255, 0, 0));
		this->Text2.setFillColor(sf::Color(255, 255, 255));
		this->Text3.setFillColor(sf::Color(255, 255, 255));
		this->Text4.setFillColor(sf::Color(255, 255, 255));
		this->Text5.setFillColor(sf::Color(255, 255, 255));
		this->TxtNumOrbits.setFillColor(sf::Color(255, 255, 255));
		this->TxtNumMonsters.setFillColor(sf::Color(255, 0, 0));
		this->TxtVOrbitron.setFillColor(sf::Color(255, 255, 255));
		this->TxtVMonster.setFillColor(sf::Color(255, 255, 255));
		break;
	case 2:
		this->Text0.setFillColor(sf::Color(255, 255, 255));
		this->Text1.setFillColor(sf::Color(255, 255, 255));
		this->Text2.setFillColor(sf::Color(255, 0, 0));
		this->Text3.setFillColor(sf::Color(255, 255, 255));
		this->Text4.setFillColor(sf::Color(255, 255, 255));
		this->Text5.setFillColor(sf::Color(255, 255, 255));
		this->TxtNumOrbits.setFillColor(sf::Color(255, 255, 255));
		this->TxtNumMonsters.setFillColor(sf::Color(255, 255, 255));
		this->TxtVOrbitron.setFillColor(sf::Color(255, 0, 0));
		this->TxtVMonster.setFillColor(sf::Color(255, 255, 255));
		break;
	case 3:
		this->Text0.setFillColor(sf::Color(255, 255, 255));
		this->Text1.setFillColor(sf::Color(255, 255, 255));
		this->Text2.setFillColor(sf::Color(255, 255, 255));
		this->Text3.setFillColor(sf::Color(255, 0, 0));
		this->Text4.setFillColor(sf::Color(255, 255, 255));
		this->Text5.setFillColor(sf::Color(255, 255, 255));
		this->TxtNumOrbits.setFillColor(sf::Color(255, 255, 255));
		this->TxtNumMonsters.setFillColor(sf::Color(255, 255, 255));
		this->TxtVOrbitron.setFillColor(sf::Color(255, 255, 255));
		this->TxtVMonster.setFillColor(sf::Color(255, 0, 0));
		break;
	case 4:
		this->Text0.setFillColor(sf::Color(255, 255, 255));
		this->Text1.setFillColor(sf::Color(255, 255, 255));
		this->Text2.setFillColor(sf::Color(255, 255, 255));
		this->Text3.setFillColor(sf::Color(255, 255, 255));
		this->Text4.setFillColor(sf::Color(255, 0, 0));
		this->Text5.setFillColor(sf::Color(255, 255, 255));
		this->TxtNumOrbits.setFillColor(sf::Color(255, 255, 255));
		this->TxtNumMonsters.setFillColor(sf::Color(255, 255, 255));
		this->TxtVOrbitron.setFillColor(sf::Color(255, 255, 255));
		this->TxtVMonster.setFillColor(sf::Color(255, 255, 255));
		break;
	case 5:
		this->Text0.setFillColor(sf::Color(255, 255, 255));
		this->Text1.setFillColor(sf::Color(255, 255, 255));
		this->Text2.setFillColor(sf::Color(255, 255, 255));
		this->Text3.setFillColor(sf::Color(255, 255, 255));
		this->Text4.setFillColor(sf::Color(255, 255, 255));
		this->Text5.setFillColor(sf::Color(255, 0, 0));
		this->TxtNumOrbits.setFillColor(sf::Color(255, 255, 255));
		this->TxtNumMonsters.setFillColor(sf::Color(255, 255, 255));
		this->TxtVOrbitron.setFillColor(sf::Color(255, 255, 255));
		this->TxtVMonster.setFillColor(sf::Color(255, 255, 255));
		break;
	default:
		break;
	}
}