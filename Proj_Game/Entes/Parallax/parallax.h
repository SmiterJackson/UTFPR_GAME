#pragma once

#include "../Camera/camera.h"

typedef std::pair<sf::Texture, std::vector<sf::Sprite>> Background;

/*
Classe que define o fundo das fases, contendo um vetor de 'n' instâncias de uma mesma textura
em função de 'm' camadas (texturas), 'm' sendo o número de diretórios passados no vetor de string para texturas,
e 'n' definido no cpp desta classe, como um MACRO. Aplica efeito parallax de maneira automática em função da camera.
*/
class ParallaxBackground : public Ente, public Trait::BasePrintable
{
public:
	ParallaxBackground();
	ParallaxBackground(Camera* pCamera, const std::vector<std::string>& paths = std::vector<std::string>(), 
					   const float _size_coeff = 1.f);
	~ParallaxBackground();

	void SetBackgrounds(const std::vector<std::string>& paths);
	const unsigned int const GetBackgroundListSize() { return this->backGrounds.size(); };

	const float const GetSizeCoefficient() { return this->size_coeff; };
	void SetSizeCoefficient(float _size_coeff) 
	{ 
		std::vector<Background>::iterator it;
		size_t i = 0;
		this->size_coeff = _size_coeff; 

		for (it = this->backGrounds.begin(); it != this->backGrounds.end(); it++)
			for(i = 0; i < it->second.size(); i++)
				it->second[i].setScale(_size_coeff, _size_coeff);
	};
	
	void ResetPosition();

	void SelfPrint(sf::RenderWindow& context_window, const float& pElapsedTime);
	void Execute(const float& pElapsedTime);

private:
	std::vector<Background> backGrounds;

	Camera* camRef;
	sf::Vector2f lastPosition;

	float layers_spd_proportion;
	float size_coeff;
};