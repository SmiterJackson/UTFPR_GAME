#include "button.h"
#include "../Managers/GraphicManager/graphic_manager.h"
using namespace Manager;

#define PROPORTION 8.0f

GUI::Button::Button():
	Ente(Type::BUTTON, PrintPriority::buttons),
	button_status(BUTTON_STATUS::BTN_IDLE),
	body(), text(),
	textColor_idle(), textColor_hover(),
	bodyColor_idle(), bodyColor_hover()
{};
GUI::Button::Button(const sf::Vector2f _size, const sf::Vector2f _position, sf::Font* _font,
					const std::string _text_data, const unsigned int _char_size,
					sf::Color _textColor_idle, sf::Color _textColor_hover,
					sf::Color _bodyColor_idle, sf::Color _bodyColor_hover) :
	Ente(Type::BUTTON, PrintPriority::buttons),
	button_status(BUTTON_STATUS::BTN_IDLE), 
	body(_size), text(),
	textColor_idle(_textColor_idle), textColor_hover(_textColor_hover),
	bodyColor_idle(_bodyColor_idle), bodyColor_hover(_bodyColor_hover)
{
	sf::FloatRect textBounds;
	sf::Vector2f midpoint;

	this->body.setOrigin(this->body.getSize() / 2.f);
	this->body.setPosition(_position);
	this->body.setFillColor(this->bodyColor_idle);

	if (_font != nullptr)
		this->text.setFont(*_font);
	this->text.setString(_text_data);
	this->text.setStyle(sf::Text::Bold);
	this->text.setFillColor(this->textColor_idle);
	this->text.setCharacterSize(_char_size);

	textBounds = this->text.getLocalBounds();
	midpoint = sf::Vector2f(
		textBounds.width	- textBounds.left,
		textBounds.height	- textBounds.top	+ _char_size
	);

	this->text.setOrigin(midpoint / 2.f);
	this->text.setPosition(_position);
};
GUI::Button::~Button()
{};

void GUI::Button::SetPosition(const sf::Vector2f position)
{
	this->body.setPosition(position);
	this->text.setPosition(position);
};
void GUI::Button::SetPosition(const float x, const float y)
{
	this->body.setPosition(x, y);
	this->text.setPosition(x, y);
};

void GUI::Button::SetText(const std::string _text_data)
{
	sf::FloatRect textBounds;
	sf::Vector2f midpoint;
	sf::Vector2f pos;

	pos = this->text.getPosition();

	this->text.setString(_text_data);
	textBounds = this->text.getLocalBounds();
	midpoint = sf::Vector2f(
		textBounds.width - textBounds.left,
		textBounds.height - textBounds.top + this->text.getCharacterSize()
	);

	this->text.setOrigin(midpoint / 2.f);
	this->text.setPosition(pos);
};

void GUI::Button::SelfPrint(const float& pElapsedTime)
{
	GraphicManager::Draw(this->body);
	GraphicManager::Draw(this->text);
};
void GUI::Button::Execute(const float& pElapsedTime)
{

	this->button_status = BTN_IDLE;

	if (this->body.getGlobalBounds().contains(GraphicManager::MouseToView()))
		this->button_status = BTN_HOVER;

	switch (this->button_status)
	{
	case BTN_IDLE:
		this->body.setFillColor(this->bodyColor_idle);
		this->text.setFillColor(this->textColor_idle);
		break;
	case BTN_HOVER:
		this->body.setFillColor(this->bodyColor_hover);
		this->text.setFillColor(this->textColor_hover);
		break;
	default:
		break;
	}
};

bool GUI::Button::IsClicked()
{
	bool contain(this->body.getGlobalBounds().contains(GraphicManager::MouseToView()));

	if (contain && this->button_status == BUTTON_STATUS::BTN_HOVER)
		return true;

	return false;
};