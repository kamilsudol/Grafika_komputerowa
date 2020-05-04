// Calosc mozna dowolnie edytowac wedle uznania. 

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "font.h"
#include <iostream>

class Menu : public sf::Drawable
{
private:
	sf::Font font;
	sf::Text *text;
	sf::RectangleShape *rectangle;

	sf::Texture *colors_texture;
	sf::Sprite *colors_sprite;
	sf::Uint8 *colors_pixels;
	const unsigned int colors_size_x = 765;
	const unsigned int colors_size_y = 60;
	inline void draw_to_color_pixels(unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b)
	{
		colors_pixels[4 * (y * colors_size_x + x) + 0] = r;
		colors_pixels[4 * (y * colors_size_x + x) + 1] = g;
		colors_pixels[4 * (y * colors_size_x + x) + 2] = b;
		colors_pixels[4 * (y * colors_size_x + x) + 3] = 255;
	}

public:
	Menu()
	{
		font.loadFromMemory(font_data, font_data_size);
		text = new sf::Text;
		text->setFont(font);
		text->setCharacterSize(12);
		text->setFillColor(sf::Color::White);

		rectangle = new sf::RectangleShape(sf::Vector2f(796, 536));
		rectangle->setFillColor(sf::Color::Transparent);
		rectangle->setOutlineColor(sf::Color::White);
		rectangle->setOutlineThickness(1.0f);
		rectangle->setPosition(2, 62);

		unsigned int x, y;
		colors_pixels = new sf::Uint8[colors_size_x * colors_size_y * 4];
		for (x = 0; x < 255; x++)
			for (y = 0; y < 30; y++)
			{
				draw_to_color_pixels(x, y, x, 255, 0);
				draw_to_color_pixels(x + 255, y, 255, 255 - x, 0);
				draw_to_color_pixels(x + 510, y, 255, 0, x);
				draw_to_color_pixels(254 - x, y + 30, 0, 255, 255 - x);
				draw_to_color_pixels(509 - x, y + 30, 0, x, 255);
				draw_to_color_pixels(764 - x, y + 30, 255 - x, 0, 255);
			}

		colors_texture = new sf::Texture();
		colors_texture->create(colors_size_x, colors_size_y);
		colors_texture->update(colors_pixels);

		colors_sprite = new sf::Sprite();
		colors_sprite->setTexture(*colors_texture);
		colors_sprite->setPosition(1, 1);
	}

	void outtextxy(sf::RenderTarget& target, float x, float y,const wchar_t *str) const
	{
		text->setPosition(x, y);
		text->setString(str);
		target.draw(*text);
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		outtextxy(target, 5, 600, L"f - wybór koloru rysowania");
		outtextxy(target, 5, 615, L"b - wybór koloru wype³niania");
		outtextxy(target, 5, 630, L"l - rysowanie linii");

		outtextxy(target, 200, 600, L"r - rysowanie prostok¹ta");
		outtextxy(target, 200, 615, L"a - rysowanie wype³nionego prostok¹ta");
		outtextxy(target, 200, 630, L"c - rysowanie okrêgu");

		outtextxy(target, 470, 600, L"w - zapis do pliku");
		outtextxy(target, 470, 615, L"o - odczyt z pliku");
		outtextxy(target, 470, 630, L"esc - wyjœcie");

		outtextxy(target, 650, 615, L"Aktualne:");
		outtextxy(target, 650, 600, L"v - rysowanie wype³nionego okrêgu");
		
		target.draw(*rectangle);
		target.draw(*colors_sprite);
	}
};

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 650), "GFK Lab 01", sf::Style::Titlebar | sf::Style::Close);
	sf::Event event;
	Menu menu;

	sf::Font font;
	font.loadFromMemory(font_data, font_data_size);
	sf::Text *text = new sf::Text;
	text->setFont(font);
	text->setCharacterSize(17);
	text->setFillColor(sf::Color::White);

	sf::Image cl_bar;

	sf::Texture bufor;
	sf::Texture obraz;
	sf::Sprite sprite;

	sf::RectangleShape color_bar, fill_color_bar,blackbar,blackbar2;
	sf::Color color = sf::Color::Blue, fill_color = sf::Color::Green;

	sf::VertexArray linia(sf::LinesStrip,2);
	sf::RectangleShape prostokat;
	sf::CircleShape kolko;

	window.setFramerateLimit(60);
	obraz.create(800, 650);
	bufor.create(800, 650);
	cl_bar.create(750, 60);
	sprite.setTexture(bufor);

	char znak = ' ';
	bool mouse_flag = false;
	float mouse_x = 0, mouse_y = 0;

	window.clear(sf::Color::Black);
	window.draw(menu);
	obraz.update(window);
	cl_bar = obraz.copyToImage();

	while (window.isOpen())
	{
		window.clear(sf::Color::Black);

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			
			if (event.type == sf::Event::MouseButtonPressed) {
				mouse_flag = true;
				mouse_x = (int)sf::Mouse::getPosition(window).x;
				mouse_y = (int)sf::Mouse::getPosition(window).y;
			}
			if (event.type == sf::Event::MouseButtonReleased) {
				mouse_flag = false;
				bufor.update(obraz.copyToImage());
			}

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::F) {
					znak = 'f';
				}else if (event.key.code == sf::Keyboard::B) {
					znak = 'b';
				}else if (event.key.code == sf::Keyboard::L) {
					//std::cout << "ok" << std::endl;
					znak = 'l';
				}else if (event.key.code == sf::Keyboard::R) {
					znak = 'r';
				}else if (event.key.code == sf::Keyboard::A) {
					znak = 'a';
				}else if (event.key.code == sf::Keyboard::C) {
					znak = 'c';
				}else if (event.key.code == sf::Keyboard::W) {
					znak = 'w';
					bufor.copyToImage().saveToFile("obraz.png");
					//std::cout << "dziala" << std::endl;
					break;
				}else if (event.key.code == sf::Keyboard::O) {
					znak = 'o';
					bufor.loadFromFile("obraz.png");
					//std::cout << "dziala" << std::endl;
					break;
				}else if (event.key.code == sf::Keyboard::Escape) {
					window.close();
					//std::cout << "ok" << std::endl;
				}else if (event.key.code == sf::Keyboard::V) {
					znak = 'v';
					//std::cout << "ok" << std::endl;
				}
			}
		}

		window.draw(sprite);

		if (mouse_flag) {
			switch (znak) {
			case 'f':
				if (sf::Mouse::getPosition(window).y < 60) {
					color = cl_bar.getPixel(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
				}
				znak = ' ';
				break;

			case 'b': 
				if (sf::Mouse::getPosition(window).y < 60) {
					fill_color = cl_bar.getPixel(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
				}
				//std::cout << fill_color.a << fill_color.b << fill_color.g << fill_color.r << std::endl;
				znak = ' ';
				break;
			
			case 'l': 
				linia[0].position = sf::Vector2f(mouse_x,mouse_y);
				linia[0].color = color;
				linia[1].position=sf::Vector2f(static_cast<float>(sf::Mouse::getPosition(window).x), static_cast<float>(sf::Mouse::getPosition(window).y));
				linia[1].color = fill_color;

				window.draw(linia);
				break;
			
			case 'r':
				prostokat.setPosition(sf::Vector2f(mouse_x, mouse_y));
				prostokat.setSize(sf::Vector2f(static_cast<float>(sf::Mouse::getPosition(window).x - mouse_x), static_cast<float>(sf::Mouse::getPosition(window).y - mouse_y)));
				prostokat.setOutlineColor(color);
				prostokat.setFillColor(sf::Color::Transparent);
				prostokat.setOutlineThickness((float)1.5);
				
				window.draw(prostokat);
				break;
			
			case 'a':
				prostokat.setPosition(sf::Vector2f(mouse_x, mouse_y));
				prostokat.setSize(sf::Vector2f(static_cast<float>(sf::Mouse::getPosition(window).x - mouse_x), static_cast<float>(sf::Mouse::getPosition(window).y - mouse_y)));
				prostokat.setOutlineColor(color);
				prostokat.setFillColor(fill_color);
				prostokat.setOutlineThickness((float)1.5);

				window.draw(prostokat);
				break;
			
			case 'c': 
				kolko.setPosition(sf::Vector2f(mouse_x, mouse_y));
				kolko.setRadius(sqrt(static_cast<float>((sf::Mouse::getPosition(window).x - mouse_x)*(sf::Mouse::getPosition(window).x - mouse_x) + (sf::Mouse::getPosition(window).y - mouse_y)*(sf::Mouse::getPosition(window).y - mouse_y))));
				kolko.setOutlineColor(color);
				kolko.setOutlineThickness(1.5);
				kolko.setFillColor(sf::Color::Transparent);
				window.draw(kolko);
				break;

			case 'v':
				kolko.setPosition(sf::Vector2f(mouse_x, mouse_y));
				kolko.setRadius(sqrt(static_cast<float>((sf::Mouse::getPosition(window).x - mouse_x)*(sf::Mouse::getPosition(window).x - mouse_x) + (sf::Mouse::getPosition(window).y - mouse_y)*(sf::Mouse::getPosition(window).y - mouse_y))));
				kolko.setOutlineColor(color);
				kolko.setOutlineThickness((float)1.5);
				kolko.setFillColor(fill_color);
				window.draw(kolko);
				break;
			}
		}

		blackbar2.setSize(sf::Vector2f(800, 60));
		blackbar2.setFillColor(sf::Color::Black);
		blackbar2.setOutlineColor(sf::Color::Transparent);
		blackbar2.setPosition(sf::Vector2f(0, 0));
		window.draw(blackbar2);

		color_bar.setSize(sf::Vector2f(35, 30));
		color_bar.setFillColor(color);
		color_bar.setOutlineThickness(0.0);
		color_bar.setPosition(765, 1);
		window.draw(color_bar);

		fill_color_bar.setSize(sf::Vector2f(35, 30));
		fill_color_bar.setFillColor(fill_color);
		fill_color_bar.setOutlineThickness(0.0);
		fill_color_bar.setPosition(765, 30);
		window.draw(fill_color_bar);

		blackbar.setSize(sf::Vector2f(800, 50));
		blackbar.setFillColor(sf::Color::Black);
		blackbar.setOutlineColor(sf::Color::Transparent);
		blackbar.setPosition(sf::Vector2f(1, 600));
		window.draw(blackbar);
		
		text->setPosition(sf::Vector2f(710, 610));
		text->setString(znak);
		window.draw(*text);

		obraz.update(window);
		window.draw(menu);
		window.display();
	}
	return 0;
}