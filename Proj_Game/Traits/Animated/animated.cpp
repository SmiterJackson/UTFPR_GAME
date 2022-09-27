#include "animated.h"

Animated::Animation::Animation() :
	sheet_token(), start(0), end(0), row(0), current(0), 
	timeAcumulator(0.f), switchTime(1.f), repeatable(true)
{};
Animated::Animation::Animation(int _start, int _end, int _row, sf::Vector2i size, float animSwitchTime, bool repeatable):
	sheet_token(), start(_start), end(_end), row(_row), current(_start),
	timeAcumulator(0.f), switchTime(animSwitchTime), repeatable(repeatable)
{
	this->sheet_token.width = size.x;
	this->sheet_token.height = size.y;
};
Animated::Animation::Animation(int _start, int _end, int _row, int width, int height, float animSwitchTime, bool repeatable):
	sheet_token(), start(_start), end(_end), row(_row), current(_start),
	timeAcumulator(0.f), switchTime(animSwitchTime), repeatable(repeatable)
{
	this->sheet_token.width = width;
	this->sheet_token.height = height;
};
Animated::Animation::~Animation()
{};

void Animated::Animation::ResetAnimation()
{
	this->current = this->start;
};
const sf::IntRect& Animated::Animation::update(float* pElapsed_time, bool right)
{
	this->timeAcumulator += *pElapsed_time;

	if (this->timeAcumulator >= this->switchTime)
	{
		this->timeAcumulator -= this->switchTime;

		if (this->current <= this->end)
			this->current++;

		if (this->repeatable)
		{
			if (this->current > this->end)
				this->current = this->start;
		}
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


Animated::Animated():
	animations(), pTexture(nullptr), pBody(nullptr), next_ani(0), last_ani(0), looking_right(true)
{};
Animated::Animated(const AnimationSheet _animations, sf::Texture* _pTexture, sf::Sprite* _pBody) :
	animations(), pTexture(_pTexture), pBody(_pBody), next_ani(0), last_ani(0), looking_right(true)
{
	AnimationSheet::const_iterator it;
	for (it = _animations.cbegin(); it != _animations.cend(); it++)
		this->animations.emplace(it->first, it->second);
};
Animated::~Animated()
{};

void Animated::UpdateAnimation(float* pElapsedTime)
{
	if (this->next_ani != this->last_ani)
	{
		this->animations[this->last_ani].ResetAnimation();
		this->last_ani = this->next_ani;
	}

	this->pBody->setTextureRect(this->animations[this->next_ani].update(
		pElapsedTime, this->looking_right)
	);
};

void Animated::AddAnimation(const int key, const Animation _animation)
{
	this->animations.emplace(key, _animation);
};
void Animated::AddRangeAnimations(const AnimationSheet _animations)
{
	AnimationSheet::const_iterator it;
	for (it = _animations.cbegin(); it != _animations.cend(); it++)
		this->animations.emplace(it->first, it->second);
};
void Animated::RemoveAnimation(const int key)
{
	this->animations.erase(key);
};
void Animated::RemoveRangeAnimations(const std::vector<int> keys)
{
	std::vector<int>::const_iterator it;
	for (it = keys.cbegin(); it != keys.cend(); it++)
		this->animations.erase(*it);
};