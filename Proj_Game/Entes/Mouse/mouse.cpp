#include "mouse.h"

Mouse::Mouse(sf::RenderWindow* _pWindow):
	Ente(Type::MOUSE), pWindow(_pWindow), 
	mToDesktop(0.f, 0.f), mToWindow(0.f, 0.f), 
	mToView(0.f, 0.f), mToGrid(0, 0), gridSize(0.f)
{};
Mouse::Mouse(const float _gridSize, sf::RenderWindow* _pWindow):
	Ente(Type::MOUSE), pWindow(_pWindow), 
	mToDesktop(0.f, 0.f), mToWindow(0.f, 0.f),
	mToView(0.f, 0.f), mToGrid(0, 0), gridSize(_gridSize)
{};
Mouse::~Mouse()
{};

void Mouse::Execute(const float& pElapsedTime)
{
	if(this->pWindow != nullptr)
	{
		this->mToDesktop = static_cast<sf::Vector2f>(sf::Mouse::getPosition());
		this->mToWindow = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*this->pWindow));
		this->mToView = this->pWindow->mapPixelToCoords(sf::Mouse::getPosition(*this->pWindow));
		this->mToGrid = sf::Vector2i(this->mToView / this->gridSize);
	}
};