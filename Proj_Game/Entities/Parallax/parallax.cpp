#include "parallax.h"

ParallaxBackground::ParallaxBackground() :
	Ente(), backGrounds(), visionReference(nullptr), lastPosition(), layers_spd_proportion(1.f), size_coeff(1.f)
{};
ParallaxBackground::ParallaxBackground(sf::View* _view, float* elapsed_timeRef, const std::vector<std::string>& paths, const float size_coefficient):
	Ente(Ente::BACKGROUND, elapsed_timeRef), backGrounds(), visionReference(_view), lastPosition(), layers_spd_proportion(1.f), size_coeff(size_coefficient)
{
	this->SetBackgrounds(paths);
};
ParallaxBackground::~ParallaxBackground()
{};

void ParallaxBackground::Execute()
{
	std::list<Background>::iterator it;
	sf::Vector2f diff;
	float lestLim, maxLim;
	int i = 0, counter = 0;

	diff = this->lastPosition - this->visionReference->getCenter();
	lestLim = this->visionReference->getCenter().x - (this->visionReference->getSize().x / 2.f);
	maxLim = this->visionReference->getCenter().x + (this->visionReference->getSize().x / 2.f);

	for (i = 0, counter = -1, it = this->backGrounds.begin(); it != this->backGrounds.end(); it++, i++)
	{
		if ((i % 2) == 0)
			counter++;

		it->second.move(diff * (-layers_spd_proportion * counter));

		if (it->second.getPosition().x + it->second.getGlobalBounds().width < lestLim)
			it->second.move((it->second.getGlobalBounds().width * 2), 0.f);

		else if (it->second.getPosition().x > maxLim)
			it->second.move(-(it->second.getGlobalBounds().width * 2), 0.f);
	}

	this->lastPosition = this->visionReference->getCenter();
};
void ParallaxBackground::SelfPrint(sf::RenderWindow& context_window)
{
	std::list<Background>::reverse_iterator rIt;

	for(rIt = this->backGrounds.rbegin(); rIt != this->backGrounds.rend(); rIt++)
		context_window.draw(rIt->second);
};

unsigned int ParallaxBackground::GetBackgroundListSize()
{
	return this->backGrounds.size();
};
void ParallaxBackground::SetBackgrounds(const std::vector<std::string>& paths)
{
	std::vector<std::string>::const_iterator cIt;
	sf::RectangleShape* LastRectRef = nullptr;
	sf::Texture* lastTextRef = nullptr;
	sf::Texture txt;

	if (this->backGrounds.size() > 0)
		this->backGrounds.clear();

	/*
		Para cada path de textura para efeito parallax cria 2 objetos de 'Background' subsequentes em ordem na
		lista e em posição na tela, tal que, cada qual com o tamanho equilavente à 2 vezes a própria textura,
		efetivando o efeito de 4 texturas iguais em fila plotados na tela
	*/
	for (cIt = paths.cbegin(); cIt != paths.cend(); cIt++)
	{
		txt.loadFromFile(*cIt);

		this->backGrounds.emplace_back(
			Background(sf::Texture(txt), sf::RectangleShape())
		);

		lastTextRef = &this->backGrounds.back().first;
		LastRectRef = &this->backGrounds.back().second;

		lastTextRef->setRepeated(true);
		LastRectRef->setSize(sf::Vector2f(lastTextRef->getSize().x * 2.f, static_cast<float>(lastTextRef->getSize().y)));
		LastRectRef->setTexture(lastTextRef);
		LastRectRef->setTextureRect(sf::IntRect(0, 0, lastTextRef->getSize().x * 2, static_cast<unsigned int>(lastTextRef->getSize().y)));
		LastRectRef->setScale(this->size_coeff, this->size_coeff);

		this->backGrounds.emplace_back(
			Background(sf::Texture(txt), sf::RectangleShape())
		);

		lastTextRef = &this->backGrounds.back().first;
		LastRectRef = &this->backGrounds.back().second;

		lastTextRef->setRepeated(true);
		LastRectRef->setSize(sf::Vector2f(lastTextRef->getSize().x * 2.f, static_cast<float>(lastTextRef->getSize().y)));
		LastRectRef->setTexture(lastTextRef);
		LastRectRef->setTextureRect(sf::IntRect(0, 0, lastTextRef->getSize().x * 2, static_cast<unsigned int>(lastTextRef->getSize().y)));
		LastRectRef->setScale(this->size_coeff, this->size_coeff);
		LastRectRef->move((LastRectRef->getSize().x * this->size_coeff), 0.f);
	}

	/*
		O coefficiente de velocidade do background é dado pelo inverso do número de camadas do efeito parallax,
		logo, por haver duas 'unidades' de cada camado divido o tamanho da lista pela metade
	*/
	this->layers_spd_proportion = 1.f / (backGrounds.size() / 2.f);
	this->lastPosition = this->visionReference->getCenter();
};