#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Bullet.hpp"

namespace mt
{
    class Ship
    {
        const int m_bulletR = 10;
        float m_v_bullet = 200;

        float m_x, m_y;
        float m_alpha;
        float m_v;
        float m_r;
        sf::Texture m_textureShip;
        sf::Sprite m_spriteShip;
        float m_scaleFactor = 0.2f;

        Bullet bullet;

    public:
        Ship() = default;
        Ship(float x, float y);
        bool Setup(float x, float y);
        void setVelocity(float dv);
        float V();
        void Move(float dt);
        float R();
        float Alpha();
        float X();
        float Y();
        void Rotate(float dalpha);
        sf::Sprite Get();
    };
}
