#pragma once

#include "../Traits/PrintableBody/printableBody.h"

namespace Trait
{
	class Animated : public PrintableBody
	{
	public:
		class Animation
		{
		public:
			Animation();
			Animation(int _start, int _end, int _row, sf::Vector2i size, float animSwitchTime, bool repeatable = true);
			Animation(int _start, int _end, int _row, int width, int height, float animSwitchTime, bool repeatable = true);
			~Animation();

			const sf::Vector2f GetAnimationSize() const { return sf::Vector2f(float(this->sheet_token.width), float(this->sheet_token.height)); };

			void ResetAnimation();
			const sf::IntRect& Update(const float& pElapsed_time, bool right = true);

		private:
			sf::IntRect sheet_token;

			int start, end, row, current;
			float timeAcumulator, switchTime;
			bool repeatable;
		};

		typedef std::vector<std::pair<int, Animation>> AnimationSheet;

		Animated();
		Animated(const std::string path, const AnimationSheet _animations, const float proportion = 1.0f);
		~Animated();

		void InvertDirection() { this->looking_right = !this->looking_right; };

		void UpdateAnimation(const float& pElapsedTime);

		void AddAnimation(const int key, const Animation _animation);
		void AddAnimationRange(const AnimationSheet _animations);
		void RemoveAnimation(const int key);
		void RemoveAnimationRange(const std::vector<int> keys);

	protected:
		std::unordered_map<int, Animation> animations;

		unsigned int next_ani, last_ani;
		bool looking_right;
	};
}