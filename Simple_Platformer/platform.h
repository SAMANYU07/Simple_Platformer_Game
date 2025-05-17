#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "player.h"

struct platform
{
	sf::RectangleShape rect;
	sf::Texture tex;
	int width;
	platform* nextPlatform;
	platform* prevPlatform;
	platform()
	{
		if (!tex.loadFromFile("sprites/mud3.png"))
			std::cout << "unable to load textures\n";
		tex.setRepeated(true);
		rect.setTexture(&tex);
		//rect.setSize(sf::Vector2f(400, 100));
		//rect.setFillColor(sf::Color::Green);
	}
};

platform platformArr[4];

void platformInit()
{
	platformArr[0].width = 800;
	platformArr[1].width = 1200;
	platformArr[2].width = 2000;
	platformArr[3].width = 400;
	for (int i = 0; i < 4; ++i)
	{
		platformArr[i].rect.setSize(sf::Vector2f(platformArr[i].width, 100));
		platformArr[i].rect.setTextureRect(sf::IntRect(0, 0, platformArr[i].width, 100));
	}
	platformArr[0].rect.setPosition(0, 800);
	platformArr[1].rect.setPosition(950, 806);
	platformArr[2].rect.setPosition(1900, 812);
	platformArr[3].rect.setPosition(2850, 818);
	platformArr[0].nextPlatform = &platformArr[1];
	platformArr[1].nextPlatform = &platformArr[2];
	platformArr[2].nextPlatform = &platformArr[3];
	platformArr[3].nextPlatform = &platformArr[0];
	platformArr[0].prevPlatform = &platformArr[3];
	platformArr[1].prevPlatform = &platformArr[0];
	platformArr[2].prevPlatform = &platformArr[1];
	platformArr[3].prevPlatform = &platformArr[2];
}

void platformGenerator(sf::Clock& clock, float& speed, player& p, float deltaTime)
{
	for (int i = 0; i < 4; i++)
	{
		if (platformArr[i].rect.getPosition().x < -platformArr[i].width)
			platformArr[i].rect.setPosition(platformArr[i].prevPlatform->rect.getPosition().x + (platformArr[i].prevPlatform->width + 700 + rand() % 251), (780 + rand() % 60));
	}
	if (clock.getElapsedTime().asSeconds() >= 10)
	{
		speed -= 0.1;
		clock.restart();
	}
	platformArr[0].rect.move(speed * deltaTime, 0);
	platformArr[1].rect.move(speed * deltaTime, 0);
	platformArr[2].rect.move(speed * deltaTime, 0);
	platformArr[3].rect.move(speed * deltaTime, 0);
	//p.body.rotate(speed * -1);
}