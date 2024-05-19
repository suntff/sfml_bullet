#pragma once
#include <SFML/Graphics.hpp>

namespace mt
{
    class Bullet
    {
        float m_r;
        float m_x, m_y;
        float m_vx, m_vy;
        sf::CircleShape m_shape;

        bool m_available = false;

    public:
        Bullet() = default;
        Bullet(float x, float y, float r, float vx, float vy);
        Bullet& operator=(const Bullet& other);
        void Setup(float x, float y, float r, float vx, float vy);
        sf::CircleShape Get();
        float X();
        void X(float value);
        void Y(float value);
        float Y();
        float R();
        float Vx();
        float Vy();
        void Move(float dt);
        sf::CircleShape GetBullet();
    };
}
