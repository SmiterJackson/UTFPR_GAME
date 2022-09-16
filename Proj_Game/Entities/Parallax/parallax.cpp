#include "parallax.h"

#define NUM_BCKG_INSTANCES 3U

ParallaxBackground::ParallaxBackground() :
	Ente(), backGrounds(), visionReference(nullptr), lastPosition(), layers_spd_proportion(1.f), size_coeff(1.f)
{};
ParallaxBackground::ParallaxBackground(sf::View* _view, float* elapsed_timeRef, const std::vector<std::string>& paths, const float size_coefficient):
	Ente(Type::BACKGROUND, elapsed_timeRef), backGrounds(), visionReference(_view), lastPosition(), layers_spd_proportion(1.f), size_coeff(size_coefficient)
{
	this->SetBackgrounds(paths);
};
ParallaxBackground::~ParallaxBackground()
{};

void ParallaxBackground::Execute()
{
	sf::Sprite* pSprite = nullptr;
	sf::Vector2f diff;
	float lestLim = 0.f, maxLim = 0.f;
	unsigned int i = 0, j = 0;

	diff = this->lastPosition - this->visionReference->getCenter();
	lestLim = this->visionReference->getCenter().x - (this->visionReference->getSize().x / 2.f);
	maxLim = this->visionReference->getCenter().x + (this->visionReference->getSize().x / 2.f);

	/* 
		Para a quantidade de "layers", camadas, de backgrounds em função do número de cópias/instancias,
		move cada camada proporcinalmente a sua respectiva velocidade dado pela "posição da camada"
	*/
	for(i = 0; i < (this->backGrounds.size() / NUM_BCKG_INSTANCES); i++)
	{
		for(j = 0; j < NUM_BCKG_INSTANCES; j++)
		{
			pSprite = &this->backGrounds[(j + (i * NUM_BCKG_INSTANCES))].second;

			pSprite->move(diff * (-layers_spd_proportion * i));

			if (pSprite->getPosition().x + pSprite->getGlobalBounds().width < lestLim)
				pSprite->move((pSprite->getGlobalBounds().width * NUM_BCKG_INSTANCES), 0.f);

			else if (pSprite->getPosition().x > maxLim)
				pSprite->move(-(pSprite->getGlobalBounds().width * NUM_BCKG_INSTANCES), 0.f);
		}
	}

	this->lastPosition = this->visionReference->getCenter();
};
void ParallaxBackground::SelfPrint(sf::RenderWindow& context_window)
{
	std::vector<Background>::reverse_iterator rIt;

	for(rIt = this->backGrounds.rbegin(); rIt != this->backGrounds.rend(); rIt++)
		context_window.draw(rIt->second);
};

void ParallaxBackground::SetBackgrounds(const std::vector<std::string>& paths)
{
	std::vector<std::string>::const_iterator cIt;
	sf::Sprite* LastSpriteRef = nullptr;
	sf::Texture* lastTextRef = nullptr;
	sf::Texture txt;
	int i = 0;

	if (this->backGrounds.size() > 0)
		this->backGrounds.clear();

	/*
		Para cada path de textura para efeito parallax cria 2 objetos de 'Background' subsequentes em ordem na
		lista e em posição na tela, tal que, cada qual com o tamanho equilavente à 2 vezes a própria textura,
		efetivando o efeito de 4 texturas iguais em fila plotados na tela
	*/
	this->backGrounds.reserve(size_t(paths.size() * NUM_BCKG_INSTANCES));
	for (cIt = paths.cbegin(); cIt != paths.cend(); cIt++)
	{
		txt.loadFromFile(*cIt);

		for (i = 0; i < NUM_BCKG_INSTANCES; i++)
		{
			this->backGrounds.emplace_back(
				Background(sf::Texture(txt), sf::Sprite())
			);

			lastTextRef = &this->backGrounds.back().first;
			LastSpriteRef = &this->backGrounds.back().second;

			LastSpriteRef->setTexture(this->backGrounds.back().first);
			LastSpriteRef->setScale(this->size_coeff, this->size_coeff);
			LastSpriteRef->move((lastTextRef->getSize().x * this->size_coeff * i), 0.f);
		}
	}

	this->layers_spd_proportion = 1.f / (backGrounds.size() / static_cast<float>(NUM_BCKG_INSTANCES));
	this->lastPosition = this->visionReference->getCenter();
};
unsigned int ParallaxBackground::GetBackgroundListSize()
{
	return this->backGrounds.size();
};