#include "parallax.h"

#define NUM_BCKG_INSTANCES 3U

ParallaxBackground::ParallaxBackground() :
	Ente(), backGrounds(), visionReference(nullptr), 
	lastPosition(sf::Vector2f(0.f, 0.f)), layers_spd_proportion(1.f), size_coeff(1.f)
{};
ParallaxBackground::ParallaxBackground(sf::View* _view, float* elapsed_timeRef, const std::vector<std::string>& paths, const float size_coefficient):
	Ente(Type::BACKGROUND, elapsed_timeRef), backGrounds(), visionReference(_view), 
	lastPosition(sf::Vector2f(0.f, 0.f)), layers_spd_proportion(1.f), size_coeff(size_coefficient)
{
	this->SetBackgrounds(paths);
};
ParallaxBackground::~ParallaxBackground()
{};

void ParallaxBackground::Execute()
{
	std::vector<Background>::iterator it;
	sf::Sprite* pSprite = nullptr;
	sf::Vector2f diff, movement;
	float lestLim = 0.f, maxLim = 0.f, counter = 1.f;
	unsigned int i = 0, j = 0;

	diff = this->lastPosition - this->visionReference->getCenter();
	lestLim = this->visionReference->getCenter().x - (this->visionReference->getSize().x / 2.f);
	maxLim = this->visionReference->getCenter().x + (this->visionReference->getSize().x / 2.f);

	/* 
		Para a quantidade de "layers", camadas, de backgrounds em função do número de cópias/instancias,
		move cada camada proporcinalmente a sua respectiva velocidade dado pela "posição da camada"
	*/
	if(diff.x != 0.f || diff.y != 0.f)
	{
		for (it = this->backGrounds.begin(), i = 0; it != this->backGrounds.end(); i++, it++)
		{
			movement = diff * (-layers_spd_proportion * i);

			for (j = 0; j < it->second.size(); j++)
			{
				pSprite = &it->second[j];

				pSprite->move(movement);

				if (pSprite->getPosition().x + pSprite->getGlobalBounds().width < lestLim)
					pSprite->move((pSprite->getGlobalBounds().width * NUM_BCKG_INSTANCES), 0.f);

				else if (pSprite->getPosition().x > maxLim)
					pSprite->move(-(pSprite->getGlobalBounds().width * NUM_BCKG_INSTANCES), 0.f);
			}
		}
	}

	this->lastPosition = this->visionReference->getCenter();
};
void ParallaxBackground::SelfPrint(sf::RenderWindow& context_window)
{
	std::vector<Background>::reverse_iterator rIt;
	size_t i = 0;

	for(rIt = this->backGrounds.rbegin(); rIt != this->backGrounds.rend(); rIt++)
		for(i = 0; i < rIt->second.size(); i++)
			context_window.draw(rIt->second[i]);
};

void ParallaxBackground::ResetPosition()
{
	std::vector<Background>::iterator backIt;
	std::vector<sf::Sprite>::iterator SpriteIt;
	unsigned int i = 0;

	for(backIt = this->backGrounds.begin(); backIt != this->backGrounds.end(); backIt++ )
	{
		for (i = 0, SpriteIt = backIt->second.begin(); SpriteIt != backIt->second.end(); SpriteIt++, i++)
		{
			SpriteIt->setPosition(0.f, 0.f);
			SpriteIt->move((backIt->first.getSize().x * this->size_coeff * i), 0.f);
		}
	}

	this->lastPosition = this->visionReference->getCenter();
};
void ParallaxBackground::SetBackgrounds(const std::vector<std::string>& paths)
{
	std::vector<std::string>::const_iterator cIt;
	std::vector<sf::Sprite>* pLastSpriteVec = nullptr;
	sf::Sprite* pLastSprite = nullptr;
	sf::Texture* pLastTexture = nullptr;
	sf::Texture txt;
	size_t i = 0;

	if (this->backGrounds.size() > 0)
		this->backGrounds.clear();

	/*
		Para cada path de textura para efeito parallax cria 2 objetos de 'Background' subsequentes em ordem na
		lista e em posição na tela, tal que, cada qual com o tamanho equilavente à 2 vezes a própria textura,
		efetivando o efeito de 4 texturas iguais em fila plotados na tela
	*/
	this->backGrounds.reserve(paths.size());
	for (cIt = paths.cbegin(); cIt != paths.cend(); cIt++)
	{
		txt.loadFromFile(*cIt);
		this->backGrounds.emplace_back(
			Background(sf::Texture(txt), std::vector<sf::Sprite>())
		);
		pLastTexture = &this->backGrounds.back().first;
		pLastSpriteVec = &this->backGrounds.back().second;

		pLastSpriteVec->reserve(NUM_BCKG_INSTANCES);
		for (i = 0; i < pLastSpriteVec->capacity(); i++)
		{
			pLastSpriteVec->emplace_back(sf::Sprite());
			pLastSprite = &pLastSpriteVec->back();

			pLastSprite->setTexture(this->backGrounds.back().first);
			pLastSprite->setScale(this->size_coeff, this->size_coeff);
			pLastSprite->move((pLastTexture->getSize().x * this->size_coeff * i), 0.f);
		}
	}

	this->layers_spd_proportion = 1.f / this->backGrounds.size();
	this->lastPosition = this->visionReference->getCenter();
};
unsigned int ParallaxBackground::GetBackgroundListSize()
{
	return this->backGrounds.size();
};