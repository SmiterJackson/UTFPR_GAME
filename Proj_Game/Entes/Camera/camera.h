#pragma once

#include "../Characters/Player/player.h"
#include "../../ListConteiner/lista.h"

/*
Classe definida para controlar a 'view' (escopo de visão dentro do jogo),
contendo ponteiro para os -players- no jogo, de tal modo que a view os 'segue'.
*/
class Camera : public Ente, public Trait::Collidable
{
public:
	Camera();
	Camera(const sf::Vector2f _center, const sf::Vector2f _size, float _zoom = 1.f,
		std::list<Characters::Player>* _pEntities = nullptr, sf::FloatRect* _mapBounds = nullptr,
		bool _lock_x = true, bool _lock_y = true, bool _bar_x = true, bool _bar_y = true);
	~Camera();

	const float const GetZoom() { return this->zoom; };
	void SetZoom(const float _zoom) { this->zoom = _zoom; };

	const sf::View* const GetView() { return &this->view; };

	void InvertLock_X() { this->lock_x = !this->lock_x; };
	void InvertLock_Y() { this->loack_y = !this->loack_y; };
	void InvertBar_X() { this->bar_x = !this->bar_x; };
	void InvertBar_Y() { this->bar_y = !this->bar_y; };

	const sf::FloatRect const GetBounds();

	const sf::Vector2f const GetPosition();
	void MovePosition(const sf::Vector2f _newPosition);
	void MovePosition(const float X_axis, const float Y_axis);

	const std::vector<Entity*> GetCameraEntities(const std::vector<Entity*>* entities);
	void WindowResized(const sf::RenderWindow& window);

	void AddPlayer(Characters::Player* pPlayer);
	void AddPlayerRange(std::list<Characters::Player*>* pPlayerList);
	void RemovePlayer(unsigned long long int id);

	void Execute(const float& pElapsedTime);

private:
	const sf::Vector2f originalSize;

	std::list<Characters::Player*> players;
	sf::View view;

	float zoom;

	bool lock_x, loack_y;
	bool bar_x, bar_y;
};