#include "pauseInterface.h"
using namespace Manager;
using namespace Trait;

#define TEXT_SIZE 16
#define BTN_PROPORTION_TO_CAMERA 0.2f

GUI::PauseInterface::PauseInterface():
	Interface(GameStateType::PAUSE_MENU),
	pGameState(nullptr), pStage(nullptr)
{};
GUI::PauseInterface::PauseInterface(unsigned short int* _pGameState, Mouse* _pMouse, Stage* _pStage):
	Interface(GameStateType::PAUSE_MENU, static_cast<Interface*>(_pStage)),
	pGameState(_pGameState), pStage(_pStage)
{
	std::vector<std::string>::iterator it;
	std::vector<std::string> buttonsTxt;

	sf::Vector2f camSize(GraphicManager::GetView()->getSize());
	sf::Vector2f position(GraphicManager::GetView()->getCenter());
	sf::Vector2f btnSize(camSize * BTN_PROPORTION_TO_CAMERA);

	unsigned int counter = 1;

	buttonsTxt.emplace_back("VOLTAR");
	if(Characters::Player::GetNumberOfPlayers() < 2)
		buttonsTxt.emplace_back("INCLUIR P2");
	else
		buttonsTxt.emplace_back("EXCLUIR P2");
	buttonsTxt.emplace_back("MENU");

	this->buttons.reserve(buttonsTxt.size());
	for (it = buttonsTxt.begin(), counter = 1; it != buttonsTxt.end(); it++, counter++)
	{
		position.y = (camSize.y / buttonsTxt.size()) * counter;
		this->buttons.emplace_back(
			btnSize, position, GraphicManager::GetFont(),
			(*it), TEXT_SIZE, _pMouse,
			sf::Color(187, 158, 132), sf::Color(240, 120, 16),
			sf::Color(80, 80, 80), sf::Color(60, 60, 60)
		);
	}
};
GUI::PauseInterface::~PauseInterface()
{};

void GUI::PauseInterface::SelfPrint(sf::RenderWindow& context_window, const float& pElapsedTime)
{
	std::vector<Button>::iterator it;

	this->PrintPreviousInterface(context_window, pElapsedTime);

	for (it = this->buttons.begin(); it != this->buttons.end(); it++)
		it->SelfPrint(context_window, pElapsedTime);
};
void GUI::PauseInterface::InputHandle(const sf::Event& _event)
{
	switch (_event.type)
	{
	case sf::Event::KeyPressed:
		if (_event.key.code == sf::Keyboard::Escape)
			*this->pGameState = GameStateType::IN_GAME;
		break;
	case sf::Event::MouseButtonPressed:
		this->VerifyButtons();
		break;
	default:
		break;
	}
};
void GUI::PauseInterface::Execute(const float& pElapsedTime)
{
	std::vector<Button>::iterator it;

	for (it = this->buttons.begin(); it != this->buttons.end(); it++)
		it->Execute(pElapsedTime);
};

void GUI::PauseInterface::VerifyButtons()
{
	std::vector<Button>::iterator it;

	for (it = this->buttons.begin(); it != this->buttons.end(); it++)
	{
		if (it->IsClicked())
		{
			this->ButtonActive(it);
			break;
		}
	}
};
void GUI::PauseInterface::ButtonActive(std::vector<Button>::iterator buttonIt)
{
	if(buttonIt->GetId() == this->buttons[0].GetId())
	{
		*this->pGameState = Trait::GameStateType::IN_GAME;
	}
	else if(buttonIt->GetId() == this->buttons[1].GetId())
	{
		if (Characters::Player::GetNumberOfPlayers() >= 2)
		{
			this->pStage->AddPlayer();
			this->buttons[1].SetText("EXCLUIR P2");
		}
		else if (Characters::Player::GetNumberOfPlayers() < 2)
		{
			this->pStage->RemovePlayer();
			this->buttons[1].SetText("INCLUIR P2");
		}
	}
	else
	{
		
	}
};