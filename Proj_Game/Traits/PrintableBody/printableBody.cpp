#include "printableBody.h"

#include "../Managers/GraphicManager/graphic_manager.h"

Trait::PrintableBody::PrintableBody(const std::string path, const sf::IntRect sheetCut, const float proportion):
	texture(nullptr), body()
{
	this->texture = Manager::GraphicManager::LoadTexture(path);

	this->body.setScale(proportion, proportion);

	if(this->texture != nullptr)
	{
		this->body.setTexture(*this->texture);
		this->texture->setRepeated(false);

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
				this->texture->getSize().x / 2.f,
				this->texture->getSize().y / 2.f
			);
		}
	}

	this->body.setPosition(0.f, 0.f);
};
Trait::PrintableBody::~PrintableBody()
{};

void Trait::PrintableBody::SetTexture(const std::string path, const sf::IntRect sheetCut)
{
	if (!path.empty())
	{
		this->texture = Manager::GraphicManager::LoadTexture(path);

		this->body.setTexture(*this->texture);
		this->texture->setRepeated(false);

		if (sheetCut.left != sheetCut.width && sheetCut.top != sheetCut.height)
		{
			this->body.setTextureRect(sheetCut);
			this->body.setOrigin(sheetCut.width / 2.f, sheetCut.height / 2.f);
		}
		else
		{
			this->body.setOrigin(
				this->texture->getSize().x / 2.f,
				this->texture->getSize().y / 2.f
			);
		}
	}
};