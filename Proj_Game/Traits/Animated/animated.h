#pragma once

#include "stdafx.h"

namespace Trait
{
	class Animated
	{
	public:
		class Animation
		{
		public:
			Animation();
			Animation(int _start, int _end, int _row, sf::Vector2i size, float animSwitchTime, bool repeatable = true);
			Animation(int _start, int _end, int _row, int width, int height, float animSwitchTime, bool repeatable = true);
			~Animation();

			void ResetAnimation();
			const sf::IntRect& update(const float& pElapsed_time, bool right = true);

		private:
			sf::IntRect sheet_token;

			int start, end, row, current;
			float timeAcumulator, switchTime;
			bool repeatable;
		};

		typedef std::vector<std::pair<int, Animation>> AnimationSheet;

		Animated();
		Animated(const AnimationSheet _animations, sf::Texture* _pTexture, sf::Sprite* _pBody);
		~Animated();

		void SetTextureReference(sf::Texture* _pTexture) { this->pTexture = _pTexture; };
		void SetBodyReference(sf::Sprite* _pBody) { this->pBody = _pBody; };
		void InvertDirection() { this->looking_right = !this->looking_right; };

		void UpdateAnimation(const float& pElapsedTime);

		void AddAnimation(const int key, const Animation _animation);
		void AddRangeAnimations(const AnimationSheet _animations);
		void RemoveAnimation(const int key);
		void RemoveRangeAnimations(const std::vector<int> keys);

	protected:
		std::unordered_map<int, Animation> animations;
		sf::Texture* pTexture;
		sf::Sprite* pBody;

		unsigned int next_ani, last_ani;
		bool looking_right;
	};
}