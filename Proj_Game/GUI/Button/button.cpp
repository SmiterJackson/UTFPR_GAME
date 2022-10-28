#include "button.h"

#define PROPORTION 8.0f

GUI::Button::Button():
	Ente(Ente::Type::BUTTON, nullptr), button_status(BUTTON_STATUS::BTN_IDLE), 
	body(), font(), text(),
	textColor_idle(), textColor_hover(),
	bodyColor_idle(), bodyColor_hover(),
	pMouse(nullptr)
{};
GUI::Button::Button(sf::View* view, const sf::Vector2f _position, const std::string fontPath,
					const std::string _text_data, const unsigned _character_size, Mouse* _pMouse,
					sf::Color _textColor_idle, sf::Color _textColor_hover,
					sf::Color _bodyColor_idle, sf::Color _bodyColor_hover) :
	Ente(Ente::Type::BUTTON, nullptr), button_status(BUTTON_STATUS::BTN_IDLE), 
	body(sf::Vector2f(view->getSize().x / PROPORTION, view->getSize().y / PROPORTION)), font(), text(),
	textColor_idle(_textColor_idle), textColor_hover(_textColor_hover),
	bodyColor_idle(_bodyColor_idle), bodyColor_hover(_bodyColor_hover), 
	pMouse(_pMouse)
{
	this->font.loadFromFile(fontPath);

	this->body.setOrigin(this->body.getSize() / 2.f);
	this->body.setPosition(_position);
	this->body.setFillColor(this->bodyColor_idle);

	this->text.setFont(this->font);
	this->text.setString(_text_data);
	this->text.setStyle(sf::Text::Bold);
	this->text.setFillColor(this->textColor_idle);
	this->text.setCharacterSize(_character_size);
	this->text.setPosition(
		_position.x - this->text.getGlobalBounds().width / 2.f,
		_position.y - this->text.getGlobalBounds().height / 2.f
	);
};
GUI::Button::~Button()
{};

bool GUI::Button::IsClicked()
{
	return this->body.getGlobalBounds().contains(this->pMouse->GetMouseToView());
};

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

void GUI::Button::Execute()
{
	if(this->pMouse != nullptr)
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
void GUI::Button::SelfPrint(sf::RenderWindow& context_window)
{
	context_window.draw(this->body);
	context_window.draw(this->text);
};