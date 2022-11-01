#pragma once

#include "../Managers/GraphicManager/graphic_manager.h"

namespace Trait
{
	class PrintableBody
	{
	public:
		PrintableBody(const std::string path = "", const sf::IntRect sheetCut = sf::IntRect(),
					  const float proportion = 1.0f);
		virtual ~PrintableBody();

		const sf::Vector2u GetTextureSize() const { return this->texture->getSize(); };
		void SetTexture(const std::string path, const sf::IntRect sheetCut = sf::IntRect(0, 0, 0, 0));

		const sf::Vector2f GetTexturePosition() const { return this->body.getPosition(); };
		void SetTexturePosition(const sf::Vector2f _pos) { this->body.setPosition(_pos); };
		void SetTexturePosition(const float X_axis, const float Y_axis) { this->body.setPosition(X_axis, Y_axis); };
		void SetTextureProportion(float proportion) { this->body.setScale(proportion, proportion); };

	protected:
		sf::Texture* texture;
		sf::Sprite body;
	};
}