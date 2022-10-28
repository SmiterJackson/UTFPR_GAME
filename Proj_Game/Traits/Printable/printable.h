#pragma once

#include "../BasePrintable/basePrintable.h"

namespace Trait
{
	class Printable : public BasePrintable
	{
	public:
		Printable();
		Printable(const unsigned short int printPriority, const std::string textureRef = "",
				  const sf::IntRect sheetCut = sf::IntRect(), const float proportion = 1.0f);
		virtual ~Printable();

		const sf::Vector2u const GetTextureSize() { return this->texture.getSize(); };
		void SetTexture(const std::string _texturePath, const sf::IntRect _rectCut = sf::IntRect(0, 0, 0, 0));

		const sf::Vector2f const  GetTexturePosition() { return this->body.getPosition(); };
		void SetTexturePosition(const sf::Vector2f _pos) { this->body.setPosition(_pos); };
		void SetTexturePosition(const float X_axis, const float Y_axis) { this->body.setPosition(X_axis, Y_axis); };
		void SetTextureProportion(float proportion) { this->body.setScale(proportion, proportion); };

		virtual void SelfPrint(sf::RenderWindow& context_window, const float& pElapsedTime) = 0;

	protected:
		sf::Texture texture;
		sf::Sprite body;
	};
}