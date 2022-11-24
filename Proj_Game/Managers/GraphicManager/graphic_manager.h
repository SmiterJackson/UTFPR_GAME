#pragma once

#include "../Entes/GUI/Interfaces/Stage/stage.h"

namespace Manager
{
	typedef std::stack<GUI::Interface*> Interfaces;
	typedef std::unordered_map<std::string, sf::Texture*> TextureMap;

	class GraphicManager
	{
	public:
		static GraphicManager* GetInstance(Interfaces* _pInterfaces = nullptr);
		static void DesconstructInstance();

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
		static const sf::Vector2f GetViewPosition()
		{
			return view.getCenter();
		};
		static const sf::Vector2f GetViewSize()
		{
			return view.getSize();
		};

		static const bool IsWindowOpen() { return window->isOpen(); };
		static void CloseWindow() { window->close(); };
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
		static const sf::Vector2i PositionToGrid(const sf::Vector2f pos)
		{
			return static_cast<sf::Vector2i>(pos / gridSize);
		};
		static const sf::IntRect CameraGridIndexs()
		{
			sf::FloatRect bounds(GraphicManager::GetViewBounds());
			sf::IntRect indexs(
				int(bounds.left		/ gridSize),
				int(bounds.top		/ gridSize),
				int(bounds.width	/ gridSize),
				int(bounds.height	/ gridSize)
			);

			return indexs;
		};
		static const float GetGridSize() { return gridSize; };

		void SetResizeDistortion(const bool X_axis, const bool Y_axis)
		{
			this->distort_x = X_axis;
			if (!this->distort_x && this->bar_x)
				this->bar_x = false;

			this->distort_y = Y_axis;
			if (!this->distort_y && this->bar_y)
				this->bar_y = false;
		};
		void SetResizeBar(const bool X_axis, const bool Y_axis)
		{
			this->bar_x = X_axis;
			if (this->bar_x && !this->distort_x)
				this->distort_x = true;

			this->bar_y = Y_axis;
			if (this->bar_y && !this->distort_y)
				this->distort_y = true;
		};

		static void UpdateCamera();
		void WindowResize() const;

		static void Draw(const sf::RectangleShape& drawTarget);
		static void Draw(const sf::CircleShape& drawTarget);
		static void Draw(const sf::Sprite& drawTarget);
		static void Draw(const sf::Text& drawTarget);

		static const Entities GetCameraEntities(const Entities& entities);
		
		static sf::Font* GetFont() { return font; };
		static sf::Texture* LoadTexture(std::string texturePath, sf::IntRect sheetCut = sf::IntRect(0,0,0,0));
		
		void Update();

	private:
		GraphicManager(Interfaces* _pInterfaces = nullptr);
		~GraphicManager();

	private:
		static const float camExtraSpace;
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
		bool distort_x, distort_y;
		bool bar_x, bar_y;
	};
}