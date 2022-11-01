#include "button.h"

#define PROPORTION 8.0f

GUI::Button::Button():
	Ente(Type::BUTTON, PrintPriority::buttons),
	button_status(BUTTON_STATUS::BTN_IDLE),
	body(), font(), text(),
	textColor_idle(), textColor_hover(),
	bodyColor_idle(), bodyColor_hover(),
	pMouse(nullptr)
{};
GUI::Button::Button(const sf::Vector2f _size, const sf::Vector2f _position, sf::Font* _font,
					const std::string _text_data, const unsigned int _char_size, Mouse* _pMouse,
					sf::Color _textColor_idle, sf::Color _textColor_hover,
					sf::Color _bodyColor_idle, sf::Color _bodyColor_hover) :
	Ente(Type::BUTTON, PrintPriority::buttons),
	button_status(BUTTON_STATUS::BTN_IDLE), 
	body(_size),
	font(_font), text(),
	textColor_idle(_textColor_idle), textColor_hover(_textColor_hover),
	bodyColor_idle(_bodyColor_idle), bodyColor_hover(_bodyColor_hover), 
	pMouse(_pMouse)
{
	this->body.setOrigin(this->body.getSize() / 2.f);
	this->body.setPosition(_position);
	this->body.setFillColor(this->bodyColor_idle);

	this->text.setString(_text_data);
	this->text.setStyle(sf::Text::Bold);
	this->text.setFillColor(this->textColor_idle);
	this->text.setCharacterSize(_char_size);
	this->text.setPosition(
		_position.x - this->text.getGlobalBounds().width / 2.f,
		_position.y - this->text.getGlobalBounds().height / 2.f
	);

	if(this->font != nullptr)
		this->text.setFont(*this->font);
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

void GUI::Button::SelfPrint(sf::RenderWindow& context_window, const float& pElapsedTime)
{
	context_window.draw(this->body);
	context_window.draw(this->text);
};
void GUI::Button::Execute(const float& pElapsedTime)
{
	if (this->pMouse != nullptr)
	{
		this->button_status = BTN_IDLE;

		if (this->body.getGlobalBounds().contains(this->pMouse->GetMouseToView()))
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
	}
};

bool GUI::Button::IsClicked()
{
	bool contain(this->body.getGlobalBounds().contains(this->pMouse->GetMouseToView()));

	if (contain && this->button_status == BUTTON_STATUS::BTN_HOVER)
		return true;

	return false;
};