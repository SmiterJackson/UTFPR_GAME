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

		static const sf::FloatRect GetViewBounds();
		static const sf::View* const GetView() { return &view; };

		static const bool IsWindowOpen() { return window->isOpen(); };
		static sf::RenderWindow& GetWindow() { return *window; };

		void InvertDistortion_X();
		void InvertDistortion_Y();
		void InvertBar_X();
		void InvertBar_Y();

		static void UpdateCamera();
		void WindowResize();

		static const ColisonVector GetCameraEntities(const ColisonVector& entities);
		static sf::Font* GetFont() { return font; };

		static sf::Texture* LoadTexture(std::string texturePath);
		void Draw();

	private:
		GraphicManager(float& _elapsedTimeRef, Interfaces* _pInterfaces);
		~GraphicManager();

	private:
		static GraphicManager* instance;
		static sf::RenderWindow* window;
		static Interfaces* pInterfaces;
		static unsigned short int* pGameState;
		static sf::Font* font;
		static TextureMap textures;
		static sf::View view;
		static sf::FloatRect cameraLim;

		const sf::Vector2f originalSize;

		float zoom;
		float& elapsedTimeRef;

		bool lock_x, lock_y;
		bool bar_x, bar_y;
	};
}