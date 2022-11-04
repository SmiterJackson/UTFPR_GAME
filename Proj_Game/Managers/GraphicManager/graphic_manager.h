#pragma once

#include "../Entes/Stage/stage.h"

namespace Manager
{
	typedef std::stack<GUI::Interface*> Interfaces;
	typedef std::unordered_map<std::string, sf::Texture*> TextureMap;

	class GraphicManager
	{
	public:
		static GraphicManager* GetGraphicInstance(float& _elapsedTimeRef, Interfaces* _pInterfaces);
		static void DesconstructGraphicInstance();

		static void SetCameraLimits(const sf::FloatRect limits) { cameraLim = limits; };

		const float GetZoom() const { return this->zoom; };
		void SetZoom(const float _zoom) { this->zoom = _zoom; };

		static const sf::FloatRect GetViewBounds() 
		{
			return sf::FloatRect(
				view.getCenter().x - (view.getSize().x / 2.f),
				view.getCenter().y - (view.getSize().y / 2.f),
				view.getCenter().x + (view.getSize().x / 2.f),
				view.getCenter().y + (view.getSize().y / 2.f)
			);
		};
		static const sf::View* const GetView() { return &view; };

		static const bool IsWindowOpen() { return window->isOpen(); };
		static sf::RenderWindow& GetWindow() { return *window; };

		static const sf::Vector2f MouseToDesktop()
		{
			return static_cast<sf::Vector2f>(sf::Mouse::getPosition());
		};
		static const sf::Vector2f MouseToWindow()
		{
			return static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window));
		};
		static const sf::Vector2f MouseToView()
		{
			return window->mapPixelToCoords(sf::Mouse::getPosition(*window));
		};
		static const sf::Vector2i MouseToGrid()
		{
			sf::Vector2f mousToView = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
			return sf::Vector2i(mousToView / gridSize);
		};

		void InvertDistortion_X()
		{
			this->lock_x = !this->lock_x;
			if (!this->lock_x && this->bar_x)
				this->bar_x = false;
		};
		void InvertDistortion_Y()
		{
			this->lock_y = !this->lock_y;
			if (!this->lock_y && this->bar_y)
				this->bar_y = false;
		};
		void InvertBar_X()
		{
			this->bar_x = !this->bar_x;
			if (this->bar_x && !this->lock_x)
				this->lock_x = true;
		};
		void InvertBar_Y()
		{
			this->bar_y = !this->bar_y;
			if (this->bar_y && !this->lock_y)
				this->lock_y = true;
		};

		static void UpdateCamera();
		void WindowResize();

		static void Draw(const sf::RectangleShape& drawTarget);
		static void Draw(const sf::CircleShape& drawTarget);
		static void Draw(const sf::Sprite& drawTarget);
		static void Draw(const sf::Text& drawTarget);

		static const ColisonVector GetCameraEntities(const ColisonVector& entities);
		static sf::Font* GetFont() { return font; };

		static sf::Texture* LoadTexture(std::string texturePath);
		void Update();

	private:
		GraphicManager(float& _elapsedTimeRef, Interfaces* _pInterfaces);
		~GraphicManager();

	private:
		static float gridSize;
		static sf::Font* font;
		static GraphicManager* instance;
		static sf::RenderWindow* window;
		static sf::FloatRect cameraLim;
		static TextureMap textures;
		static sf::View view;

		const sf::Vector2f originalSize;
		Interfaces* pInterfaces;

		float zoom;
		float& elapsedTimeRef;

		bool lock_x, lock_y;
		bool bar_x, bar_y;
	};
}