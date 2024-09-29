#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <time.h>

class Particle
{
public:
	sf::RectangleShape body;
	sf::Texture texture;
	float speed = 0;
	Particle(float &speed): speed(speed)
	{
		if (!texture.loadFromFile("sprites/particle1.png"))
			std::cout << "unable to load particle1.png\n";
		this->body.setTexture(&texture);
		this->body.setSize(sf::Vector2f(100, 100));
		this->body.setScale(2, 1);
	}
};