#include "CGame.h"
#include "CState.h"
#include "CStateMainMenu.h"
#include "CStateConfigMenu.h"
#include "CStatePlayingScreen.h"

//define and initialize static members 
CState* CGame::pMainMenuState = new CStateMainMenu;
CState* CGame::pConfigMenuState = new CStateConfigMenu;
CState* CGame::pPlayingState = new CStatePlayingScreen;

CGame::CGame()
{
	// We don't initialize static data member here, 
	// because static data initialization will happen on every constructor call.
	//this->pMainMenuState = new CStateMainMenu;
	//this->pConfigMenuState = new CStateConfigMenu;
	//this->pPlayingState = new CStatePlayingScreen;
	this->pCurrentState = this->pMainMenuState;
	this->pCurrentState->OnEntry(*this);
	this->IsRunning = true;
	this->FlagGameOver = false;
	this->FlagLostLife = false;
	this->FlagGamePaused = false;
}

CGame::~CGame()
{
	delete this->pMainMenuState;
	delete this->pConfigMenuState;
	delete this->pPlayingState;
}

void CGame::OnStateHandler(sf::RenderWindow& window, CConfigurationData& config_data, CModel& model)
{
	this->pCurrentState->OnStateHandler(*this, window, config_data, model);
}

CState* CGame::GetState()
{
	return this->pCurrentState;
}

void CGame::SetIsRunning(BOOLEAN is_running)
{
	this->IsRunning = is_running;
}

void CGame::SetState(CState* p_state)
{
	// leave the current state - execute exit action
	this->pCurrentState->OnExit(*this);

	// state transistion
	this->pCurrentState = p_state;

	// enter the new state - execute enter action
	this->pCurrentState->OnEntry(*this);
}

BOOLEAN CGame::GetIsRunning()
{
	return this->IsRunning;
}

void CGame::SetFlagGameOver(BOOLEAN flag)
{
	this->FlagGameOver = flag;
}

void CGame::SetFlagLostLife(BOOLEAN flag)
{
	this->FlagLostLife = flag;
}

void CGame::SetFlagGamePaused(BOOLEAN flag)
{
	this->FlagGamePaused = flag;
}

BOOLEAN CGame::GetFlagGameOver()
{
	return this->FlagGameOver;
}

BOOLEAN CGame::GetFlagLostLife()
{
	return this->FlagLostLife;
}

BOOLEAN CGame::GetFlagGamePaused()
{
	return this->FlagGamePaused;
}