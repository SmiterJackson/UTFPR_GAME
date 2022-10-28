#include "pauseInterface.h"

#define TEXT_SIZE 16
#define EXECUTION_PERIOD 0.1f

GUI::PauseInterface::PauseInterface(float* _pElapsedTime, short int* _pGameState, Camera* _pCamera, Mouse* _pMouse, 
									Stage* _pStage, std::vector<Ente*>* _pStateEnte, const std::string fontPath):
	Interface(_pGameState), background(), buttons(), pStage(_pStage), pStateEnte(_pStateEnte), acummulator(0.f)
{
	if(_pGameState != nullptr || _pCamera != nullptr || _pMouse != nullptr)
	{
		std::vector<std::string>::iterator it;
		std::vector<std::string> buttonsTxt;
		sf::Vector2f camSize(_pCamera->GetView()->getSize());
		sf::Vector2f aux(_pCamera->GetView()->getCenter());
		unsigned int mount = 1;

		buttonsTxt.emplace_back("VOLTAR");
		if(Characters::Player::GetNumberOfPlayers() < 2)
			buttonsTxt.emplace_back("INCLUIR P2");
		else
			buttonsTxt.emplace_back("EXCLUIR P2");
		buttonsTxt.emplace_back("MENU");

		this->SetElapsedTimeRef(_pElapsedTime);
		this->background.setSize(camSize);
		this->background.setOrigin(this->background.getSize() / 2.f);
		this->background.setFillColor(sf::Color(18, 18, 18, 84));
		this->background.setPosition(aux);

		this->buttons.reserve(buttonsTxt.size());
		for (it = buttonsTxt.begin(), mount = 1; it != buttonsTxt.end(); it++, mount++)
		{
			aux.y = (camSize.y / buttonsTxt.size()) * mount;
			this->buttons.emplace_back(
				_pCamera->GetView(), sf::Vector2f(aux), fontPath, (*it), TEXT_SIZE,
				_pMouse, sf::Color(187, 158, 132), sf::Color(240, 120, 16),
				sf::Color(80, 80, 80), sf::Color(60, 60, 60)
			);
		}
	}
};
GUI::PauseInterface::~PauseInterface()
{
	*this->pGameState = Game::STATE::PLAYING;
};

void GUI::PauseInterface::Execute()
{
	std::vector<Button>::iterator it;

	this->acummulator += *this->elapsedTime;

	if(this->acummulator >= EXECUTION_PERIOD)
	{
		for (it = this->buttons.begin(); it != this->buttons.end(); it++)
			it->Execute();

		this->acummulator -= EXECUTION_PERIOD;
	}
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
		*this->pGameState = Game::PLAYING;
	}
	else if(buttonIt->GetId() == this->buttons[1].GetId())
	{
		if (this->pStage != nullptr && Characters::Player::GetNumberOfPlayers() < 2)
		{
			this->pStage->AddPlayer();
			this->buttons[1].SetText("EXCLUIR P2");
		}
		else if (this->pStage != nullptr && Characters::Player::GetNumberOfPlayers() == 2)
		{
			this->pStage->RemovePlayer();
			this->buttons[1].SetText("INCLUIR P2");
		}
	}
	else
	{
		
	}
};
void GUI::PauseInterface::InputHandle(const sf::Event& _event)
{
	switch (_event.type)
	{
	case sf::Event::KeyPressed:
		if (_event.key.code == sf::Keyboard::Escape)
			*this->pGameState = Game::PLAYING;
		break;
	case sf::Event::MouseButtonPressed:
		this->VerifyButtons();
		break;
	default:
		break;
	}
};
void GUI::PauseInterface::SelfPrint(sf::RenderWindow& context_window)
{
	std::vector<Button>::iterator it;

	context_window.draw(this->background);

	for (it = this->buttons.begin(); it != this->buttons.end(); it++)
		it->SelfPrint(context_window);
};