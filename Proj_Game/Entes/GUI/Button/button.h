#pragma once

#include "../Entes/Ente/ente.h"

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
		Button(const sf::Vector2f _size, const sf::Vector2f _position,
			   const std::string _text_data, const unsigned int _char_size,
			   sf::Color _textColor_idle, sf::Color _textColor_hover,
			   sf::Color _bodyColor_idle, sf::Color _bodyColor_hover);
		~Button();

		void SetPosition(const sf::Vector2f position);
		void SetPosition(const float x, const float y);

		void SetText(const std::string _text_data);
		const std::string GetText() { return this->text.getString(); };

		void SelfPrint();
		void Execute();

		bool IsClicked();

	protected:
		short unsigned button_status;

		sf::RectangleShape body;
		sf::Text text;

		sf::Color textColor_idle, textColor_hover;
		sf::Color bodyColor_idle, bodyColor_hover;
	};
}