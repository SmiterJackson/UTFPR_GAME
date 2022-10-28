#pragma once

#include "../Ente/ente.h"

class Mouse : public Ente
{
public:
	Mouse(sf::RenderWindow* _pWindow = nullptr);
	Mouse(const float _gridSize, sf::RenderWindow* _pWindow);
	~Mouse();

	void Execute(const float& pElapsedTime);

	const sf::Vector2f const GetMouseToDesktop() { return this->mToDesktop; };
	const sf::Vector2f const GetMouseToWindow() { return this->mToWindow; };
	const sf::Vector2f const GetMouseToView() { return this->mToView; };
	const sf::Vector2i const GetMouseToGrid() { return this->mToGrid; };

	void SetGridSize(const float _gridSize) { this->gridSize = _gridSize; };
	void SetWindowReference(sf::RenderWindow* _pWindow) { this->pWindow = _pWindow; };

private:
	sf::RenderWindow* pWindow;

	sf::Vector2f mToDesktop;
	sf::Vector2f mToWindow;
	sf::Vector2f mToView;

	sf::Vector2i mToGrid;

	float gridSize;
};