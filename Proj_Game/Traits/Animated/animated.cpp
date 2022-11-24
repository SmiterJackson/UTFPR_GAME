#include "animated.h"
#include "../game/game.h"

Trait::Animated::Animation::Animation() :
	sheet_token(), start(0), end(0), row(0), current(0), 
	timeAcumulator(0.f), switchTime(1.f), repeatable(true)
{};
Trait::Animated::Animation::Animation(int _start, int _end, int _row, sf::Vector2i size, float animSwitchTime, bool repeatable):
	sheet_token(), start(_start), end(_end), row(_row), current(_start),
	timeAcumulator(0.f), switchTime(animSwitchTime), repeatable(repeatable)
{
	this->sheet_token.width = size.x;
	this->sheet_token.height = size.y;
};
Trait::Animated::Animation::Animation(int _start, int _end, int _row, int width, int height, float animSwitchTime, bool repeatable):
	sheet_token(), start(_start), end(_end), row(_row), current(_start),
	timeAcumulator(0.f), switchTime(animSwitchTime), repeatable(repeatable)
{
	this->sheet_token.width = width;
	this->sheet_token.height = height;
};
Trait::Animated::Animation::~Animation()
{};

void Trait::Animated::Animation::ResetAnimation()
{
	this->current = this->start;
};
const sf::IntRect& Trait::Animated::Animation::Update(const float& pElapsed_time, bool right)
{
	this->timeAcumulator += pElapsed_time;
	unsigned short int state = Game::GetGameState();

	if(state == GameStateType::PAUSE_MENU || state == GameStateType::SUB_MENU)
	{
		this->timeAcumulator -= pElapsed_time;
		return this->sheet_token;
	}

	if (this->timeAcumulator >= this->switchTime)
	{
		this->timeAcumulator -= this->switchTime;

		if (this->repeatable)
		{
			if (this->current == this->end)
				this->current = this->start;
		}

		if (this->current < this->end)
			this->current++;
	}

	this->sheet_token.top = this->row * this->sheet_token.height;

	if(right)
	{
		this->sheet_token.left = this->current * abs(this->sheet_token.width);
		this->sheet_token.width = abs(this->sheet_token.width);

		return this->sheet_token;
	}

	this->sheet_token.left = (this->current + 1) * abs(this->sheet_token.width);
	this->sheet_token.width = -abs(this->sheet_token.width);

	return this->sheet_token;
};


Trait::Animated::Animated(sf::Sprite& _bodyRef, const AnimationSheet _animations) :
	animations(), bodyRef(_bodyRef), next_ani(0), last_ani(0), looking_right(true)
{
	AnimationSheet::const_iterator it;
	sf::Vector2f size;

	for (it = _animations.cbegin(); it != _animations.cend(); it++)
		this->animations.emplace(it->first, it->second);

	size = this->animations[this->next_ani].GetAnimationSize();
	this->bodyRef.setOrigin(size / 2.f);
};
Trait::Animated::~Animated()
{};

void Trait::Animated::UpdateAnimation(const float& pElapsedTime)
{
	if (this->next_ani != this->last_ani)
	{
		this->animations[this->last_ani].ResetAnimation();
		this->last_ani = this->next_ani;
	}

	this->bodyRef.setTextureRect(this->animations[this->next_ani].Update(
		pElapsedTime, this->looking_right)
	);
};

void Trait::Animated::AddAnimation(const int key, const Animation _animation)
{
	this->animations.emplace(key, _animation);
};
void Trait::Animated::AddAnimationRange(const AnimationSheet _animations)
{
	AnimationSheet::const_iterator it;
	for (it = _animations.cbegin(); it != _animations.cend(); it++)
		this->animations.emplace(it->first, it->second);
};
void Trait::Animated::RemoveAnimation(const int key)
{
	this->animations.erase(key);
};
void Trait::Animated::RemoveAnimationRange(const std::vector<int> keys)
{
	std::vector<int>::const_iterator it;
	for (it = keys.cbegin(); it != keys.cend(); it++)
		this->animations.erase(*it);
};