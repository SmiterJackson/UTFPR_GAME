#pragma once

#include "../Ente/ente.h"

class Mouse : public Ente
{
public:
	Mouse(sf::RenderWindow* _pWindow = nullptr);
	Mouse(const float _gridSize, sf::RenderWindow* _pWindow = nullptr);
	~Mouse();

	const sf::Vector2f GetMouseToDesktop() const { return this->mToDesktop; };
	const sf::Vector2f GetMouseToWindow() const { return this->mToWindow; };
	const sf::Vector2f GetMouseToView() const { return this->mToView; };
	const sf::Vector2i GetMouseToGrid() const { return this->mToGrid; };

	void SetGridSize(const float _gridSize) { this->gridSize = _gridSize; };
	void SetWindowReference(sf::RenderWindow* _pWindow) { this->pWindow = _pWindow; };

	void Execute(const float& pElapsedTime);

private:
	sf::RenderWindow* pWindow;

	sf::Vector2f mToDesktop;
	sf::Vector2f mToWindow;
	sf::Vector2f mToView;

	sf::Vector2i mToGrid;

	float gridSize;
};