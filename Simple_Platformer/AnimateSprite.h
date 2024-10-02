#pragma once
#include <SFML/Graphics.hpp>
#include "player.h"
#include "Crow.h"

#define P_IDLE 0
#define P_RUNNING 1
#define P_JUMPING 2
#define P_BLOCKING 3

class AnimateSprite
{
public:
	sf::Clock c1;
	void animate(int state ,sf::Sprite& sprite, int rowTotalSize, int& xToAnimate, int yToAnimate, int rectWidth, int rectHeight)
	{
		if (state == P_JUMPING)
			yToAnimate = 300;
		else if (state == P_BLOCKING)
			yToAnimate = 600;
		else
			yToAnimate = 0;
		sprite.setTextureRect(sf::IntRect(xToAnimate, yToAnimate, rectWidth, rectHeight));
		if (xToAnimate >= rowTotalSize)
			xToAnimate = 0;
		if (state == P_RUNNING && this->c1.getElapsedTime().asSeconds() >= 0.06)
		{
			xToAnimate += rectWidth;
			this->c1.restart();
		}
		else if (state == P_JUMPING && this->c1.getElapsedTime().asSeconds() >= 0.1)
		{
			xToAnimate += rectWidth;
			this->c1.restart();
		}
		else if (state == P_BLOCKING && this->c1.getElapsedTime().asSeconds() >= 0.1)
		{
			if (xToAnimate == rowTotalSize - rectWidth)
				state = P_RUNNING;
			xToAnimate += rectWidth;
			this->c1.restart();
		}
	}
	void animteCrow(sf::Sprite& sprite, sf::Clock &clock, int rowTotalSize, int& xToAnimate, int yToAnimate, int rectWidth, int rectHeight)
	{
		if (xToAnimate >= rowTotalSize - rectWidth)
			xToAnimate = 44;
		if (clock.getElapsedTime().asMilliseconds() >= 50)
		{
			xToAnimate += rectWidth + (2*45);
			sprite.setTextureRect(sf::IntRect(xToAnimate, 0, rectWidth, rectHeight));
			clock.restart();
		}
	}
};

//struct player
//{
//	sf::Sprite sprite;
//	sf::Texture texture;
//	int rowSizeArr[4];
//	int rectWidth, rectHeight, yToAnimate, xToAnimate;
//	player() : rowSizeArr{ 32, 64, 16, 16 }
//	{
//		sprite.setScale(4, 4);
//		if (!texture.loadFromFile("robot.png"))
//		{
//			std::cout << "unable to open file\n";
//			exit(EXIT_FAILURE);
//		}
//		sprite.setTexture(texture);
//		sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
//		sprite.setPosition(100, 100);
//		rectWidth = 16, rectHeight = 16, xToAnimate = 0, yToAnimate = 0;
//	}
//};