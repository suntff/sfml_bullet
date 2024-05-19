#include "Asteroid.hpp"
#include <cmath>
#include <string>

namespace mt {

    Asteroid::Asteroid(float x, float y) {
        m_x = x;
        m_y = y;
    }

    Asteroid& Asteroid::operator=(const Asteroid& other) {
        if (this != &other) {
            m_x = other.m_x;
            m_y = other.m_y;
            m_alpha = other.m_alpha;
            m_v = other.m_v;
            m_r = other.m_r;
            m_textureAsteroid = other.m_textureAsteroid;
            m_spriteAsteroid = other.m_spriteAsteroid;
            m_scaleFactor = other.m_scaleFactor;
            bullet = other.bullet;
        }
        return *this;
    }

    bool Asteroid::Setup(float x, float y) {
        m_x = x;
        m_y = y;
        std::string asteroid_adress = "assets\\asteroid.png";
        if (!m_textureAsteroid.loadFromFile(asteroid_adress)) {
            std::cerr << "Error while loading " << asteroid_adress << std::endl;
            return false;
        }
        m_spriteAsteroid.setTexture(m_textureAsteroid);
        m_spriteAsteroid.setScale(m_scaleFactor, m_scaleFactor);
        m_spriteAsteroid.setOrigin(m_textureAsteroid.getSize().x / 2, m_textureAsteroid.getSize().y / 2);
        m_spriteAsteroid.setPosition(m_x, m_y);

        if (m_textureAsteroid.getSize().x > m_textureAsteroid.getSize().y)
            m_r = m_scaleFactor * m_textureAsteroid.getSize().x / 2;
        else
            m_r = m_scaleFactor * m_textureAsteroid.getSize().y / 2;

        return true;
    }

    sf::Sprite Asteroid::Get() {
        return m_spriteAsteroid;
    }
}
