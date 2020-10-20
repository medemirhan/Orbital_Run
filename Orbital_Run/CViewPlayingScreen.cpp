#include "CViewPlayingScreen.h"

CViewPlayingScreen::CViewPlayingScreen()
{

}

CViewPlayingScreen::~CViewPlayingScreen()
{

}

void CViewPlayingScreen::SetSceneProperties()
{
	
	this->TextFont.loadFromFile("SlopeOpera.ttf");
	this->WarningFont.loadFromFile("ghostclan.ttf");
	
	sf::Texture entity_textures;
	entity_textures.setSmooth(true);
	entity_textures.loadFromFile("orbitron.png");
	this->EntityTextures.push_back(entity_textures);
	entity_textures.loadFromFile("monster.png");
	this->EntityTextures.push_back(entity_textures);
	entity_textures.loadFromFile("rocket_right.png");
	this->EntityTextures.push_back(entity_textures);
	entity_textures.loadFromFile("rocket_right.png");
	this->EntityTextures.push_back(entity_textures);
	entity_textures.loadFromFile("bomb.png");
	this->EntityTextures.push_back(entity_textures);
	entity_textures.loadFromFile("heart_green.png");
	this->EntityTextures.push_back(entity_textures);

	this->Mask.setFillColor(sf::Color(0, 0, 0, MASK_ALPHA));
	this->Mask.setPosition(0, 0);
	this->Mask.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));

	this->LevelIconTexture.loadFromFile("level.png");
	this->LevelIconTexture.setSmooth(true);
	this->LevelIcon.setTexture(this->LevelIconTexture);
	this->LevelIcon.setPosition(35.0f, 35.0f);
	this->LevelIcon.setOrigin(this->LevelIcon.getLocalBounds().width / 2.0f, this->LevelIcon.getLocalBounds().height / 2.0f);
	this->LevelIcon.setScale(sf::Vector2f(0.07f, 0.07f));

	this->LittlelifeIconTexture.loadFromFile("heart_green.png");
	this->LittlelifeIconTexture.setSmooth(true);
	this->LittlelifeIcon.setTexture(this->LittlelifeIconTexture);
	this->LittlelifeIcon.setPosition(35.0f, 85.0f);
	this->LittlelifeIcon.setOrigin(this->LittlelifeIcon.getLocalBounds().width / 2.0f, this->LittlelifeIcon.getLocalBounds().height / 2.0f);
	this->LittlelifeIcon.setScale(sf::Vector2f(0.07f, 0.07f));

	this->LifeIconTexture.loadFromFile("heart.png");
	this->LifeIconTexture.setSmooth(true);
	this->LifeIcon.setTexture(this->LifeIconTexture);
	this->LifeIcon.setPosition(35.0f, 135.0f);
	this->LifeIcon.setOrigin(this->LifeIcon.getLocalBounds().width / 2.0f, this->LifeIcon.getLocalBounds().height / 2.0f);
	this->LifeIcon.setScale(sf::Vector2f(0.07f, 0.07f));

	this->RocketRightIconTexture.loadFromFile("rocket_right.png");
	this->RocketRightIcon.setTexture(this->RocketRightIconTexture);
	this->RocketRightIcon.setPosition(35.0f, 183.0f);
	this->RocketRightIcon.setOrigin(this->RocketRightIcon.getLocalBounds().width / 2.0f, this->RocketRightIcon.getLocalBounds().height / 2.0f);
	this->RocketRightIcon.setScale(sf::Vector2f(0.08f, 0.08f));

	this->TxtGameLevel.setFillColor(sf::Color::White);
	this->TxtGameLevel.setFont(this->TextFont);
	this->TxtGameLevel.setCharacterSize(20);
	this->TxtGameLevel.setPosition(75.0f, 22.0f);
	this->TxtLittlelife.setFillColor(sf::Color::White);
	this->TxtLittlelife.setFont(this->TextFont);
	this->TxtLittlelife.setCharacterSize(20);
	this->TxtLittlelife.setPosition(75.0f, 73.0f);
	this->TxtLife.setFillColor(sf::Color::White);
	this->TxtLife.setFont(this->TextFont);
	this->TxtLife.setCharacterSize(20);
	this->TxtLife.setPosition(75.0f, 121.0f);
	this->TxtRocketRight.setFillColor(sf::Color::White);
	this->TxtRocketRight.setFont(this->TextFont);
	this->TxtRocketRight.setCharacterSize(20);
	this->TxtRocketRight.setPosition(75.0f, 170.0f);

	this->TxtLostLife.setFillColor(sf::Color::Green);
	this->TxtLostLife.setFont(this->WarningFont);
	this->TxtLostLife.setCharacterSize(65);
	this->TxtLostLife.setString("CRASHED!");
	sf::FloatRect txt_lost_life_rect = this->TxtLostLife.getLocalBounds();
	this->TxtLostLife.setOrigin(txt_lost_life_rect.left + txt_lost_life_rect.width / 2.0f, txt_lost_life_rect.top + txt_lost_life_rect.height / 2.0f);
	this->TxtLostLife.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f));

	this->TxtGameOver.setFillColor(sf::Color::Green);
	this->TxtGameOver.setFont(this->WarningFont);
	this->TxtGameOver.setCharacterSize(65);
	this->TxtGameOver.setString("GAME OVER!");
	sf::FloatRect txt_game_over_rect = this->TxtGameOver.getLocalBounds();
	this->TxtGameOver.setOrigin(txt_game_over_rect.left + txt_game_over_rect.width / 2.0f, txt_game_over_rect.top + txt_game_over_rect.height / 2.0f);
	this->TxtGameOver.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f));

	this->TxtGamePaused.setFillColor(sf::Color::Green);
	this->TxtGamePaused.setFont(this->WarningFont);
	this->TxtGamePaused.setCharacterSize(65);
	this->TxtGamePaused.setString("PAUSED");
	sf::FloatRect txt_game_paused_rect = this->TxtGamePaused.getLocalBounds();
	this->TxtGamePaused.setOrigin(txt_game_paused_rect.left + txt_game_paused_rect.width / 2.0f, txt_game_paused_rect.top + txt_game_paused_rect.height / 2.0f);
	this->TxtGamePaused.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f));

	this->TxtLostLifeOptions.setFillColor(sf::Color::Green);
	this->TxtLostLifeOptions.setFont(this->WarningFont);
	this->TxtLostLifeOptions.setCharacterSize(30);
	this->TxtLostLifeOptions.setString("Enter > Continue\nM      > Main Menu");
	sf::FloatRect txt_lost_life_options_rect = this->TxtLostLifeOptions.getLocalBounds();
	this->TxtLostLifeOptions.setOrigin(txt_lost_life_options_rect.left + txt_lost_life_options_rect.width / 2.0f, txt_lost_life_options_rect.top + txt_lost_life_options_rect.height / 2.0f);
	this->TxtLostLifeOptions.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f + 70.0f));

	this->TxtGameOverOptions.setFillColor(sf::Color::Green);
	this->TxtGameOverOptions.setFont(this->WarningFont);
	this->TxtGameOverOptions.setCharacterSize(30);
	this->TxtGameOverOptions.setString("Enter > Restart\nM      > Main Menu");
	sf::FloatRect txt_game_over_options_rect = this->TxtGameOverOptions.getLocalBounds();
	this->TxtGameOverOptions.setOrigin(txt_game_over_options_rect.left + txt_game_over_options_rect.width / 2.0f, txt_game_over_options_rect.top + txt_game_over_options_rect.height / 2.0f);
	this->TxtGameOverOptions.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f + 70.0f));

	this->TxtGamePausedOptions.setFillColor(sf::Color::Green);
	this->TxtGamePausedOptions.setFont(this->WarningFont);
	this->TxtGamePausedOptions.setCharacterSize(30);
	this->TxtGamePausedOptions.setString("Enter > Continue\nM      > Main Menu");
	sf::FloatRect txt_game_paused_options_rect = this->TxtGamePausedOptions.getLocalBounds();
	this->TxtGamePausedOptions.setOrigin(txt_game_paused_options_rect.left + txt_game_paused_options_rect.width / 2.0f, txt_game_paused_options_rect.top + txt_game_paused_options_rect.height / 2.0f);
	this->TxtGamePausedOptions.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f + 70.0f));

	this->TxtScore.setFillColor(sf::Color::White);
	this->TxtScore.setFont(this->WarningFont);
	this->TxtScore.setCharacterSize(75);

	this->Texture.loadFromFile("background.png");
	this->Texture.setSmooth(true);
	this->BackgroundSprite.setTexture(this->Texture);
}

void CViewPlayingScreen::GenerateOrbitDrawings(const CConfigurationData& init_config_data)
{
	for (INT32S i = 0; i < init_config_data.GetOrbitNumber(); i++) {
		//sf::CircleShape* p_orbit = new sf::CircleShape;
		std::shared_ptr<sf::CircleShape> p_orbit(new sf::CircleShape);
		this->Orbits.push_back(*p_orbit);
		//delete p_orbit;
		this->Orbits[i].setRadius(INNER_ORBIT_RADIUS + i * DISTANCE_BTW_ORBITS);
		this->Orbits[i].setFillColor(sf::Color::Transparent);
		this->Orbits[i].setOutlineThickness(ENTITY_OUTLINE_THICKNESS);
		this->Orbits[i].setOutlineColor(sf::Color(255, 255, 255));
		this->Orbits[i].setPosition(WINDOW_CENTER_X, WINDOW_CENTER_Y);
		this->Orbits[i].setOrigin(this->Orbits[i].getLocalBounds().width / 2.0f, this->Orbits[i].getLocalBounds().height / 2.0f);
		this->Orbits[i].setPointCount(ORBIT_POINT_COUNT);
	}
}

void CViewPlayingScreen::GenerateEntityDrawings(const CConfigurationData& init_config_data, const std::shared_ptr<CEntity> p_entity)
{
	std::shared_ptr<sf::Sprite> p_entity_drawing(new sf::Sprite);
	this->EntityDrawings.push_back(*p_entity_drawing);
	switch (p_entity->GetEntityType()) {
	case ENTITY_TYPES_ORBITRON:
		this->EntityDrawings.back().setTexture(this->EntityTextures[0]);
		this->EntityDrawings.back().setScale(sf::Vector2f(0.08f, 0.08f));
		break;
	case ENTITY_TYPES_MONSTER:
		this->EntityDrawings.back().setTexture(this->EntityTextures[1]);
		this->EntityDrawings.back().setScale(sf::Vector2f(0.05f, 0.05f));
		break;
	case ENTITY_TYPES_ROCKET:
		this->EntityDrawings.back().setTexture(this->EntityTextures[2]);
		this->EntityDrawings.back().setScale(sf::Vector2f(0.08f, 0.08f));
		break;
	case ENTITY_TYPES_ROCKET_RIGHT:
		this->EntityDrawings.back().setTexture(this->EntityTextures[3]);
		this->EntityDrawings.back().setScale(sf::Vector2f(0.08f, 0.08f));
		break;
	case ENTITY_TYPES_BOMB:
		this->EntityDrawings.back().setTexture(this->EntityTextures[4]);
		this->EntityDrawings.back().setScale(sf::Vector2f(0.05f, 0.05f));
		break;
	case ENTITY_TYPES_LIFE:
		this->EntityDrawings.back().setTexture(this->EntityTextures[5]);
		this->EntityDrawings.back().setScale(sf::Vector2f(0.05f, 0.05f));
		break;
	default:
		break;
	}
	this->EntityDrawings.back().setPosition(p_entity->GetPositionX(), p_entity->GetPositionY());
	this->EntityDrawings.back().setOrigin(this->EntityDrawings.back().getLocalBounds().width / 2.0f, this->EntityDrawings.back().getLocalBounds().height / 2.0f);
}

void CViewPlayingScreen::PrintScreen(sf::RenderWindow& app, std::vector<std::shared_ptr<CEntity>>& p_entity_list, E_STATES& game_state, INT32S num_orbits)
{
	//m.lock();
	//app.setActive(true);
	app.clear();
	app.draw(this->BackgroundSprite);
	for (INT32S i = 0; i < num_orbits; i++) {
		app.draw(this->Orbits[num_orbits - i - 1]);
	}
	for (INT32S i = 0; i < p_entity_list.size(); i++) {
		if (p_entity_list[i]->GetIsAlive() && p_entity_list[i]->GetNumLife() > 0) {
			if (p_entity_list[i]->GetEntityType() == ENTITY_TYPES_ROCKET) {
				this->EntityDrawings[i].setRotation(90.0f + p_entity_list[i]->GetAngle());
			}else {

			}
			app.draw(this->EntityDrawings[i]);
		}else {

		}
	}

	if (game_state == STATES_GAME_PAUSED || game_state == STATES_LOST_LIFE || game_state == STATES_GAME_OVER) {
		app.draw(this->Mask);
	}else {

	}

	if (game_state == STATES_GAME_OVER) {
		app.draw(this->TxtScore);
	}else {

	}

	app.draw(this->LevelIcon);
	app.draw(this->LittlelifeIcon);
	app.draw(this->LifeIcon);
	app.draw(this->RocketRightIcon);
	app.draw(this->TxtGameLevel);
	app.draw(this->TxtLife);
	app.draw(this->TxtLittlelife);
	app.draw(this->TxtRocketRight);

	switch (game_state) {
	case STATES_LOST_LIFE:
		app.draw(this->TxtLostLife);
		app.draw(this->TxtLostLifeOptions);
		break;
	case STATES_GAME_OVER:
		app.draw(this->TxtGameOver);
		app.draw(this->TxtGameOverOptions);
		break;
	case STATES_GAME_PAUSED:
		app.draw(this->TxtGamePaused);
		app.draw(this->TxtGamePausedOptions);
		break;
	default:
		break;
	}
	app.display();
	//app.setActive(false);
	//m.unlock();
}

void CViewPlayingScreen::UpdateIndicatorsView(FP32 game_level, INT32S indicator_num_life, INT32S indicator_num_littlelife, INT32S indicator_num_rocketright)
{
	std::ostringstream stream_game_level;
	stream_game_level << std::fixed;
	stream_game_level << std::setprecision(LEVEL_DISPLAY_PRECISION);
	stream_game_level << game_level;
	std::string string_game_level = stream_game_level.str();
	this->TxtGameLevel.setString(string_game_level);

	this->TxtLife.setString(std::to_string(indicator_num_life));
	this->TxtLittlelife.setString(std::to_string(indicator_num_littlelife));
	this->TxtRocketRight.setString(std::to_string(indicator_num_rocketright));

	this->TxtScore.setFont(this->WarningFont);
	this->TxtScore.setString("SCORE : " + string_game_level);
	sf::FloatRect txt_score_rect = this->TxtScore.getLocalBounds();
	this->TxtScore.setOrigin(txt_score_rect.left + txt_score_rect.width / 2.0f, txt_score_rect.top + txt_score_rect.height / 2.0f);
	this->TxtScore.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f - 220.0f));
}

void CViewPlayingScreen::UpdateEntityDrawings(const std::vector<INT32S>& idx)
{
	for (INT32S i = 0; i < idx.size(); i++) {
		this->EntityDrawings.erase(this->EntityDrawings.begin() + idx[i] - i);
	}
}

void CViewPlayingScreen::SetEntityDrawings(const std::vector<sf::Sprite>& entity_drawings)
{
	this->EntityDrawings = entity_drawings;
}

void CViewPlayingScreen::SetEntityTextures(const std::vector<sf::Texture>& textures)
{
	this->EntityTextures = textures;
}

void CViewPlayingScreen::SetOrbits(const std::vector<sf::CircleShape>& orbits)
{
	this->Orbits = orbits;
}

void CViewPlayingScreen::SetMask(const sf::RectangleShape& mask)
{
	this->Mask = mask;
}

void CViewPlayingScreen::SetTxtScore(const sf::Text& txt)
{
	this->TxtScore = txt;
}

void CViewPlayingScreen::SetTxtGameLevel(const sf::Text& txt)
{
	this->TxtGameLevel = txt;
}

void CViewPlayingScreen::SetTxtLife(const sf::Text& txt)
{
	this->TxtLife = txt;
}

void CViewPlayingScreen::SetTxtLittlelife(const sf::Text& txt)
{
	this->TxtLittlelife = txt;
}

void CViewPlayingScreen::SetTxtRocketRight(const sf::Text& txt)
{
	this->TxtRocketRight = txt;
}

void CViewPlayingScreen::SetTxtLostLife(const sf::Text& txt)
{
	this->TxtLostLife = txt;
}

void CViewPlayingScreen::SetTxtLostLifeOptions(const sf::Text& txt)
{
	this->TxtLostLifeOptions = txt;
}

void CViewPlayingScreen::SetTxtGameOver(const sf::Text& txt)
{
	this->TxtGameOver = txt;
}

void CViewPlayingScreen::SetTxtGameOverOptions(const sf::Text& txt)
{
	this->TxtGameOverOptions = txt;
}

void CViewPlayingScreen::SetTxtGamePaused(const sf::Text& txt)
{
	this->TxtGamePaused = txt;
}

void CViewPlayingScreen::SetTxtGamePausedOptions(const sf::Text& txt)
{
	this->TxtGamePausedOptions = txt;
}

void CViewPlayingScreen::SetBackgroundSprite(const sf::Sprite& sprite)
{
	this->BackgroundSprite = sprite;
}

void CViewPlayingScreen::SetLevelIcon(const sf::Sprite& sprite)
{
	this->LevelIcon = sprite;
}

void CViewPlayingScreen::SetLifeIcon(const sf::Sprite& sprite)
{
	this->LifeIcon = sprite;
}

void CViewPlayingScreen::SetLittlelifeIcon(const sf::Sprite& sprite)
{
	this->LittlelifeIcon = sprite;
}

void CViewPlayingScreen::SetRocketRightIcon(const sf::Sprite& sprite)
{
	this->RocketRightIcon = sprite;
}

void CViewPlayingScreen::SetFont(const sf::Font& font)
{
	this->Font = font;
}

void CViewPlayingScreen::SetTextFont(const sf::Font& font)
{
	this->TextFont = font;
}

void CViewPlayingScreen::SetWarningFont(const sf::Font& font)
{
	this->WarningFont = font;
}

void CViewPlayingScreen::SetTexture(const sf::Texture& texture)
{
	this->Texture = texture;
}

void CViewPlayingScreen::SetLevelIconTexture(const sf::Texture& texture)
{
	this->LevelIconTexture = texture;
}

void CViewPlayingScreen::SetLifeIconTexture(const sf::Texture& texture)
{
	this->LifeIconTexture = texture;
}

void CViewPlayingScreen::SetLittlelifeIconTexture(const sf::Texture& texture)
{
	this->LittlelifeIconTexture = texture;
}

void CViewPlayingScreen::SetRocketRightIconTexture(const sf::Texture& texture)
{
	this->RocketRightIconTexture = texture;
}

std::vector<sf::Sprite> CViewPlayingScreen::GetEntityDrawings() const
{
	return this->EntityDrawings;
}

std::vector<sf::Texture> CViewPlayingScreen::GetEntityTextures() const
{
	return this->EntityTextures;
}

std::vector<sf::CircleShape> CViewPlayingScreen::GetOrbits() const
{
	return this->Orbits;
}

sf::RectangleShape CViewPlayingScreen::GetMask() const
{
	return this->Mask;
}

sf::Text CViewPlayingScreen::GetTxtScore() const
{
	return this->TxtScore;
}

sf::Text CViewPlayingScreen::GetTxtGameLevel() const
{
	return this->TxtGameLevel;
}

sf::Text CViewPlayingScreen::GetTxtLife() const
{
	return this->TxtLife;
}

sf::Text CViewPlayingScreen::GetTxtLittlelife() const
{
	return this->TxtLittlelife;
}

sf::Text CViewPlayingScreen::GetTxtRocketRight() const
{
	return this->TxtRocketRight;
}

sf::Text CViewPlayingScreen::GetTxtLostLife() const
{
	return this->TxtLostLife;
}

sf::Text CViewPlayingScreen::GetTxtLostLifeOptions() const
{
	return this->TxtLostLifeOptions;
}

sf::Text CViewPlayingScreen::GetTxtGameOver() const
{
	return this->TxtGameOver;
}

sf::Text CViewPlayingScreen::GetTxtGameOverOptions() const
{
	return this->TxtGameOverOptions;
}

sf::Text CViewPlayingScreen::GetTxtGamePaused() const
{
	return this->TxtGamePaused;
}

sf::Text CViewPlayingScreen::GetTxtGamePausedOptions() const
{
	return this->TxtGamePausedOptions;
}

sf::Sprite CViewPlayingScreen::GetBackgroundSprite() const
{
	return this->BackgroundSprite;
}

sf::Sprite CViewPlayingScreen::GetLevelIcon() const
{
	return this->LevelIcon;
}

sf::Sprite CViewPlayingScreen::GetLifeIcon() const
{
	return this->LifeIcon;
}

sf::Sprite CViewPlayingScreen::GetLittlelifeIcon() const
{
	return this->LittlelifeIcon;
}

sf::Sprite CViewPlayingScreen::GetRocketRightIcon() const
{
	return this->RocketRightIcon;
}

sf::Font CViewPlayingScreen::GetFont() const
{
	return this->Font;
}

sf::Font CViewPlayingScreen::GetTextFont() const
{
	return this->TextFont;
}

sf::Font CViewPlayingScreen::GetWarningFont() const
{
	return this->WarningFont;
}

sf::Texture CViewPlayingScreen::GetTexture() const
{
	return this->Texture;
}

sf::Texture CViewPlayingScreen::GetLevelIconTexture() const
{
	return this->LevelIconTexture;
}

sf::Texture CViewPlayingScreen::GetLifeIconTexture() const
{
	return this->LifeIconTexture;
}

sf::Texture CViewPlayingScreen::GetLittlelifeIconTexture() const
{
	return this->LittlelifeIconTexture;
}

sf::Texture CViewPlayingScreen::GetRocketRightIconTexture() const
{
	return this->RocketRightIconTexture;
}
