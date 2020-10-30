#pragma once
#include <thread>
#include <mutex>
#include <future>
#include <chrono>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <SFML/Graphics.hpp>
#include "CEntity.h"
#include "COrbitron.h"
#include "CMonster.h"
#include "CRocket.h"
#include "CRocketRight.h"
#include "CBomb.h"
#include "CLife.h"
#include "CView.h"
#include "CModel.h"
#include "CConfigurationData.h"
#include "CTimer.h"
#include "CGame.h"

class CViewPlayingScreen : public CView {
	friend class CControllerPlayingScreen;
private:
	std::vector<sf::Sprite> EntityDrawings;
	std::vector<sf::Texture> EntityTextures;
	std::vector<sf::CircleShape> Orbits;
	sf::RectangleShape Mask;
	sf::Text TxtScore, TxtGameLevel, TxtLife, TxtLittlelife, TxtRocketRight, TxtLostLife, TxtLostLifeOptions, TxtGameOver, TxtGameOverOptions, TxtGamePaused, TxtGamePausedOptions;
	sf::Sprite BackgroundSprite, LevelIcon, LifeIcon, LittlelifeIcon, RocketRightIcon;
	sf::Font Font, TextFont, WarningFont;
	sf::Texture Texture, LevelIconTexture, LifeIconTexture, LittlelifeIconTexture, RocketRightIconTexture;
public:
	CViewPlayingScreen();
	~CViewPlayingScreen();
	void SetSceneProperties() override;
	void GenerateOrbitDrawings(const CConfigurationData& config_data);
	void GenerateEntityDrawings(const CConfigurationData& config_data, const std::shared_ptr<CEntity> p_entity);
	void PrintScreen(CGame& game, sf::RenderWindow& window, const std::vector<std::shared_ptr<CEntity>>& p_entity_list, INT32S num_orbits);
	void UpdateIndicatorsView(FP32 game_level, INT32S indicator_num_life, INT32S indicator_num_littlelife, INT32S indicator_num_rocketright);
	void UpdateEntityDrawings(const std::vector<INT32S>& idx);

	void SetEntityDrawings(const std::vector<sf::Sprite>& entity_drawings);
	void SetEntityTextures(const std::vector<sf::Texture>& textures);
	void SetOrbits(const std::vector<sf::CircleShape>& orbits);
	void SetMask(const sf::RectangleShape& mask);
	void SetTxtScore(const sf::Text& txt);
	void SetTxtGameLevel(const sf::Text& txt);
	void SetTxtLife(const sf::Text& txt);
	void SetTxtLittlelife(const sf::Text& txt);
	void SetTxtRocketRight(const sf::Text& txt);
	void SetTxtLostLife(const sf::Text& txt);
	void SetTxtLostLifeOptions(const sf::Text& txt);
	void SetTxtGameOver(const sf::Text& txt);
	void SetTxtGameOverOptions(const sf::Text& txt);
	void SetTxtGamePaused(const sf::Text& txt);
	void SetTxtGamePausedOptions(const sf::Text& txt);
	void SetBackgroundSprite(const sf::Sprite& sprite);
	void SetLevelIcon(const sf::Sprite& sprite);
	void SetLifeIcon(const sf::Sprite& sprite);
	void SetLittlelifeIcon(const sf::Sprite& sprite);
	void SetRocketRightIcon(const sf::Sprite& sprite);
	void SetFont(const sf::Font& font);
	void SetTextFont(const sf::Font& font);
	void SetWarningFont(const sf::Font& font);
	void SetTexture(const sf::Texture& texture);
	void SetLevelIconTexture(const sf::Texture& texture);
	void SetLifeIconTexture(const sf::Texture& texture);
	void SetLittlelifeIconTexture(const sf::Texture& texture);
	void SetRocketRightIconTexture(const sf::Texture& texture);

	std::vector<sf::Sprite> GetEntityDrawings() const;
	std::vector<sf::Texture> GetEntityTextures() const;
	std::vector<sf::CircleShape> GetOrbits() const;
	sf::RectangleShape GetMask() const;
	sf::Text GetTxtScore() const;
	sf::Text GetTxtGameLevel() const;
	sf::Text GetTxtLife() const;
	sf::Text GetTxtLittlelife() const;
	sf::Text GetTxtRocketRight() const;
	sf::Text GetTxtLostLife() const;
	sf::Text GetTxtLostLifeOptions() const;
	sf::Text GetTxtGameOver() const;
	sf::Text GetTxtGameOverOptions() const;
	sf::Text GetTxtGamePaused() const;
	sf::Text GetTxtGamePausedOptions() const;
	sf::Sprite GetBackgroundSprite() const;
	sf::Sprite GetLevelIcon() const;
	sf::Sprite GetLifeIcon() const;
	sf::Sprite GetLittlelifeIcon() const;
	sf::Sprite GetRocketRightIcon() const;
	sf::Font GetFont() const;
	sf::Font GetTextFont() const;
	sf::Font GetWarningFont() const;
	sf::Texture GetTexture() const;
	sf::Texture GetLevelIconTexture() const;
	sf::Texture GetLifeIconTexture() const;
	sf::Texture GetLittlelifeIconTexture() const;
	sf::Texture GetRocketRightIconTexture() const;
};