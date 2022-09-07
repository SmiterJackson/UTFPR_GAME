#pragma once

#include "../../Managers/Colision Manager/colisionManager.h"
#include "../../Entities/Parallax/parallax.h"
#include "../../ListConteiner/lista.h"

class Stage : public Ente
{
public:
	Stage();
	Stage(sf::FloatRect mapBounds, sf::View* _view, const std::vector<std::string>& paths, const float size_coefficient);
	~Stage();

	virtual void ReadArchive(const std::string name) = 0;
	virtual void Execute(const float elapsedTime) = 0;
	virtual void SelfPrint(sf::RenderWindow& context_window, const float elapsedTime) = 0;

protected:
	sf::FloatRect mapBounds;

	ColisionManager colision_manager;
	ParallaxBackground background;

	Lista<Entity*> entities;
};