#include<iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "font.h"

using namespace std;

void draw_to_color_pixels(sf::Uint8 *color_pixels, unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b, unsigned char alfa, int size)
{
	color_pixels[4 * (y * size + x) + 0] = r;
	color_pixels[4 * (y * size + x) + 1] = g;
	color_pixels[4 * (y * size + x) + 2] = b;
	color_pixels[4 * (y * size + x) + 3] = alfa;
}

float converter(float a, float tmp1, float tmp2) {

	if (a > 1) {
		a -= 1;
	}
	if (a < 0) {
		a += 1;
	}

	if (6 * a < 1) {
		a = tmp2 + 6 * a * (tmp1 - tmp2);
	}
	else if (2 * a < 1) {
		a = tmp1;
	}
	else if (1.5 * a < 1) {
		a = tmp2 + 6 * (tmp1 - tmp2) * (0.66666 - a);
	}
	else {
		a = tmp2;
	}
	return a;
}

float r_val(int i, float tmp1, float tmp2, float tmp3 , float v) {
	if (i == 0 || i == 5) {
		return v;
	}
	else if (i == 1) {
		return tmp2;
	}
	else if (i == 2 || i == 3) {
		return tmp1;
	}
	else if (i == 4) {
		return tmp3;
	}
}

float g_val(int i, float tmp1, float tmp2, float tmp3, float v) {
	if (i == 0) {
		return tmp3;
	}
	else if (i == 1 || i== 2) {
		return v;
	}
	else if (i == 3) {
		return tmp2;
	}
	else if (i == 4 || i == 5) {
		return tmp1;
	}
}

float b_val(int i, float tmp1, float tmp2, float tmp3, float v) {
	if (i == 0 || i == 1) {
		return tmp1;
	}
	else if (i == 2) {
		return tmp3;
	}
	else if (i == 3 || i == 4) {
		return v;
	}
	else {
		return tmp2;
	}
}

void R_G_B(sf::Uint8 *color_pixels,int size, float x, bool flag) {

	float radius, rad = size / 2, alfa, cosine;

	for (int i = 0; i < size; i++) {

		for (int j = 0; j < size; j++) {

			radius = static_cast<float> (sqrt(pow(j - rad, 2) + pow(rad - i, 2)));
			cosine = static_cast<float>((j - rad) / radius);

			if (i > rad) {
				cosine = -cosine;
			}

			alfa = static_cast<float> (acos(cosine) * 180 / 3.14);

			if (i > rad) {
				alfa += 180;
			}

			if (alfa > 360) {
				alfa = 360;
			}

			if (alfa < 0) {
				alfa = 0;
			}

			if (flag) {
				draw_to_color_pixels(color_pixels, j, i, static_cast<int> (radius / rad * 255), static_cast<int> ((alfa / 360.0) * 255), static_cast<int> (x * 255), 255, size);

				if (radius > rad) {
					draw_to_color_pixels(color_pixels, j, i, static_cast<int> (radius / rad * 255), static_cast<int> (alfa * 255), static_cast<int> (x * 255), 0, size);
				}
			}
			else {
				draw_to_color_pixels(color_pixels, j, i, static_cast<int> (radius / rad * 255), static_cast<int> ((alfa / 360.0) * 255), static_cast<int> (x * 255), 255, size);

				if (radius > rad) {
					draw_to_color_pixels(color_pixels, j, i, static_cast<int> (radius / rad * 255), static_cast<int> (alfa * 255), static_cast<int> (x * 255), 0, size);
				}
			}
		}
	}
}

void C_M_Y(sf::Uint8 *color_pixels, int size, float x, bool flag) {
	
	float radius, rad = size / 2, alfa, cosine;

	for (int i = 0; i < size; i++) {

		for (int j = 0; j < size; j++) {

			radius = static_cast<float> (sqrt(pow(j - rad, 2) + pow(rad - i, 2)));
			cosine = (static_cast<float> (j - rad) / radius);

			if (i > rad) {
				cosine = -cosine;
			}

			alfa = static_cast<float> (acos(cosine) * 180 / 3.14);

			if (i > rad) {
				alfa += 180;
			}

			if (alfa > 360) {
				alfa = 360;
			}

			if (alfa < 0) {
				alfa = 0;
			}
			
			if (flag) {
				draw_to_color_pixels(color_pixels, j, i, 255 - static_cast<int> (radius / rad * 255), 255 - static_cast<int> ((alfa / 360.0) * 255), 255 - static_cast<int> (x * 255), 255, size);

				if (radius > rad) {
					draw_to_color_pixels(color_pixels, j, i, static_cast<int> (radius / rad * 255), static_cast<int> (alfa * 255), static_cast<int> (x * 255), 0, size);
				}
			}
			else {
				draw_to_color_pixels(color_pixels, j, i, 255 - static_cast<int> (radius / rad * 255), 255 - static_cast<int> ((alfa / 360.0) * 255), 255 - static_cast<int> (x * 255), 255, size);

				if (radius > rad) {
					draw_to_color_pixels(color_pixels, j, i, static_cast<int> (radius / rad * 255), static_cast<int> (alfa * 255), static_cast<int> (x * 255), 0, size);
				}
			}
		}
	}
}

void H_S_L(sf::Uint8 *color_pixels,int size, float x, bool flag) {
	float radius, rad = size / 2, alfa, cosine;
	float r, g, b, h, s, l;
	float tmp1, tmp2;
	 
	for (int i = 0; i < size; i++) {

		for (int j = 0; j < size; j++) {
			radius = static_cast<float> (sqrt(pow(j - rad, 2) + pow(rad - i, 2)));
			cosine = (static_cast<float> (j - rad) / radius);

			if (i > rad) {
				cosine = -cosine;
			}

			alfa = static_cast<float> (acos(cosine) * 180 / 3.14);

			if (i > rad) {
				alfa += 180;
			}

			if (alfa > 360) {
				alfa = 360;
			}

			if (alfa < 0) {
				alfa = 0;
			}
			
			h = alfa / 360;
			s = radius / rad;
			l = x;
			
			if (s == 0) {
				r = 255 * l; 
				g = 255 * l; 
				b = 255 * l;
			}
			else if (l < 0.5) {
				tmp1 = l * (s + 1);
			}
			else {
				tmp1 = l + s - l * s;
			}
				
			tmp2 = 2 * l - tmp1;
			
			r = h + 0.33333;
			g = h;
			b = h - 0.33333;
			
			r = converter(r, tmp1, tmp2);
			g = converter(g, tmp1, tmp2);
			b = converter(b, tmp1, tmp2);

			if (flag) {
				draw_to_color_pixels(color_pixels, j, i, static_cast<int> (r * 255), static_cast<int> (g * 255), static_cast<int> (b * 255), 255, size);
				if (radius > rad) {
					draw_to_color_pixels(color_pixels, j, i, static_cast<int> (r * 255), static_cast<int> (g * 255), static_cast<int> (b * 255), 0, size);
				}

			}
			else {
				draw_to_color_pixels(color_pixels, j, i, static_cast<int> (r * 255), static_cast<int> (g * 255), static_cast<int> (b * 255), 255, size);

				if (r > rad) {
					draw_to_color_pixels(color_pixels, j, i, static_cast<int> (r * 255), static_cast<int> (g * 255), static_cast<int> (b * 255), 0, size);
				}
			}
							
		}
	}
}

void H_S_V(sf::Uint8 *color_pixels,int size, float x, bool flag) {
	float radius, rad = size / 2, alfa, cosine;
	float tmp1, tmp2, tmp3, tmp_h, tmp_int;
	float r, g, b, h, s, v;

	for (int i = 0; i < size; i++) {

		for (int j = 0; j < size; j++) {
			radius = static_cast<float> (sqrt(pow(j - rad, 2) + pow(rad - i, 2)));
			cosine = (static_cast<float> (j - rad) / radius);
			if (i > rad) {
				cosine = -cosine;
			}

			alfa = static_cast<float> (acos(cosine) * 180 / 3.14);

			if (i > rad) {
				alfa += 180;
			}

			if (alfa > 360) {
				alfa = 360;
			}

			if (alfa < 0) {
				alfa = 0;
			}

			h = alfa / 360;
			s = radius / rad;
			v = x;

			if (s == 0) {
				r = - v * 255;
				g = - v * 255;
				b = - v * 255;
			}
			else {

				tmp_h = h * 6;
				if (tmp_h == 6) {
					tmp_h = 0;
				}

				tmp_int = static_cast<int>(tmp_h);
				tmp1 = v * (1 - s);
				tmp2 = v * (1 - s * (tmp_h - tmp_int));
				tmp3 = v * (1 - s * (1 - (tmp_h - tmp_int)));
				
				r = r_val(tmp_int, tmp1, tmp2, tmp3, v);
				g = g_val(tmp_int, tmp1, tmp2, tmp3, v);
				b = b_val(tmp_int, tmp1, tmp2, tmp3, v);
				
			}

			if (flag) {
				draw_to_color_pixels(color_pixels, j, i, static_cast<int> (r * 255), static_cast<int> (g * 255), static_cast<int> (b * 255), 255, size);
				if (radius > rad) {
					draw_to_color_pixels(color_pixels, j, i, static_cast<int> (r * 255), static_cast<int> (g * 255), static_cast<int> (b * 255), 0, size);
				}					
			}
			else {
				draw_to_color_pixels(color_pixels, j, i, static_cast<int> (r * 255), static_cast<int> (g * 255), static_cast<int> (b * 255), 255, size);

				if (radius > rad) {
					draw_to_color_pixels(color_pixels, j, i, static_cast<int> (r * 255), static_cast<int> (g * 255), static_cast<int> (b * 255), 0, size);
				}
			}
		}
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 650), "GFK Lab 02", sf::Style::Titlebar | sf::Style::Close);
	sf::Clock clock;
	sf::Time time = sf::Time::Zero;
	unsigned int FPS = 0 , frame_counter = 0;

	sf::Font font;
	sf::Text *text1, *text2, *text3, *text4, *text5, *text6, *text7, *text8, *text9, *text10, *text11, *text12, *text13, *text14;
	font.loadFromMemory(font_data, font_data_size);

	text1 = new sf::Text;
	text1->setFont(font);
	text1->setCharacterSize(12);
	text1->setFillColor(sf::Color::Black);

	text1->setPosition(675, 320);
	text1->setString("FPS = ");


	text2 = new sf::Text;
	text2->setFont(font);
	text2->setCharacterSize(12);
	text2->setFillColor(sf::Color::Black);

	text2->setPosition(10, 10);
	text2->setString("HSL");
	

	text3 = new sf::Text;
	text3->setFont(font);
	text3->setCharacterSize(12);
	text3->setFillColor(sf::Color::Black);

	text3->setPosition(350, 10);
	text3->setString("HSV");
	

	text4 = new sf::Text;
	text4->setFont(font);
	text4->setCharacterSize(12);
	text4->setFillColor(sf::Color::Black);

	text4->setPosition(10, 350);
	text4->setString("CMY");
	

	text5 = new sf::Text;
	text5->setFont(font);
	text5->setCharacterSize(12);
	text5->setFillColor(sf::Color::Black);

	text5->setPosition(350, 350);
	text5->setString("RGB");

	text6 = new sf::Text;
	text6->setFont(font);
	text6->setCharacterSize(12);
	text6->setFillColor(sf::Color::Black);

	text6->setPosition(710, 320);

	text7 = new sf::Text;
	text7->setFont(font);
	text7->setCharacterSize(12);
	text7->setFillColor(sf::Color::Black);

	text7->setPosition(10, 300);
	text7->setString("L = ");

	text8 = new sf::Text;
	text8->setFont(font);
	text8->setCharacterSize(12);
	text8->setFillColor(sf::Color::Black);

	text8->setPosition(350, 300);
	text8->setString("V = ");

	text9 = new sf::Text;
	text9->setFont(font);
	text9->setCharacterSize(12);
	text9->setFillColor(sf::Color::Black);

	text9->setPosition(10, 630);
	text9->setString("Y = ");

	text10 = new sf::Text;
	text10->setFont(font);
	text10->setCharacterSize(12);
	text10->setFillColor(sf::Color::Black);

	text10->setPosition(350, 630);
	text10->setString("B = ");

	text11 = new sf::Text;
	text11->setFont(font);
	text11->setCharacterSize(12);
	text11->setFillColor(sf::Color::Black);

	text11->setPosition(35, 300);
	

	text12 = new sf::Text;
	text12->setFont(font);
	text12->setCharacterSize(12);
	text12->setFillColor(sf::Color::Black);

	text12->setPosition(375, 300);
	

	text13 = new sf::Text;
	text13->setFont(font);
	text13->setCharacterSize(12);
	text13->setFillColor(sf::Color::Black);

	text13->setPosition(35, 630);
	

	text14 = new sf::Text;
	text14->setFont(font);
	text14->setCharacterSize(12);
	text14->setFillColor(sf::Color::Black);

	text14->setPosition(375, 630);
	

	bool mouse_flag = false;
	float mouse_x, mouse_y;

	sf::RectangleShape bar;

	sf::Vertex changer_bar[4];
	changer_bar[0] = sf::Vertex(sf::Vector2f(675, 10), sf::Color::Black);
	changer_bar[1] = sf::Vertex(sf::Vector2f(675, 310), sf::Color::White);
	changer_bar[2] = sf::Vertex(sf::Vector2f(725, 310), sf::Color::White);
	changer_bar[3] = sf::Vertex(sf::Vector2f(725, 10), sf::Color::Black);

	window.clear(sf::Color::White);
	bar.setSize(sf::Vector2f(60, 2));
	bar.setPosition(sf::Vector2f(670,160));
	bar.setFillColor(sf::Color::Black);
	window.draw(changer_bar, 4, sf::Quads);
	

	sf::Image img, RGB_img, CMY_img, HSL_img, HSV_img;
	sf::Texture bufor;
	sf::Texture texture;
	sf::Sprite sprite;
	bufor.create(800, 650);
	texture.create(800, 650);
	sprite.setTexture(bufor);

	texture.update(window);
	img.create(800, 650);
	img = texture.copyToImage();

	sf::Color change = img.getPixel(700, 160);
	float x = change.b;
	//cout << x << change.b << change.g << change.r<<endl;

	int rad = 250;

	sf::Uint8 *RGB_colors = new sf::Uint8[rad * rad * 4];
	R_G_B(RGB_colors, rad, static_cast<float>(change.b) / 255, false);
	R_G_B(RGB_colors, rad, static_cast<float>(change.b) / 255, true);
	RGB_img.create(rad, rad, RGB_colors);

	sf::Uint8 *CMY_colors = new sf::Uint8[rad * rad * 4];
	C_M_Y(CMY_colors, rad, static_cast<float>(change.b) / 255, false);
	C_M_Y(CMY_colors, rad, static_cast<float>(change.b) / 255, true);
	CMY_img.create(rad, rad, CMY_colors);

	sf::Uint8 *HSL_colors = new sf::Uint8[rad * rad * 4];
	H_S_L(HSL_colors, rad, static_cast<float>(change.b) / 255, false);
	H_S_L(HSL_colors, rad, static_cast<float>(change.b) / 255, true);
	HSL_img.create(rad, rad, HSL_colors);

	sf::Uint8 *HSV_colors = new sf::Uint8[rad * rad * 4];
	H_S_V(HSV_colors, rad, static_cast<float>(change.b) / 255, false);
	H_S_V(HSV_colors, rad, static_cast<float>(change.b) / 255, true);
	HSV_img.create(rad, rad, HSV_colors);
	
	
	//inicjalizacja 
	clock.restart().asMilliseconds();
	while (window.isOpen())
	{
		sf::Event event;
		window.clear(sf::Color::White);

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::MouseButtonPressed) {
				//cout << "dziala" << endl;
				mouse_flag = true;
				
			}
			if (event.type == sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
				mouse_flag = true;
				mouse_x = sf::Mouse::getPosition(window).x;
				mouse_y = sf::Mouse::getPosition(window).y;

			}
			
			else if (event.type == sf::Event::MouseButtonReleased) {
				mouse_flag = false;
			}
	
		}
		//tu wyrysować wszystko na ekran
		if (mouse_flag) {
			//cout << "dziala2" << endl;
			mouse_x = sf::Mouse::getPosition(window).x;
			mouse_y = sf::Mouse::getPosition(window).y;
			if (mouse_x >= 675 && mouse_x <= 725 && mouse_y >= 10 && mouse_y <= 310) {
				bufor.update(texture.copyToImage());
				bar.setPosition(sf::Vector2f(670, mouse_y));
				change = img.getPixel(mouse_x, mouse_y);
				x = change.b;
				//cout << x << endl;
			}

			R_G_B(RGB_colors, rad, -x, true);
			RGB_img.create(rad, rad, RGB_colors);

			H_S_L(HSL_colors, rad, static_cast<float>( x / 255), true);
			HSL_img.create(rad, rad, HSL_colors);
			
			H_S_V(HSV_colors, rad, static_cast<float>( x / 255), true);
			HSV_img.create(rad, rad, HSV_colors);
		
			C_M_Y(CMY_colors, rad, -x, true);
			CMY_img.create(rad, rad, CMY_colors);
		
		}
		
		bufor.update(HSL_img);
		sprite.setPosition(25, 25);
		window.draw(sprite);
		
		bufor.update(HSV_img);
		sprite.setPosition(350, 25);
		window.draw(sprite);
		
		bufor.update(CMY_img);
		sprite.setPosition(25, 350);
		window.draw(sprite);
		
		bufor.update(RGB_img);
		sprite.setPosition(350, 350);
		window.draw(sprite);

		//tu wypisać na ekran wartość FPS
		if (clock.getElapsedTime().asSeconds() >= 1.0f)
		{
			FPS = (unsigned int)((float)frame_counter / clock.getElapsedTime().asSeconds());
			clock.restart();
			frame_counter = 0;
		}
		
		//cout << FPS << endl;
		frame_counter++;
		window.draw(*text1);
		window.draw(*text2);
		window.draw(*text3);
		window.draw(*text4);
		window.draw(*text5);
		text6->setString(to_string(FPS));
		window.draw(*text6);
		window.draw(*text7);
		window.draw(*text8);
		window.draw(*text9);
		window.draw(*text10);
		text11->setString(to_string(x/255));
		text12->setString(to_string(x/255));
		text13->setString(to_string(static_cast<int>(x / 255 * 100)) + " %");
		text14->setString(to_string(static_cast<int>(x)));
		window.draw(*text11);
		window.draw(*text12);
		window.draw(*text13);
		window.draw(*text14);
		window.draw(changer_bar, 4, sf::Quads);
		window.draw(bar);
		window.display();
	}
}