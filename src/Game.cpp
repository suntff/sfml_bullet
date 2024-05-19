#include <Game.hpp>
namespace mt
{
		Game::Game(int width, int height, const std::string& capture)
		{
			m_width = width;
			m_height = height;
			m_capture = capture;
		}

		bool Game::Setup(int n)
		{
			m_nc = n; m_na = m_nc;
			m_window.create(sf::VideoMode(m_width, m_height), m_capture);
			std::string background_adress = "assets\\background.jpg";
			if (!m_textureBackground.loadFromFile(background_adress))
			{
				std::cerr << "Error while loading " << background_adress << std::endl;
				return false;
			}
			m_spriteBackground.setTexture(m_textureBackground);
			std::string font_adress = "assets\\AGENCYB.TTF";
			if (!m_font.loadFromFile(font_adress))
			{
				std::cerr << "Error while loading " << font_adress << std::endl;
				return false;
			}
			m_fpsText.setFont(m_font);

			if (!m_ship.Setup(100, 100))
				return false;

			srand(time(0));

			m_c = new mt::Circle[m_nc];
			for (int i = 0; i < m_nc; i++)
			{
				int r = rand() % 100 + 10;
				int x = rand() % (m_width - 2 * r) + r;
				int y = rand() % (m_height - 2 * r) + r;
				int v = rand() % 50 + 100;
				float alfa = rand() % 7;
				m_c[i].Setup(x, y, r, v, alfa);
			}
			asteroids = new mt::Asteroid[m_na];
			for (int i = 0; i < m_na; i++)
			{
				int x = rand() % static_cast<int>(m_width);
				int y = rand() % static_cast<int>(m_height);
				asteroids[i].Setup(x, y);
			}
		}

		void Game::TouchBorder(Circle& obj)
		{
			float x = obj.X();
			float y = obj.Y();
			float r = obj.R();


			if (isTouchBorder)
			{
				isTouchBorder = false;

				if (x + r >= m_width || x - r <= 0)
				{
					obj.Alfa(pi - obj.Alfa());
				}

				if (y + r >= m_height || y - r <= 0)
				{
					obj.Alfa(2 * pi - obj.Alfa());
				}

			}
			else
			{
				if (x + r + 20 <= m_width || x - r - 20 >= 0)
				{
					isTouchBorder = true;
				}

				if (y + r + 20 <= m_height || y - r - 20 >= 0)
				{
					isTouchBorder = true;
				}
			}

		}

		void Game::Collision(int i)
		{
			Circle& c = m_c[i];
			float dist = sqrt(pow(m_ship.X() - c.X(), 2) + pow(m_ship.Y() - c.Y(), 2));
			if (m_ship.R() + c.R() >= dist)
			{
				std::cout << "Collision " << m_ship.V() << std::endl;
				isVisible = false;
			}
		}
		bool Game::Are_circles_collision(Bullet& obj1, Circle& obj2) {
			if (std::hypot(obj1.GetBullet().getPosition().x - obj2.Get().getPosition().x, obj1.Get().getPosition().y - obj2.Get().getPosition().y) <=
				obj1.Get().getRadius() + obj2.Get().getRadius()) {
				return true;
			}
			return false;
		}
		bool Game::Are_bullet_collision_with_asteroid(Bullet& obj1, Asteroid& obj2) {
			sf::Rect bounds_asteroids = obj2.Get().getGlobalBounds();
			float width_asteroid = bounds_asteroids.width;
			float height_asteroid = bounds_asteroids.height;
			float left_asteroid = bounds_asteroids.left;
			float top_asteroid = bounds_asteroids.top;
			float center_x = bounds_asteroids.left + bounds_asteroids.width / 2;
			float center_y = bounds_asteroids.top + bounds_asteroids.height / 2;
			float hypot_asteroid = std::hypot(width_asteroid, height_asteroid) / 2;
			float dist = std::hypot(obj1.Get().getPosition().x - obj2.Get().getPosition().x, obj1.Get().getPosition().y - obj2.Get().getPosition().y);
			if (dist <= hypot_asteroid + obj1.Get().getRadius()) {
				return true;

			}
			return false;
		}

		void Game::Increase_size_bullets() {
			size_bullets *= 1.5;
			Bullet* new_bullets = new Bullet[size_bullets];
			for (int i = 0; i < count_bullets; ++i) {
				new_bullets[i] = bullets[i];
			}
			delete[] bullets;
			bullets = new_bullets;
		}
		void Game::remove_circle(int i) {
			if (i >= 0 && i < m_nc) {
				for (int j = i; j < m_nc - 1; j++) {
					m_c[j] = m_c[j + 1];
				}
				m_nc--;
			}
		}
		void Game::remove_asteroid(int i) {
			if (i >= 0 && i < m_na) {
				for (int j = i; j < m_na - 1; j++) {
					asteroids[j] = asteroids[j + 1];
				}
				m_na--;
			}
		}
		void Game::LifeCycle()
		{
			sf::Clock clock;
			sf::Clock clock_bullet;
			sf::Clock clock_fps;
			m_window.setVerticalSyncEnabled(true);
			while (m_window.isOpen())
			{
				sf::Event event;
				while (m_window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						m_window.close();
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					m_ship.setVelocity(1);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					m_ship.setVelocity(-1);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					m_ship.Rotate(-2);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					m_ship.Rotate(2);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					if (count_bullets == size_bullets) {
						Increase_size_bullets();
					}
					if (clock_bullet.getElapsedTime().asSeconds() > 0.5) {
						bullets[count_bullets].Setup(m_ship.Get().getPosition().x, m_ship.Get().getPosition().y, 5,
							(m_ship.V() + 30) * cos(acos(-1) * m_ship.Alpha() / 180), (m_ship.V() + 30) * sin(acos(-1) * m_ship.Alpha() / 180));
						count_bullets++;
						clock_bullet.restart();
					}
				}
				float dt = clock.getElapsedTime().asSeconds();
				clock.restart();

				m_ship.Move(dt);
				for (int i = 0; i < count_bullets; i++) {
					bullets[i].Move(dt);
				}

				for (int i = 0; i < m_nc; i++)
				{
					float x = m_c[i].X();
					float y = m_c[i].Y();
					float r = m_c[i].R();
					float v = m_c[i].V();
					float alfa = m_c[i].Alfa();

					float x_s = x + v * cos(alfa) * dt;
					float y_s = y + v * sin(alfa) * dt;

					bool collision = false;
					if (x_s + r >= m_width)
					{
						m_c[i].Alfa(pi - m_c[i].Alfa());
						m_c[i].X(m_width - r);
						collision = true;
					}

					if (x_s - r <= 0)
					{
						m_c[i].Alfa(pi - m_c[i].Alfa());
						m_c[i].X(r);
						collision = true;
					}

					if (y_s + r >= m_height)
					{
						m_c[i].Alfa(2 * pi - m_c[i].Alfa());
						m_c[i].Y(m_height - r);
						collision = true;
					}

					if (y_s - r <= 0)
					{
						m_c[i].Alfa(2 * pi - m_c[i].Alfa());
						m_c[i].Y(r);
						collision = true;
					}

					if (!collision)
					{
						m_c[i].X(x_s);
						m_c[i].Y(y_s);
					}
				}

				for (int i = 0; i < m_nc; i++) {
					for (int j = 0; j < count_bullets; j++) {
						if (Are_circles_collision(bullets[j], m_c[i])) {
							remove_circle(i);
							i--;
							break;
						}
					}
				}

				for (int i = 0; i < m_na; i++) {
					for (int j = 0; j < count_bullets; j++) {
						if (Are_bullet_collision_with_asteroid(bullets[j], asteroids[i])) {
							remove_asteroid(i);
							i--;
							break;
						}
					}
				}
				if (clock_fps.getElapsedTime().asSeconds() > 0.5)
				{
					m_fpsText.setString(std::to_string(1 / dt));
					clock_fps.restart();
				}
				m_window.clear();
				m_window.draw(m_spriteBackground);
				m_window.draw(m_fpsText);
				if (isVisible)
					m_window.draw(m_ship.Get());
				for (int i = 0; i < count_bullets; i++) {
					m_window.draw(bullets[i].GetBullet());
				}
				for (int i = 0; i < m_na; i++) {
					m_window.draw(asteroids[i].Get());
				}
				for (int i = 0; i < m_nc; i++) {
					m_window.draw(m_c[i].Get());
				}

				m_window.display();
			}
		}

		Game::~Game() {
			delete[] bullets;
			delete[] m_c;
			delete[] asteroids;
		}
}


