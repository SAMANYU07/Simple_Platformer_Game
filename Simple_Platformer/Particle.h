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

Particle* ParticleArray[10];

float randomSpeed()
{
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_real_distribution<float> distribution(-32, -16);
	float random_number = distribution(generator);
	return random_number;
}

void particleInit(Particle& p)
{
	p.speed = randomSpeed();
	p.body.setPosition(rand() % 1920, rand() % 700);
}

void particleGenerator(Particle& p, float deltaTime)
{
	if (p.body.getPosition().x < -100)
		p.body.setPosition(1920 + rand() % 200, rand() % 700);
	p.body.move(p.speed * deltaTime, 0);
}