#pragma once

#include "../Entes/Ente/ente.h"

namespace GUI
{
	typedef std::pair<sf::Texture*, std::vector<sf::Sprite>> Layer;
	class Parallax : public Ente
	{
	public:
		Parallax(const std::vector<std::string>& paths = std::vector<std::string>(), const float _size_coeff = 1.f);
		~Parallax();

		void SetBackgrounds(const std::vector<std::string>& paths);
		void ResetBackground();

		const unsigned int GetBackgroundListSize() const { return this->backGrounds.size(); };

		void SetSizeCoefficient(float _size_coeff)
		{
			std::vector<Layer>::iterator it;
			size_t i = 0;
			this->size_coeff = _size_coeff;

			for (it = this->backGrounds.begin(); it != this->backGrounds.end(); it++)
				for (i = 0; i < it->second.size(); i++)
					it->second[i].setScale(_size_coeff, _size_coeff);
		};

		void SelfPrint();
		void Execute();

	private:
		std::vector<Layer> backGrounds;

		sf::Vector2f lastPosition;

		float layers_spd_coeff;
		float size_coeff;
	};
}