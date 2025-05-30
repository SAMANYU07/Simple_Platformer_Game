#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "AnimateSprite.h"
#define P_IDLE 0
#define P_RUNNING 1
#define P_JUMPING 2
#define P_BLOCKING 3

class player
{
public:
	bool JUMP_STATE = false, JUMP_GOING_UP = false, JUMP_FALLING = false, BLOCK_STATE = false;
	sf::Clock jump_clock, block_clock;
	//sf::RectangleShape body;
	sf::Sprite body;
	sf::Texture texture;
	int totalRowSize = 2400, state = P_RUNNING, xToAnimate = 0, yToAnimate = 0, rectWidth = 300, rectHeight = 300;
	player()
	{
		if (!texture.loadFromFile("sprites/player3E2.png"))
			std::cout << "unable to load player3E.png\n";
		body.setTexture(texture);
		body.setTextureRect(sf::IntRect(0, 0, 300, 300));
		body.setScale(0.6, 0.6);
		body.setOrigin(100*0.25, 100 * 0.25);
		//body.setScale(0.7, 0.8);
		//body.setOrigin(311.3 * 0.25, 311.3 * 0.25);
		body.setPosition(200, 200);
		//this->body.setSize(sf::Vector2f(100, 100));
		//this->body.setFillColor(sf::Color::Black);
		//this->body.setOrigin(50, 50);
	}
	void jump()
	{
		if (!this->JUMP_STATE)
		{
			this->jump_clock.restart();
			this->JUMP_STATE = true;
		}
	}
	void check_jump(float deltaTime)
	{
		if (this->JUMP_STATE && this->jump_clock.getElapsedTime().asMilliseconds() >= 200)
			this->JUMP_STATE = false;
		else if (this->JUMP_STATE && this->jump_clock.getElapsedTime().asMilliseconds() < 400)
			this->body.move(0, -2800 * deltaTime);
	}
	void block()
	{
		if (!this->BLOCK_STATE)
		{
			this->BLOCK_STATE = true;
			this->block_clock.restart();
		}
	}
	void check_block()
	{
		if (this->BLOCK_STATE && this->block_clock.getElapsedTime().asMilliseconds() >= 1000)
			this->BLOCK_STATE = false;
		else if (this->BLOCK_STATE && this->block_clock.getElapsedTime().asMilliseconds() < 1000)
			yToAnimate = 200;
	}
};