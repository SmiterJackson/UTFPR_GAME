#pragma once

#include "../../Entes/Mouse/mouse.h"

const enum BUTTON_STATUS 
{
	BTN_IDLE = 0, 
	BTN_HOVER 
};

namespace GUI
{
	class Button : public Ente
	{
	public:
		Button();
		Button(const sf::Vector2f _size, const sf::Vector2f _position, sf::Font* _font,
			   const std::string _text_data, const unsigned _char_size, Mouse* _pMouse,
			   sf::Color _textColor_idle, sf::Color _textColor_hover,
			   sf::Color _bodyColor_idle, sf::Color _bodyColor_hover);
		~Button();

		void SetPosition(const sf::Vector2f position);
		void SetPosition(const float x, const float y);

		void SetText(const std::string _text_data) { this->text.setString(_text_data); };

		void SelfPrint(sf::RenderWindow& context_window, const float& pElapsedTime);
		void Execute(const float& pElapsedTime);

		bool IsClicked();

	protected:
		short unsigned button_status;

		sf::RectangleShape body;

		sf::Font* font;
		sf::Text text;

		sf::Color textColor_idle, textColor_hover;
		sf::Color bodyColor_idle, bodyColor_hover;

		Mouse* pMouse;
	};
}