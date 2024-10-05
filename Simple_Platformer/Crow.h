#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <random>

class Crow
{
public:
	sf::Sprite body;
	sf::Texture tex;
	sf::Clock crowClock;
	int totalRowSize = 4200, xToAnimate = 44, yToAnimate = 64, rectWidth = 207, rectHeight = 265;
	bool deflected = false;
	Crow()
	{
		if (!tex.loadFromFile("sprites/crowE2.png"))
			std::cout << "Unable to load crowE1.png\n";
		this->body.setTexture(tex);
		this->body.setPosition(1920, 600);
		this->body.setScale(0.5, 0.5);
		//this->body.setColor(sf::Color::Blue);
		this->xToAnimate = 0;
		srand(time(0));
	}
	void spawn()
	{
		if (this->body.getPosition().x < 0)
			this->body.setPosition(2400 + rand() % 500, rand() % 500);
		this->body.move(-1, 0);
	}
};