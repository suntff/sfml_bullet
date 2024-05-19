#include <Circle.hpp>

namespace mt
{

		Circle::Circle(float x, float y, float r, float v, float alfa)
		{
			Setup(x, y, r, v, alfa);
		}
		Circle& Circle::operator=(const Circle& other)
		{
			if (this != &other)
			{
				m_r = other.m_r;
				m_x = other.m_x;
				m_y = other.m_y;
				m_v = other.m_v;
				m_alfa = other.m_alfa;
				m_shape = other.m_shape;
			}
			return *this;
		}
		void Circle::Setup(float x, float y, float r, float v, float alfa)
		{
			m_x = x;
			m_y = y;
			m_r = r;
			m_v = v;
			m_alfa = alfa;
			m_shape.setOrigin(m_r, m_r);
			m_shape.setRadius(m_r);
			m_shape.setPosition(m_x, m_y);
			int color_r = rand() % 256;
			int color_g = rand() % 256;
			int color_b = rand() % 256;
			m_shape.setFillColor(sf::Color::Color(color_r, color_b, color_g, 0));
			m_shape.setOutlineThickness(-10.f);
			m_shape.setOutlineColor(sf::Color(250, 150, 100));
		}

		sf::CircleShape Circle::Get()
		{
			return m_shape;
		}

		float Circle::X() { return m_x; }
		void Circle::X(float value) { m_x = value; m_shape.setPosition(m_x, m_y); }
		void Circle::Y(float value) { m_y = value; m_shape.setPosition(m_x, m_y); }
		float Circle::Y() { return m_y; }
		float Circle::R() { return m_r; }
		float Circle::Vx() { return m_v * cos(m_alfa); }
		float Circle::Vy() { return m_v * sin(m_alfa); }
		void Circle::V(float value) { m_v = value / cos(m_alfa); }
		//void Vy() { return m_v * sin(m_alfa); }
		float Circle::V() { return m_v; }
		float Circle::Alfa() { return m_alfa; }
		void Circle::Alfa(float alfa)
		{
			m_alfa = alfa;
		}


		void Circle::Move(float dt)
		{
			float vx = m_v * cos(m_alfa);
			float vy = m_v * sin(m_alfa);
			m_x += vx * dt;
			m_y += vy * dt;
			m_shape.setPosition(m_x, m_y);
		}

}

