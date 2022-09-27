#include "player.h"
#include "../Camera/camera.h"
#include "../StageClass/stage.h"

#define P1_TEXTURE_REF "Resources/characters/player/sheets/DinoSprites_mort.png"
#define P2_TEXTURE_REF "Resources/characters/player/sheets/DinoSprites_vita.png"

#define TEXTURE_TOKEN_SIZE 24

#define INVENCIBILITY_FRAMES_TIME 2.5f

#define H_ACCELERATION 0.6f
#define H_MAX_ACCELERATION 0.3f

#define JUMP -0.5f
#define V_ACCELERATION 1.f
#define V_MAX_ACCELERATION 0.75f

#define PLAYER_TOTAL_LIFE 10U

unsigned int Characters::Player::playerCounter = 0;

Characters::Player::Player():
	Character(
		Type::CHARACTER, nullptr, sf::RectangleShape(sf::Vector2f(0.f, 0.f)), std::string(),
		sf::IntRect(0, 0, TEXTURE_TOKEN_SIZE, TEXTURE_TOKEN_SIZE), AnimationSheet(), PLAYER_TOTAL_LIFE, INVENCIBILITY_FRAMES_TIME
	),
	onGround(true), crouching(false), jump(false), walkLeft(false), walkRight(false), walking(true), done(false), playerId(playerCounter)
{
	Initialize();
};
Characters::Player::Player(float* elapsed_timeRef) :
	Character(
		Type::CHARACTER, elapsed_timeRef, sf::RectangleShape(sf::Vector2f(18.f, 18.f)), std::string(),
		sf::IntRect(0, 0, TEXTURE_TOKEN_SIZE, TEXTURE_TOKEN_SIZE), AnimationSheet(), PLAYER_TOTAL_LIFE, INVENCIBILITY_FRAMES_TIME
	),
	onGround(true), crouching(false), jump(false), walkLeft(false), walkRight(false), walking(true), done(false), playerId(playerCounter)
{
	Initialize();
};
Characters::Player::~Player()
{
	playerCounter--;
};

void Characters::Player::Execute()
{
	float coeff = H_ACCELERATION * (*this->elapsedTime);

	if (this->walking)
	{
		if (this->jump && this->onGround && !this->crouching)
		{
			this->onGround = false;
			this->speedV = JUMP;
			coeff /= 10;
		}

		if ((this->walkLeft && !this->walkRight) || (!this->walkLeft && this->walkRight))
		{
			if (!this->crouching)
				this->next_ani = Actions::WALKING;
			else
			{
				this->next_ani = Actions::CROUCHING;
				coeff /= 2.f;
			}

			if (this->walkRight && this->speedH < H_MAX_ACCELERATION)
				this->speedH += coeff;

			if (this->walkLeft && this->speedH > -H_MAX_ACCELERATION)
				this->speedH -= coeff;
		}
		else
		{
			this->next_ani = Actions::IDLE;

			if (this->speedH < 0.f)
				this->speedH += coeff;

			if (this->speedH > 0.f)
				this->speedH -= coeff;

			if (this->speedH <= 0.1f && this->speedH >= -0.1f)
				this->speedH = 0.f;
		}

		if (!this->onGround)
		{
			if (this->speedV < V_MAX_ACCELERATION)
				this->speedV += V_ACCELERATION * (*this->elapsedTime);
		}
		else
		{
			this->speedV = 0.001f;
			this->onGround = false;
		}
	}
	else
	{
		if ((this->walkLeft && !this->walkRight) || (!this->walkLeft && this->walkRight))
		{
			if (this->walkRight && this->speedH < H_MAX_ACCELERATION)
				this->speedH += coeff;

			if (this->walkLeft && this->speedH > -H_MAX_ACCELERATION)
				this->speedH -= coeff;
		}
		else
		{
			if (this->speedH < 0.f)
				this->speedH += coeff;

			if (this->speedH > 0.f)
				this->speedH -= coeff;

			if (this->speedH <= 0.1f && this->speedH >= -0.1f)
				this->speedH = 0.f;
		}
		if ((this->jump && !this->crouching) || (!this->jump && this->crouching))
		{
			if (this->jump && this->speedV < H_MAX_ACCELERATION)
				this->speedV -= coeff;

			if (this->crouching && this->speedV > -H_MAX_ACCELERATION)
				this->speedV += coeff;
		}
		else
		{
			if (this->speedV < 0.f)
				this->speedV += coeff;

			if (this->speedV > 0.f)
				this->speedV -= coeff;

			if (this->speedV <= 0.1f && this->speedV >= -0.1f)
				this->speedV = 0.f;
		}
	}

	this->MovePosition(sf::Vector2f(speedH, speedV));
};
void Characters::Player::Collided(Ente* _other)
{
	switch (_other->GetType())
	{
	case Type::CAMERA:
		this->CameraCollision(static_cast<Camera*>(_other));
		break;
	case Type::STAGE:
		this->StageCollision(static_cast<Stage*>(_other));
		break;
	case Type::OBSTACLE:
		this->ObstacleCollision(static_cast<Entity*>(_other));
		break;
	case Type::PROJECTILE:
		break;
	case Type::ENEMY:
		break;
	default:
		break;
	}
};
void Characters::Player::SelfPrint(sf::RenderWindow& context_window)
{
	this->UpdateAnimation(this->elapsedTime);
	context_window.draw(this->body);

#ifdef _DEBUG
	this->hitBox.setOutlineColor(sf::Color::Red);
	this->hitBox.setOutlineThickness(1.5f);
	context_window.draw(this->hitBox);
#endif
};

void Characters::Player::PlayerInputHandler(const sf::Event& _event)
{
	if (_event.type == sf::Event::KeyPressed)
	{
		switch (_event.key.code)
		{
		case sf::Keyboard::D:
			if (this->playerId == 0)
			{
				this->walkRight = true;
				this->looking_right = true;
			}
			break;
		case sf::Keyboard::A:
			if (this->playerId == 0)
			{
				this->walkLeft = true;
				this->looking_right = false;
			}
			break;
		case sf::Keyboard::W:
			if (this->playerId == 0)
				this->jump = true;
			break;
		case sf::Keyboard::S:
			if (this->playerId == 0)
				this->crouching = true;
			break;
		case sf::Keyboard::Right:
			if (this->playerId == 1)
			{
				this->walkRight = true;
				this->looking_right = true;
			}
			break;
		case sf::Keyboard::Left:
			if (this->playerId == 1)
			{
				this->walkLeft = true;
				this->looking_right = false;
			}
			break;
		case sf::Keyboard::Up:
			if (this->playerId == 1)
				this->jump = true;
			break;
		case sf::Keyboard::Down:
			if (this->playerId == 1)
				this->crouching = true;
			break;
		case sf::Keyboard::Enter:
			if (!this->done)
			{
				if (this->walking)
					this->walking = false;
				else
					this->walking = true;
			}
			break;
		default:
			break;
		}
	}
	else
	{
		switch (_event.key.code)
		{
		case sf::Keyboard::D:
			if (this->playerId == 0)
				this->walkRight = false;
			break;
		case sf::Keyboard::A:
			if (this->playerId == 0)
				this->walkLeft = false;
			break;
		case sf::Keyboard::W:
			if (this->playerId == 0)
				this->jump = false;
			break;
		case sf::Keyboard::S:
			if (this->playerId == 0)
				this->crouching = false;
			break;
		case sf::Keyboard::Right:
			if (this->playerId == 1)
				this->walkRight = false;
			break;
		case sf::Keyboard::Left:
			if (this->playerId == 1)
				this->walkLeft = false;
			break;
		case sf::Keyboard::Up:
			if (this->playerId == 1)
				this->jump = false;
			break;
		case sf::Keyboard::Down:
			if (this->playerId == 1)
				this->crouching = false;
			break;
		default:
			break;
		}
	}
};
void Characters::Player::Initialize()
{
	this->playerCounter++;

	if (this->playerCounter == 1)
		this->SetTexture(P1_TEXTURE_REF, sf::IntRect(0, 0, TEXTURE_TOKEN_SIZE, TEXTURE_TOKEN_SIZE));
	else
		this->SetTexture(P2_TEXTURE_REF, sf::IntRect(0, 0, TEXTURE_TOKEN_SIZE, TEXTURE_TOKEN_SIZE));

	sf::Vector2i size(TEXTURE_TOKEN_SIZE, TEXTURE_TOKEN_SIZE);
	this->AddRangeAnimations(
		std::vector<std::pair<int, Animation>>({
			std::pair<int, Animation>(Actions::IDLE,		Animation(0, 2, 0,		size, 0.4f,		true)),
			std::pair<int, Animation>(Actions::WALKING,		Animation(3, 9, 0,		size, 0.15f,	true)),
			std::pair<int, Animation>(Actions::KICK,		Animation(10, 12, 0,	size, 0.6f,		true)),
			std::pair<int, Animation>(Actions::DAMAGED,		Animation(13, 16, 0,	size, 0.6f,		true)),
			std::pair<int, Animation>(Actions::CROUCHING,	Animation(17, 23, 0,	size, 0.1f,		true))
			}
		)
	);
};

void Characters::Player::ObstacleCollision(Entity* Obstacle)
{
	sf::Vector2f intersection;
	sf::Vector2f obsSize(Obstacle->GetHitBoxSize());
	sf::Vector2f size(this->GetHitBoxSize());
	sf::Vector2f distance(
		Obstacle->GetPosition().x - this->GetPosition().x,
		Obstacle->GetPosition().y - this->GetPosition().y
	);

	obsSize /= 2.0f;
	size /= 2.0f;

	intersection = sf::Vector2f(
		fabs(distance.x) - (obsSize.x + size.x),
		fabs(distance.y) - (obsSize.y + size.y)
	);

	if (intersection.x > intersection.y)
	{
		if (distance.x > 0.f)
			this->MovePosition(intersection.x, 0.f);
		else
			this->MovePosition(-(intersection.x), 0.f);
	}
	else
	{
		if (distance.y > 0.f)
			this->MovePosition(0.f, intersection.y);
		else
			this->MovePosition(0.f, -(intersection.y));
		this->onGround = true;
	}
};
void Characters::Player::CameraCollision(Camera* camera)
{
	sf::FloatRect cameraBounds(camera->CameraBounds());
	sf::FloatRect entBounds(this->GetHitBoxBounds());

	if (entBounds.left < cameraBounds.left || entBounds.width > cameraBounds.width)
	{
		if (entBounds.left < cameraBounds.left)
			this->MovePosition(sf::Vector2f(cameraBounds.left - entBounds.left, 0.f));
		else
			this->MovePosition(sf::Vector2f(cameraBounds.width - entBounds.width, 0.f));
	}
};
void Characters::Player::StageCollision(Stage* stage)
{
	sf::FloatRect entBounds(this->GetHitBoxBounds());
	sf::FloatRect mapBounds(stage->GetMapBounds());

	if (entBounds.top < mapBounds.top || entBounds.height > mapBounds.height)
	{
		if (entBounds.top < mapBounds.top)
			this->MovePosition(sf::Vector2f(0.f, mapBounds.top - entBounds.top));
		else
		{
			this->MovePosition(sf::Vector2f(0.f, mapBounds.height - entBounds.height));
			this->onGround = true;
		}
	}
};