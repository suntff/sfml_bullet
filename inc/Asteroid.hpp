#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Bullet.hpp"

namespace mt
{
    class Asteroid
    {
        const int m_asteroidR = 10;
        float m_v_Asteroid = 200;

        float m_x, m_y;
        float m_alpha;
        float m_v;
        float m_r;
        sf::Texture m_textureAsteroid;
        sf::Sprite m_spriteAsteroid;
        float m_scaleFactor = 0.1;
        Bullet bullet;

    public:
        Asteroid() = default;
        Asteroid(float x, float y);
        Asteroid& operator=(const Asteroid& other);
        bool Setup(float x, float y);
        sf::Sprite Get();
    };
}
