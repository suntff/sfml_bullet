#pragma once
#include <string>
#include <thread>
#include <iostream>
#include <Ship.hpp>
#include <Bullet.hpp>
#include <Circle.hpp>
#include <Asteroid.hpp>
namespace mt
{

	const float pi = acos(-1);

	class Game
	{
		int m_width;
		int m_height;
		std::string m_capture;
		mt::Circle* m_c;
		mt::Asteroid* asteroids;
		int m_nc; int m_na;
		sf::RenderWindow m_window;
		sf::Texture m_textureBackground;
		sf::Sprite m_spriteBackground;
		sf::Font m_font;
		sf::Text m_fpsText;
		Ship m_ship;
		bool isVisible = true;
		bool isTouchBorder = true;
		int count_bullets = 0;
		int size_bullets = 100;
		mt::Bullet* bullets = new mt::Bullet[size_bullets];

	public:
		Game(int width, int height, const std::string& capture);

		bool Setup(int n);

		void TouchBorder(Circle& obj);

		void Collision(int i);
		bool Are_circles_collision(Bullet& obj1, Circle& obj2);
		bool Are_bullet_collision_with_asteroid(Bullet& obj1, Asteroid& obj2);

		void Increase_size_bullets();
		void remove_circle(int i);
		void remove_asteroid(int i);
		void LifeCycle();

		~Game();
	};
}


