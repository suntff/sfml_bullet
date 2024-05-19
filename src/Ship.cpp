#include "Ship.hpp"
#include <cmath>
#include <string>

namespace mt {

    Ship::Ship(float x, float y) {
        m_x = x;
        m_y = y;
    }

    bool Ship::Setup(float x, float y) {
        m_x = x;
        m_y = y;
        m_alpha = 0;
        m_v = 0;
        std::string ship_adress = "assets\\ship.png";
        if (!m_textureShip.loadFromFile(ship_adress)) {
            std::cerr << "Error while loading " << ship_adress << std::endl;
            return false;
        }
        m_spriteShip.setTexture(m_textureShip);
        m_spriteShip.setScale(m_scaleFactor, m_scaleFactor);
        m_spriteShip.setOrigin(m_textureShip.getSize().x / 2, m_textureShip.getSize().y / 2);
        m_spriteShip.setPosition(m_x, m_y);
        m_spriteShip.setRotation(m_alpha);

        if (m_textureShip.getSize().x > m_textureShip.getSize().y)
            m_r = m_scaleFactor * m_textureShip.getSize().x / 2;
        else
            m_r = m_scaleFactor * m_textureShip.getSize().y / 2;

        return true;
    }

    void Ship::setVelocity(float dv) {
        m_v += dv;
    }

    float Ship::V() { return m_v; }

    void Ship::Move(float dt) {
        bullet.Move(dt);

        float alphaRad = acos(-1) * m_alpha / 180;
        m_x += m_v * cos(alphaRad) * dt;
        m_y += m_v * sin(alphaRad) * dt;
        m_spriteShip.setPosition(m_x, m_y);
    }

    float Ship::R() { return m_r; }
    float Ship::Alpha() { return m_alpha; }
    float Ship::X() { return m_x; }
    float Ship::Y() { return m_y; }

    void Ship::Rotate(float dalpha) {
        m_alpha += dalpha;
        m_spriteShip.setRotation(m_alpha);
    }

    sf::Sprite Ship::Get() {
        return m_spriteShip;
    }
}
