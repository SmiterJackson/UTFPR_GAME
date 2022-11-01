#pragma once

#include "../GUI/Interfaces/Interface/interface.h"
#include "../ColisionManager/colisionManager.h"
#include "../Entes/Stage/stage.h"

namespace Manager
{
	typedef std::unordered_map<unsigned short int, GUI::Interface*> InterfaceMap;
	typedef std::unordered_map<std::string, sf::Texture*> TextureMap;

	const enum PrintPriority
	{
		undefined = 0,
		background,
		obstacles,
		characters,
		projectiles,
		interfaces,
		buttons
	};

	class GraphicManager
	{
	public:
		static const GraphicManager* GetGraphicInstance(float& _elapsedTimeRef);
		static void DesconstructGraphicInstance();

		void SetCameraLimits(const sf::FloatRect limits) { this->cameraLim = limits; };

		const float GetZoom() const { return this->zoom; };
		void SetZoom(const float _zoom) { this->zoom = _zoom; };

		static const sf::FloatRect GetViewBounds();
		static const sf::View* const GetView() { return &view; };

		static void UpdateCamera();
		void InvertDistortion_X();
		void InvertDistortion_Y();
		void InvertBar_X();
		void InvertBar_Y();
		void WindowResize();

		static const ColisonVector GetCameraEntities(const ColisonVector& entities);
		static const sf::Font* GetFont();

		static sf::Texture* LoadTexture(std::string texturePath);
		static void Draw(const float& pElapsedTime);

	private:
		GraphicManager(float& _elapsedTimeRef);
		~GraphicManager();

	private:
		static GraphicManager* instance;
		static InterfaceMap* pInterfaces;
		static unsigned short int* pGameState;
		static sf::Font* font;
		static TextureMap textures;
		static sf::View view;
		static sf::RenderWindow window;

		Stage::Parallax* parallax;
		const sf::Vector2f originalSize;
		sf::FloatRect cameraLim;

		float zoom;
		float& elapsedTimeRef;

		bool lock_x, lock_y;
		bool bar_x, bar_y;
	};
}