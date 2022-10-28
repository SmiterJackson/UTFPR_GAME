#include "printable.h"

Trait::Printable::Printable():
	BasePrintable(), texture(), body()
{
	this->body.setTexture(this->texture);
	this->body.setPosition(0.f, 0.f);
};
Trait::Printable::Printable(const unsigned short int printPriority, const std::string textureRef,
							const sf::IntRect sheetCut, const float proportion) :
	BasePrintable(printPriority), texture(), body()
{
	this->texture.loadFromFile(textureRef);
	this->texture.setRepeated(false);

	this->body.setTexture(this->texture);
	this->body.setScale(proportion, proportion);
	
	if (sheetCut.left != sheetCut.width && sheetCut.top != sheetCut.height)
	{
		this->body.setTextureRect(sheetCut);
		this->body.setOrigin(
			sheetCut.width / 2.f,
			sheetCut.height / 2.f
		);
	}
	else
	{
		this->body.setOrigin(
			this->texture.getSize().x / 2.f,
			this->texture.getSize().y / 2.f
		);
	}

	this->body.setPosition(0.f, 0.f);
};
Trait::Printable::~Printable()
{
	
};

void Trait::Printable::SetTexture(const std::string _texturePath, const sf::IntRect _rectCut)
{
	if (!_texturePath.empty())
	{
		this->texture.loadFromFile(_texturePath);

		if (_rectCut.left != _rectCut.width && _rectCut.top != _rectCut.height)
		{
			this->body.setTextureRect(_rectCut);
			this->body.setOrigin(_rectCut.width / 2.f, _rectCut.height / 2.f);
		}
		else
		{
			this->body.setOrigin(
				this->texture.getSize().x / 2.f,
				this->texture.getSize().y / 2.f
			);
		}
	}
};