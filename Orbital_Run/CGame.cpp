#include "CGame.h"
#include "CState.h"
#include "CStateMainMenu.h"
#include "CStateConfigMenu.h"
#include "CStatePlayingScreen.h"

//define and initialize static members 
CState* CGame::MainMenuState = new CStateMainMenu;
CState* CGame::ConfigMenuState = new CStateConfigMenu;
CState* CGame::PlayingState = new CStatePlayingScreen;

CGame::CGame()
{
	// We don't initialize static data member here, 
	// because static data initialization will happen on every constructor call.
	//this->MainMenuState = new CStateMainMenu;
	//this->ConfigMenuState = new CStateConfigMenu;
	//this->PlayingState = new CStatePlayingScreen;
	this->CurrentState = this->MainMenuState;
	this->CurrentState->OnEntry(this);
	this->IsRunning = true;
	this->FlagGameOver = false;
	this->FlagLostLife = false;
	this->FlagGamePaused = false;
}

CGame::~CGame()
{
	delete this->MainMenuState;
	delete this->ConfigMenuState;
	delete this->PlayingState;
}

void CGame::OnStateHandler(sf::RenderWindow& app, CConfigurationData& config_data, CModel& model)
{
	this->CurrentState->OnStateHandler(this, app, config_data, model);
}

CState* CGame::GetState()
{
	return this->CurrentState;
}

void CGame::SetIsRunning(BOOLEAN is_running)
{
	this->IsRunning = is_running;
}

void CGame::SetState(CState* new_state)
{
	// leave the current state - execute exit action
	this->CurrentState->OnExit(this);

	// state transistion
	this->CurrentState = new_state;

	// enter the new state - execute enter action
	this->CurrentState->OnEntry(this);
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