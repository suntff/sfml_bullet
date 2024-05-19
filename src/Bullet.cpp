#include "Bullet.hpp"

namespace mt {

    Bullet::Bullet(float x, float y, float r, float vx, float vy) {
        Setup(x, y, r, vx, vy);
    }

    Bullet& Bullet::operator=(const Bullet& other) {
        if (this != &other) {
            m_r = other.m_r;
            m_x = other.m_x;
            m_y = other.m_y;
            m_vx = other.m_vx;
            m_vy = other.m_vy;
            m_shape = other.m_shape;
            m_available = other.m_available;
        }
        return *this;
    }

    void Bullet::Setup(float x, float y, float r, float vx, float vy) {
        m_x = x;
        m_y = y;
        m_r = r;
        m_vx = vx;
        m_vy = vy;
        m_shape.setOrigin(m_r, m_r);
        m_shape.setRadius(m_r);
        m_shape.setPosition(m_x, m_y);
        int color_r = 255;
        int color_g = 0;
        int color_b = 0;
        m_shape.setFillColor(sf::Color::Color(color_r, color_b, color_g, 255));
    }

    sf::CircleShape Bullet::Get() {
        return m_shape;
    }

    float Bullet::X() { return m_x; }
    void Bullet::X(float value) { m_x = value; m_shape.setPosition(m_x, m_y); }
    void Bullet::Y(float value) { m_y = value; m_shape.setPosition(m_x, m_y); }
    float Bullet::Y() { return m_y; }
    float Bullet::R() { return m_r; }
    float Bullet::Vx() { return m_vx; }
    float Bullet::Vy() { return m_vy; }

    void Bullet::Move(float dt) {
        m_x += m_vx * dt;
        m_y += m_vy * dt;
        m_shape.setPosition(m_x, m_y);
    }

    sf::CircleShape Bullet::GetBullet() {
        return m_shape;
    }
}
