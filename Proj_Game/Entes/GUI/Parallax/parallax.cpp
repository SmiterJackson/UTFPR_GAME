#include "parallax.h"
#include "../Managers/GraphicManager/graphic_manager.h"
using namespace Manager;
using namespace GUI;

#define NUM_BCKG_INSTANCES 3U

Parallax::Parallax(const std::vector<std::string>& paths, const float _size_coeff) :
	Ente(Type::BACKGROUND, PrintPriority::background),
	backGrounds(),
	lastPosition(0.f, 0.f), layers_spd_coeff(1.f), size_coeff(_size_coeff)
{
	this->SetBackgrounds(paths);
};
Parallax::~Parallax()
{};

void Parallax::SetBackgrounds(const std::vector<std::string>& paths)
{
	std::vector<std::string>::const_iterator cIt;
	std::vector<sf::Sprite>* pLastSpriteVec = nullptr;
	sf::Sprite* pLastSprite = nullptr;
	sf::Texture* txt = nullptr;
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
		txt = GraphicManager::LoadTexture(*cIt);
		this->backGrounds.emplace_back(Layer(txt, std::vector<sf::Sprite>()));
		pLastSpriteVec = &this->backGrounds.back().second;

		pLastSpriteVec->reserve(NUM_BCKG_INSTANCES);
		for (i = 0; i < NUM_BCKG_INSTANCES; i++)
		{
			pLastSpriteVec->emplace_back(sf::Sprite());
			pLastSprite = &pLastSpriteVec->back();

			pLastSprite->setTexture(*txt);
			pLastSprite->setPosition(0.f, 0.f);
			pLastSprite->setScale(this->size_coeff, this->size_coeff);
			pLastSprite->move((txt->getSize().x * this->size_coeff * i), 0.f);
		}
	}

	this->layers_spd_coeff = 1.f / this->backGrounds.size();
	this->lastPosition = GraphicManager::GetViewPosition();
};
void Parallax::ResetBackground()
{
	std::vector<Layer>::iterator layer;
	std::vector<sf::Sprite>::iterator SpriteIt;
	unsigned int i = 0;

	for (layer = this->backGrounds.begin(); layer != this->backGrounds.end(); layer++)
	{
		for (i = 0, SpriteIt = layer->second.begin(); SpriteIt != layer->second.end(); SpriteIt++, i++)
		{
			SpriteIt->setPosition(0.f, 0.f);
			SpriteIt->move((layer->first->getSize().x * this->size_coeff * i), 0.f);
		}
	}

	this->lastPosition = GraphicManager::GetViewPosition();
};

void Parallax::SelfPrint()
{
	std::vector<Layer>::reverse_iterator rIt;
	size_t i = 0;

	for (rIt = this->backGrounds.rbegin(); rIt != this->backGrounds.rend(); rIt++)
		for (i = 0; i < rIt->second.size(); i++)
			GraphicManager::Draw(rIt->second[i]);
};
void Parallax::Execute()
{
	std::vector<Layer>::iterator it;
	sf::Sprite* pSprite = nullptr;
	sf::Vector2f diff, movement;
	float leastLim = 0.f, maxLim = 0.f, counter = 1.f;
	unsigned int i = 0;

	diff = this->lastPosition - GraphicManager::GetViewPosition();
	leastLim = GraphicManager::GetViewPosition().x - GraphicManager::GetViewSize().x;
	maxLim = GraphicManager::GetViewPosition().x + GraphicManager::GetViewSize().x;
	this->lastPosition = GraphicManager::GetViewPosition();

	/*
		Para a quantidade de "layers", camadas, de backgrounds em função do número de cópias/instancias,
		move cada camada proporcinalmente a sua respectiva velocidade dado pela "posição da camada"
	*/
	if (diff.x != 0.f || diff.y != 0.f)
	{
		for (it = this->backGrounds.begin(), counter = 0;
			it != this->backGrounds.end();
			counter++, it++)
		{
			movement = diff * (-layers_spd_coeff * counter);

			for (i = 0; i < it->second.size(); i++)
			{
				pSprite = &it->second[i];

				pSprite->move(movement);

				if (pSprite->getPosition().x + pSprite->getGlobalBounds().width < leastLim)
					pSprite->move((pSprite->getGlobalBounds().width * NUM_BCKG_INSTANCES), 0.f);

				else if (pSprite->getPosition().x > maxLim)
					pSprite->move(-(pSprite->getGlobalBounds().width * NUM_BCKG_INSTANCES), 0.f);
			}
		}
	}
};
