#include "CViewMainMenu.h"

CViewMainMenu::CViewMainMenu()
{
	this->CurrentSelection = 0;
}

CViewMainMenu::~CViewMainMenu()
{

}

void CViewMainMenu::SetSceneProperties()
{
	this->Texture.setSmooth(true);
	this->Sprite.setTexture(this->Texture);
	this->Sprite.setColor(sf::Color(255, 255, 255));
	this->Font.loadFromFile("SlopeOpera.ttf");

	this->BackgroundTexture.loadFromFile("background.png");
	this->BackgroundTexture.setSmooth(true);
	this->BackgroundSprite.setTexture(this->BackgroundTexture);

	this->GameLogoTexture.loadFromFile("game_logo.png");
	this->GameLogoTexture.setSmooth(true);
	this->GameLogo.setTexture(this->GameLogoTexture);
	this->GameLogo.setPosition(325.0f, 230.0f);
	this->GameLogo.setOrigin(this->GameLogo.getLocalBounds().width / 2.0f, this->GameLogo.getLocalBounds().height / 2.0f);
	this->GameLogo.setScale(sf::Vector2f(0.8f, 0.8f));

	this->Header.setFont(this->Font);
	this->Header.setCharacterSize(75);
	this->Header.setString("ORBITAL RUN");
	this->Header.setFillColor(sf::Color(115, 69, 190));
	sf::FloatRect header_rect = this->Header.getLocalBounds();
	this->Header.setOrigin(header_rect.left + header_rect.width / 2.0f, header_rect.top + header_rect.height / 2.0f);
	this->Header.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.0f + 80.0f, 230.0f));

	this->MenuOptionStartGame.setFont(this->Font);
	this->MenuOptionStartGame.setCharacterSize(35);
	this->MenuOptionStartGame.setString("Start Game");
	sf::FloatRect menu_option_start_game_rect = this->MenuOptionStartGame.getLocalBounds();
	this->MenuOptionStartGame.setOrigin(menu_option_start_game_rect.left + menu_option_start_game_rect.width / 2.0f, menu_option_start_game_rect.top + menu_option_start_game_rect.height / 2.0f);
	this->MenuOptionStartGame.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0));

	this->MenuOptionConfigMenu.setFont(this->Font);
	this->MenuOptionConfigMenu.setCharacterSize(35);
	this->MenuOptionConfigMenu.setString("Configure Settings");
	sf::FloatRect menu_option_config_menu_rect = this->MenuOptionConfigMenu.getLocalBounds();
	this->MenuOptionConfigMenu.setOrigin(menu_option_config_menu_rect.left + menu_option_config_menu_rect.width / 2.0f, menu_option_config_menu_rect.top + menu_option_config_menu_rect.height / 2.0f);
	this->MenuOptionConfigMenu.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f + 60.0f));

	this->MenuOptionExit.setFont(this->Font);
	this->MenuOptionExit.setCharacterSize(35);
	this->MenuOptionExit.setString("Exit");
	sf::FloatRect menu_option_exit_rect = this->MenuOptionExit.getLocalBounds();
	this->MenuOptionExit.setOrigin(menu_option_exit_rect.left + menu_option_exit_rect.width / 2.0f, menu_option_exit_rect.top + menu_option_exit_rect.height / 2.0f);
	this->MenuOptionExit.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f + 120.0f));
}

void CViewMainMenu::PrintScreen(sf::RenderWindow& app)
{
	//mutex.lock();
	app.clear();
	app.draw(this->BackgroundSprite);
	app.draw(this->Sprite);
	app.draw(this->GameLogo);
	app.draw(this->Header);
	app.draw(this->MenuOptionStartGame);
	app.draw(this->MenuOptionConfigMenu);
	app.draw(this->MenuOptionExit);
	app.display();
	//app.setActive(false);
	//mutex.unlock();
}

void CViewMainMenu::UpdateTextColors()
{
	this->Sprite.setColor(sf::Color(255, 255, 255));
	if (this->CurrentSelection == 0) {
		this->MenuOptionStartGame.setFillColor(sf::Color(255, 0, 0));
		this->MenuOptionConfigMenu.setFillColor(sf::Color(255, 255, 255));
		this->MenuOptionExit.setFillColor(sf::Color(255, 255, 255));
	}else if (this->CurrentSelection == 1) {
		this->MenuOptionStartGame.setFillColor(sf::Color(255, 255, 255));
		this->MenuOptionConfigMenu.setFillColor(sf::Color(255, 0, 0));
		this->MenuOptionExit.setFillColor(sf::Color(255, 255, 255));
	}else {
		this->MenuOptionStartGame.setFillColor(sf::Color(255, 255, 255));
		this->MenuOptionConfigMenu.setFillColor(sf::Color(255, 255, 255));
		this->MenuOptionExit.setFillColor(sf::Color(255, 0, 0));
	}
}

void CViewMainMenu::SetCurrentSelection(INT32S selection)
{
	this->CurrentSelection = selection;
}

void CViewMainMenu::SetTexture(sf::Texture texture)
{
	this->Texture = texture;
}

void CViewMainMenu::SetGameLogoTexture(sf::Texture texture)
{
	this->GameLogoTexture = texture;
}

void CViewMainMenu::SetBackgroundTexture(sf::Texture texture)
{
	this->BackgroundTexture = texture;
}

void CViewMainMenu::SetSprite(sf::Sprite sprite)
{
	this->Sprite = sprite;
}

void CViewMainMenu::SetGameLogo(sf::Sprite sprite)
{
	this->GameLogo = sprite;
}

void CViewMainMenu::SetBackgroundSprite(sf::Sprite sprite)
{
	this->BackgroundSprite = sprite;
}

void CViewMainMenu::SetFont(sf::Font font)
{
	this->Font = font;
}

void CViewMainMenu::SetHeader(sf::Text text)
{
	this->Header = text;
}

void CViewMainMenu::SetMenuOptionStartGame(sf::Text text)
{
	this->MenuOptionStartGame = text;
}

void CViewMainMenu::SetMenuOptionConfigMenu(sf::Text text)
{
	this->MenuOptionConfigMenu = text;
}

void CViewMainMenu::SetMenuOptionExit(sf::Text text)
{
	this->MenuOptionExit = text;
}

INT32S CViewMainMenu::GetCurrentSelection() const
{
	return this->CurrentSelection;
}

sf::Texture CViewMainMenu::GetTexture() const
{
	return this->Texture;
}

sf::Texture CViewMainMenu::GetGameLogoTexture() const
{
	return this->GameLogoTexture;
}

sf::Texture CViewMainMenu::GetBackgroundTexture() const
{
	return this->BackgroundTexture;
}

sf::Sprite CViewMainMenu::GetSprite() const
{
	return this->Sprite;
}

sf::Sprite CViewMainMenu::GetGameLogo() const
{
	return this->GameLogo;
}

sf::Sprite CViewMainMenu::GetBackgroundSprite() const
{
	return this->BackgroundSprite;
}

sf::Font CViewMainMenu::GetFont() const
{
	return this->Font;
}

sf::Text CViewMainMenu::GetHeader() const
{
	return this->Header;
}

sf::Text CViewMainMenu::GetMenuOptionStartGame() const
{
	return this->MenuOptionStartGame;
}

sf::Text CViewMainMenu::GetMenuOptionConfigMenu() const
{
	return this->MenuOptionConfigMenu;
}

sf::Text CViewMainMenu::GetMenuOptionExit() const
{
	return this->MenuOptionExit;
}
