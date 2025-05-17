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
	int totalRowSize = 1400, xToAnimate = 0, yToAnimate = 0, rectWidth = 100, rectHeight = 100;
	bool deflected = false, dead = false;
	Crow()
	{
		if (!tex.loadFromFile("sprites/crowE3.png"))
			std::cout << "Unable to load crowE1.png\n";
		this->body.setTexture(tex);
		this->body.setPosition(1920, 600);
		this->body.setScale(1, 1);
		//this->body.setColor(sf::Color::Blue);
		this->xToAnimate = 0;
		srand(time(0));
	}
	void spawn(float deltaTime)
	{
		if (!this->dead && this->body.getPosition().x < 0)
			this->body.setPosition(2400 + rand() % 500, rand() % 500);
		else if (this->dead && this->body.getPosition().x < 0)
		{
			this->dead = false;
			this->yToAnimate = 0;
		}
		this->body.move(-2000 * deltaTime, 0);
	}
};