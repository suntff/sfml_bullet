#pragma once
#include <SFML/Graphics.hpp>

namespace mt
{

	class Circle
	{
		float m_r;
		float m_x, m_y;
		float m_v;
		float m_alfa;
		sf::CircleShape m_shape;

	public:
		Circle() = default;

		Circle(float x, float y, float r, float v, float alfa);
		Circle& operator=(const Circle& other);
		void Setup(float x, float y, float r, float v, float alfa);

		sf::CircleShape Get();

		float X();
		void X(float value);
		void Y(float value);
		float Y();
		float R();
		float Vx();
		float Vy();
		void V(float value);
		//void Vy() { return m_v * sin(m_alfa); }
		float V();
		float Alfa();
		void Alfa(float alfa);


		void Move(float dt);
	};

}
