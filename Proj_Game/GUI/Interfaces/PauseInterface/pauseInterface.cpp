#include "pauseInterface.h"
#include "../game/game.h"
#include "../Entes/Stage/stage.h"
#include "../Managers/GraphicManager/graphic_manager.h"
using namespace Manager;
using namespace Trait;
using namespace GUI;

#define TEXT_SIZE 16U
#define BTN_PROPORTION_TO_CAMERA 0.15f

const IntToText	PauseInterface::buttonsTxt = 
{
	IntToText::value_type(Text::VOLTAR,		"VOLTAR"),
	IntToText::value_type(Text::INCLUIR,	"INCLUIR P2"),
	IntToText::value_type(Text::EXCLUIR,	"EXCLUIR"),
	IntToText::value_type(Text::MENU,		"MENU")
};
StringToFunc PauseInterface::funcMap = 
{
	StringToFunc::value_type(buttonsTxt.at(Text::VOLTAR),	&ChangeGameState),
	StringToFunc::value_type(buttonsTxt.at(Text::INCLUIR),	&AddPlayer),
	StringToFunc::value_type(buttonsTxt.at(Text::EXCLUIR),	&RemovePlayer),
	StringToFunc::value_type(buttonsTxt.at(Text::MENU),		&ReturnToMainMenu)
};
Stage* PauseInterface::pStage = nullptr;

PauseInterface::PauseInterface():
	Interface(GameStateType::PAUSE_MENU),
	Observer(this->id),
	background(), buttons()
{};
PauseInterface::PauseInterface(Stage* _pStage):
	Interface(GameStateType::PAUSE_MENU, static_cast<Interface*>(_pStage)),
	Observer(this->id),
	background(), buttons()
{
	sf::Vector2f camSize(GraphicManager::GetView()->getSize());
	sf::Vector2f position(GraphicManager::GetView()->getCenter());
	sf::Vector2f btnSize(camSize * BTN_PROPORTION_TO_CAMERA);
	unsigned int i = 0, counter = 2;

	pStage = _pStage;

	this->background.setSize(camSize);
	this->background.setOrigin(camSize / 2.f);
	this->background.setPosition(position);
	this->background.setFillColor(sf::Color(60, 6, 125, 40));

	this->buttons.reserve(buttonsTxt.size());
	for (i = Text::VOLTAR, counter = 2; i <= Text::MENU; i++, counter++)
	{
		if (Characters::Player::GetNumberOfPlayers() >= 2 && i == Text::INCLUIR)
			i++;
		if (Characters::Player::GetNumberOfPlayers() == 1 && i == Text::EXCLUIR)
			i++;

		position.y = 40.f + (camSize.y / 5) * counter;
		this->buttons.emplace_back(
				btnSize, position, GraphicManager::GetFont(), buttonsTxt.at(i), TEXT_SIZE,
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
		switch (_event.type)
		{
		case sf::Event::KeyPressed:
			if (_event.key.code == sf::Keyboard::Escape)
			{
				Game::SetGameState(GameStateType::IN_GAME);
				EventManager::InputSubject::InvertStopWarning();
			}
			break;
		case sf::Event::MouseButtonPressed:
			this->VerifyButtons();
			break;
		default:
			break;
		}
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

	for (it = this->buttons.begin(); it != this->buttons.end(); it++)
	{
		if (it->IsClicked())
		{
			//Para o texto inserido nno botão e utilizado como chave do mapa de funções chama a função do dado texto
			funcMap[it->GetText()]();

			if (it->GetText() == buttonsTxt.at(Text::INCLUIR))
				it->SetText(buttonsTxt.at(Text::EXCLUIR));
			else if(it->GetText() == buttonsTxt.at(Text::EXCLUIR))
				it->SetText(buttonsTxt.at(Text::INCLUIR));

			break;
		}
	}
};

void PauseInterface::ChangeGameState()
{
	Game::SetGameState(GameStateType::IN_GAME);
};
void PauseInterface::AddPlayer()
{
	pStage->AddPlayer();
};
void PauseInterface::RemovePlayer()
{
	pStage->RemovePlayer();
};
void PauseInterface::ReturnToMainMenu()
{
	Game::SetGameState(GameStateType::MAIN_MENU);
};