#include "printableBody.h"
#include "../Managers/GraphicManager/graphic_manager.h"
using namespace Manager;
using namespace Trait;

PrintableBody::PrintableBody(const std::string path, const sf::IntRect sheetCut, const float proportion):
	texture(nullptr), body()
{
	if(!path.empty())
		this->texture = GraphicManager::LoadTexture(path, sheetCut);

	this->body.setScale(proportion, proportion);

	if(this->texture != nullptr)
	{
		this->body.setTexture(*this->texture);
		this->texture->setRepeated(false);

		this->body.setOrigin(
			this->texture->getSize().x / 2.f,
			this->texture->getSize().y / 2.f
		);
	}

	this->body.setPosition(0.f, 0.f);
};
PrintableBody::~PrintableBody()
{};

void PrintableBody::SetTexture(const std::string path, const sf::IntRect sheetCut)
{
	if (!path.empty())
	{
		this->texture = GraphicManager::LoadTexture(path);

		this->body.setTexture(*this->texture);
		this->texture->setRepeated(false);

		this->body.setOrigin(
			this->texture->getSize().x / 2.f,
			this->texture->getSize().y / 2.f
		);
	}
};