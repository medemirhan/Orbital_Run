#include "CGame.h"
#include "CState.h"
#include "CStateMainMenu.h"
#include "CStateConfigMenu.h"
#include "CStatePlayingScreen.h"

CState* CGame::pMainMenuState = DBG_NEW CStateMainMenu;
CState* CGame::pConfigMenuState = DBG_NEW CStateConfigMenu;
CState* CGame::pPlayingState = DBG_NEW CStatePlayingScreen;

CGame::CGame()
{
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

/* Delegates its behaviour to the pCurrentState's OnStateHandler method */
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
	this->pCurrentState->OnExit(); /* leave current state and delegate execute exit action to pCurrentState's OnExit method */
	this->pCurrentState = p_state; /* set current state */
	this->pCurrentState->OnEntry(*this); /* enter new state and delegate entry action to pCurrentState's OnEntry method */
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