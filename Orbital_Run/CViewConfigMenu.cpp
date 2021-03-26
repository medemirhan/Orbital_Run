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

/* Sets scene properties such as textures, fonts, texts etc. */
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
	this->Text0.setString("            Number of Orbits   (" + std::to_string(INT32S(LOWER_LIMIT_ORBIT_NUM)) + " - " + std::to_string(INT32S(UPPER_LIMIT_ORBIT_NUM)) + ")");
	this->Text0.setPosition({ 300.f, 220.f });
	this->TxtNumOrbits.setFont(this->Font);
	this->TxtNumOrbits.setCharacterSize(30);
	this->TxtNumOrbits.setString("");
	this->TxtNumOrbits.setPosition({ 900.f, 220.f });

	this->Text1.setFont(this->Font);
	this->Text1.setCharacterSize(30);
	this->Text1.setString("   Number of Monsters   (" + std::to_string(INT32S(LOWER_LIMIT_MONSTER_NUM)) + " - " + std::to_string(INT32S(UPPER_LIMIT_MONSTER_NUM)) + ")");
	this->Text1.setPosition({ 300.f, 290.f });
	this->TxtNumMonsters.setFont(this->Font);
	this->TxtNumMonsters.setCharacterSize(30);
	this->TxtNumMonsters.setString("");
	this->TxtNumMonsters.setPosition({ 900.f, 290.f });

	this->Text2.setFont(this->Font);
	this->Text2.setCharacterSize(30);
	this->Text2.setString("                Orbitron Speed   (" + std::to_string(INT32S(LOWER_LIMIT_ORBITRON_VEL / VELOCITY_TRANSFORM_COEFF)) + " - " + std::to_string(INT32S(UPPER_LIMIT_ORBITRON_VEL / VELOCITY_TRANSFORM_COEFF)) + ")");
	this->Text2.setPosition({ 300.f, 360.f });
	this->TxtVOrbitron.setFont(this->Font);
	this->TxtVOrbitron.setCharacterSize(30);
	this->TxtVOrbitron.setString("");
	this->TxtVOrbitron.setPosition({ 900.f, 360.f });

	this->Text3.setFont(this->Font);
	this->Text3.setCharacterSize(30);
	this->Text3.setString("                Monster Speed   (" + std::to_string(INT32S(LOWER_LIMIT_MONSTER_VEL / VELOCITY_TRANSFORM_COEFF)) + " - " + std::to_string(INT32S(UPPER_LIMIT_MONSTER_VEL / VELOCITY_TRANSFORM_COEFF)) + ")");
	this->Text3.setPosition({ 300.f, 430.f });
	this->TxtVMonster.setFont(this->Font);
	this->TxtVMonster.setCharacterSize(30);
	this->TxtVMonster.setString("");
	this->TxtVMonster.setPosition({ 900.f, 430.f });

	this->Text4.setFont(this->Font);
	this->Text4.setCharacterSize(30);
	this->Text4.setString("                         START GAME");
	this->Text4.setPosition({ 300.f, 590.f });

	this->Text5.setFont(this->Font);
	this->Text5.setCharacterSize(30);
	this->Text5.setString("                             MAIN MENU");
	this->Text5.setPosition({ 300.f, 660.f });
}

/* Prints current scene */
void CViewConfigMenu::PrintScreen(sf::RenderWindow& window, sf::Clock& flash_display_clock)
{
	//mutex.lock();
	window.clear();
	window.draw(this->BackgroundSprite);
	window.draw(this->Sprite);

	if (!this->WaitingEntry) {
		window.draw(this->Text0);
		window.draw(this->Text1);
		window.draw(this->Text2);
		window.draw(this->Text3);
		window.draw(this->TxtNumOrbits);
		window.draw(this->TxtNumMonsters);
		window.draw(this->TxtVOrbitron);
		window.draw(this->TxtVMonster);
	}else if (this->CurrentSelection == 0) {
		window.draw(this->Text1);
		window.draw(this->Text2);
		window.draw(this->Text3);
		window.draw(this->TxtNumMonsters);
		window.draw(this->TxtVOrbitron);
		window.draw(this->TxtVMonster);
		if (flash_display_clock.getElapsedTime().asMilliseconds() > FLASH_TEXT_START_MSEC && flash_display_clock.getElapsedTime().asMilliseconds() <= FLASH_TEXT_STOP_MSEC) {
			window.draw(this->Text0);
			window.draw(this->TxtNumOrbits);
		}else {

		}
	}else if (this->CurrentSelection == 1) {
		window.draw(this->Text0);
		window.draw(this->Text2);
		window.draw(this->Text3);
		window.draw(this->TxtNumOrbits);
		window.draw(this->TxtVOrbitron);
		window.draw(this->TxtVMonster);
		if (flash_display_clock.getElapsedTime().asMilliseconds() > FLASH_TEXT_START_MSEC && flash_display_clock.getElapsedTime().asMilliseconds() <= FLASH_TEXT_STOP_MSEC) {
			window.draw(this->Text1);
			window.draw(this->TxtNumMonsters);
		}else {

		}
	}else if (this->CurrentSelection == 2) {
		window.draw(this->Text0);
		window.draw(this->Text1);
		window.draw(this->Text3);
		window.draw(this->TxtNumOrbits);
		window.draw(this->TxtNumMonsters);
		window.draw(this->TxtVMonster);
		if (flash_display_clock.getElapsedTime().asMilliseconds() > FLASH_TEXT_START_MSEC && flash_display_clock.getElapsedTime().asMilliseconds() <= FLASH_TEXT_STOP_MSEC) {
			window.draw(this->Text2);
			window.draw(this->TxtVOrbitron);
		}else {

		}
	}else if (this->CurrentSelection == 3) {
		window.draw(this->Text0);
		window.draw(this->Text1);
		window.draw(this->Text2);
		window.draw(this->TxtNumOrbits);
		window.draw(this->TxtNumMonsters);
		window.draw(this->TxtVOrbitron);
		if (flash_display_clock.getElapsedTime().asMilliseconds() > FLASH_TEXT_START_MSEC && flash_display_clock.getElapsedTime().asMilliseconds() <= FLASH_TEXT_STOP_MSEC) {
			window.draw(this->Text3);
			window.draw(this->TxtVMonster);
		}else {

		}
	}else {

	}
	if (flash_display_clock.getElapsedTime().asMilliseconds() > FLASH_TEXT_STOP_MSEC) {
		flash_display_clock.restart();
	}else {

	}
	window.draw(this->Text4);
	window.draw(this->Text5);
	window.display();
	//window.setActive(false);
	//mutex.unlock();
}

/* Updates text colors depending on the user's button actions */
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

void CViewConfigMenu::SetCurrentSelection(INT32S selection)
{
	this->CurrentSelection = selection;
}

void CViewConfigMenu::SetWaitingEntry(BOOLEAN waiting_entry)
{
	this->WaitingEntry = waiting_entry;
}

void CViewConfigMenu::SetPlayerInput(sf::String input)
{
	this->PlayerInput = input;
}

void CViewConfigMenu::SetTxtNumOrbits(sf::Text txt)
{
	this->TxtNumOrbits = txt;
}

void CViewConfigMenu::SetTxtNumMonsters(sf::Text txt)
{
	this->TxtNumMonsters = txt;
}

void CViewConfigMenu::SetTxtVOrbitron(sf::Text txt)
{
	this->TxtVOrbitron = txt;
}

void CViewConfigMenu::SetTxtVMonster(sf::Text txt)
{
	this->TxtVMonster = txt;
}

void CViewConfigMenu::SetText0(sf::Text txt)
{
	this->Text0 = txt;
}

void CViewConfigMenu::SetText1(sf::Text txt)
{
	this->Text1 = txt;
}

void CViewConfigMenu::SetText2(sf::Text txt)
{
	this->Text2 = txt;
}

void CViewConfigMenu::SetText3(sf::Text txt)
{
	this->Text3 = txt;
}

void CViewConfigMenu::SetText4(sf::Text txt)
{
	this->Text4 = txt;
}

void CViewConfigMenu::SetText5(sf::Text txt)
{
	this->Text5 = txt;
}

void CViewConfigMenu::SetTexture(sf::Texture texture)
{
	this->Texture = texture;
}

void CViewConfigMenu::SetBackgroundTexture(sf::Texture texture)
{
	this->BackgroundTexture = texture;
}

void CViewConfigMenu::SetSprite(sf::Sprite sprite)
{
	this->Sprite = sprite;
}

void CViewConfigMenu::SetBackgroundSprite(sf::Sprite sprite)
{
	this->BackgroundSprite = sprite;
}

void CViewConfigMenu::SetFont(sf::Font font)
{
	this->Font = font;
}

INT32S CViewConfigMenu::GetCurrentSelection() const
{
	return this->CurrentSelection;
}

BOOLEAN CViewConfigMenu::GetWaitingEntry() const
{
	return this->WaitingEntry;
}

sf::String CViewConfigMenu::GetPlayerInput() const
{
	return this->PlayerInput;
}

sf::Text CViewConfigMenu::GetTxtNumOrbits() const
{
	return this->TxtNumOrbits;
}

sf::Text CViewConfigMenu::GetTxtNumMonsters() const
{
	return this->TxtNumMonsters;
}

sf::Text CViewConfigMenu::GetTxtVOrbitron() const
{
	return this->TxtVOrbitron;
}

sf::Text CViewConfigMenu::GetTxtVMonster() const
{
	return this->TxtVMonster;
}

sf::Text CViewConfigMenu::GetText0() const
{
	return this->Text0;
}

sf::Text CViewConfigMenu::GetText1() const
{
	return this->Text1;
}

sf::Text CViewConfigMenu::GetText2() const
{
	return this->Text2;
}

sf::Text CViewConfigMenu::GetText3() const
{
	return this->Text3;
}

sf::Text CViewConfigMenu::GetText4() const
{
	return this->Text4;
}

sf::Text CViewConfigMenu::GetText5() const
{
	return this->Text5;
}

sf::Texture CViewConfigMenu::GetTexture() const
{
	return this->Texture;
}

sf::Texture CViewConfigMenu::GetBackgroundTexture() const
{
	return this->BackgroundTexture;
}

sf::Sprite CViewConfigMenu::GetSprite() const
{
	return this->Sprite;
}

sf::Sprite CViewConfigMenu::GetBackgroundSprite() const
{
	return this->BackgroundSprite;
}

sf::Font CViewConfigMenu::GetFont() const
{
	return this->Font;
}
