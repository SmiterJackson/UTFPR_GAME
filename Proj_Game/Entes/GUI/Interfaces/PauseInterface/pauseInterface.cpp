#include "pauseInterface.h"
#include "../game/game.h"
#include "../Stage/stage.h"
#include "../Managers/GraphicManager/graphic_manager.h"
using namespace Manager;
using namespace Trait;
using namespace GUI;

#define TEXT_SIZE 16U
#define BTN_PROPORTION_TO_CAMERA 0.15f

#define BTN_VOLTAR	"VOLTAR"
#define BTN_INCLUIR "INCLUIR P2"
#define BTN_EXCLUIR "EXCLUIR"
#define BTN_MENU	"MENU"

StringToValue	PauseInterface::stringToValue = {
	StringToValue::value_type(BTN_VOLTAR,	Text::VOLTAR),
	StringToValue::value_type(BTN_INCLUIR,	Text::INCLUIR),
	StringToValue::value_type(BTN_EXCLUIR,	Text::EXCLUIR),
	StringToValue::value_type(BTN_MENU,		Text::MENU)
};

PauseInterface::PauseInterface():
	Interface(GameStateType::PAUSE_MENU),
	Observer(this->id),
	background(), buttons(), pStage(nullptr)
{};
PauseInterface::PauseInterface(Stage* _pStage):
	Interface(GameStateType::PAUSE_MENU, static_cast<Interface*>(_pStage)),
	Observer(this->id),
	background(), buttons(), pStage(_pStage)
{
	sf::Vector2f camSize(GraphicManager::GetViewSize());
	sf::Vector2f position(GraphicManager::GetViewPosition());
	sf::Vector2f btnSize(camSize * BTN_PROPORTION_TO_CAMERA);
	unsigned short int i = 0, counter = 2;
	StringToValue::iterator it;

	this->background.setSize(camSize);
	this->background.setOrigin(camSize / 2.f);
	this->background.setPosition(position);
	this->background.setFillColor(sf::Color(60, 6, 125, 40));

	this->buttons.reserve(3);
	for (it = stringToValue.begin(), counter = 2; it != stringToValue.end(); it++, counter++)
	{
		if (Characters::Player::GetNumberOfPlayers() >= 2 && it->first == BTN_INCLUIR)
			it++;
		if (Characters::Player::GetNumberOfPlayers() <= 1 && it->first == BTN_EXCLUIR)
			it++;

		position.y = 40.f + (camSize.y / 5) * counter;
		this->buttons.emplace_back(
				btnSize, position, it->first, TEXT_SIZE,
				sf::Color(255, 215, 60), sf::Color(255, 215, 60),
				sf::Color(30, 150, 95), sf::Color(20, 100, 63)
		);
	}
};
PauseInterface::~PauseInterface()
{};

void PauseInterface::SelfPrint(const float& pElapsedTime)
{
	std::vector<Button>::iterator it;

	this->PrintPreviousInterface(pElapsedTime);

	GraphicManager::Draw(this->background);
	for (it = this->buttons.begin(); it != this->buttons.end(); it++)
		it->SelfPrint(pElapsedTime);
};
void PauseInterface::UpdateObsever(const sf::Event& _event)
{
	if(Game::GetGameState() == GameStateType::PAUSE_MENU)
	{
		if(_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::Escape)
		{
			Game::SetGameState(GameStateType::IN_GAME);
			EventManager::InputSubject::InvertStopWarning();
		}
		else if(_event.type == sf::Event::MouseButtonPressed)
			this->VerifyButtons();
	}
};
void PauseInterface::Execute(const float& pElapsedTime)
{
	std::vector<Button>::iterator it;

	for (it = this->buttons.begin(); it != this->buttons.end(); it++)
		it->Execute(pElapsedTime);
};

void PauseInterface::VerifyButtons()
{
	std::vector<Button>::iterator it;
	unsigned short int aux = Text::NO_TEXT;

	for (it = this->buttons.begin(); it != this->buttons.end(); it++)
	{
		if (it->IsClicked())
		{
			aux = stringToValue[it->GetText()];

			if (stringToValue[it->GetText()] == Text::INCLUIR)
				it->SetText(BTN_EXCLUIR);
			else if (stringToValue[it->GetText()] == Text::EXCLUIR)
				it->SetText(BTN_INCLUIR);

			break;
		}
	}

	switch (aux)
	{
	case Text::VOLTAR:
		Game::SetGameState(GameStateType::IN_GAME);
		break;
	case Text::INCLUIR:
		if (Characters::Player::GetNumberOfPlayers() <= 1 && pStage != nullptr)
			pStage->AddPlayer();
		break;
	case Text::EXCLUIR:
		if (Characters::Player::GetNumberOfPlayers() >= 2 && pStage != nullptr)
			pStage->RemovePlayer();
		break;
	case Text::MENU:
		Game::SetGameState(GameStateType::MAIN_MENU);
		break;
	default:
		break;
	}
};