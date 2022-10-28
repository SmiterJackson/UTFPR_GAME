#pragma once

#include "../../Entities/Mouse/mouse.h"

namespace GUI
{
	class Button : public Ente
	{
	public:
		Button();
		Button(sf::View* view, const sf::Vector2f _position, const std::string fontPath,
			   const std::string _text_data, const unsigned _character_size, Mouse* _pMouse,
			   sf::Color _textColor_idle, sf::Color _textColor_hover,
			   sf::Color _bodyColor_idle, sf::Color _bodyColor_hover);
		~Button();

		bool IsClicked();

		void SetPosition(const sf::Vector2f position);
		void SetPosition(const float x, const float y);

		const std::string GetText() { return this->text.getString(); };
		void SetText(const std::string _text_data) { this->text.setString(_text_data); };

		void Execute();
		void SelfPrint(sf::RenderWindow& context_window);

	public:
		enum BUTTON_STATUS { BTN_IDLE = 0, BTN_HOVER };

	protected:
		short unsigned button_status;

		sf::RectangleShape body;

		sf::Font font;
		sf::Text text;

		sf::Color textColor_idle, textColor_hover;
		sf::Color bodyColor_idle, bodyColor_hover;

		Mouse* pMouse;
	};
}