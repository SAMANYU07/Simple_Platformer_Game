#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include "player.h"
#include <time.h>
#include <random>
#include "AnimateSprite.h"
#include "platform.h"
#include "Particle.h"
#define P_IDLE 0
#define P_RUNNING 1
#define P_JUMPING 2

void gravity(player &p)
{
	if (!p.body.getGlobalBounds().intersects(platformArr[0].rect.getGlobalBounds()) &&
		!p.body.getGlobalBounds().intersects(platformArr[1].rect.getGlobalBounds()) &&
		!p.body.getGlobalBounds().intersects(platformArr[2].rect.getGlobalBounds()) &&
		!p.body.getGlobalBounds().intersects(platformArr[3].rect.getGlobalBounds())
		)
		p.body.move(0, 1);
}

float randomSpeed()
{
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_real_distribution<float> distribution(-0.2, -0.1);
	float random_number = distribution(generator);
	return random_number;
}

Particle* ParticleArray[10];

void particleInit(Particle& p)
{
	p.speed = randomSpeed();
	p.body.setPosition(rand() % 1920, rand() % 200);
}

void particleGenerator(Particle& p)
{
	if (p.body.getPosition().x < -100)
		p.body.setPosition(1920 + rand() % 200, rand() % 200);
	p.body.move(p.speed, 0);
}


int main()
{
	sf::RenderWindow win(sf::VideoMode(1920, 1080), "Game", sf::Style::Close | sf::Style::Fullscreen);
	player p;
	platform plt;
	platformInit();
	for (int i = 0; i < 10; i++)
	{
		float rs = randomSpeed();
		ParticleArray[i] = new Particle(rs);
		particleInit(*ParticleArray[i]);
	}
	sf::Clock initial_clock;
	float plt_speed = -0.4;
	bool stop = false;
	srand(static_cast<unsigned int>(time(0)));
	AnimateSprite anim;
	while (win.isOpen())
	{
		sf::Event evt;
		while (win.pollEvent(evt))
		{
			if (evt.type == sf::Event::Closed)
			{
				win.close();
				exit(EXIT_SUCCESS);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			win.close();
			exit(EXIT_SUCCESS);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
			p.body.setPosition(100, 100);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			p.body.move(1, 0);
			anim.animate(p.state ,p.body, 4096, p.xToAnimate, p.yToAnimate, p.rectWidth, p.rectHeight);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			p.body.move(-1, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			stop = !stop;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			if (!p.JUMP_STATE && (p.body.getGlobalBounds().intersects(platformArr[0].rect.getGlobalBounds()) ||
				p.body.getGlobalBounds().intersects(platformArr[1].rect.getGlobalBounds()) ||
				p.body.getGlobalBounds().intersects(platformArr[2].rect.getGlobalBounds()) ||
				p.body.getGlobalBounds().intersects(platformArr[3].rect.getGlobalBounds())
				))
			{
				p.jump();
				p.state = P_JUMPING;
			}
		}
		if (!p.JUMP_STATE && (p.body.getGlobalBounds().intersects(platformArr[0].rect.getGlobalBounds()) ||
			p.body.getGlobalBounds().intersects(platformArr[1].rect.getGlobalBounds()) ||
			p.body.getGlobalBounds().intersects(platformArr[2].rect.getGlobalBounds()) ||
			p.body.getGlobalBounds().intersects(platformArr[3].rect.getGlobalBounds())
			))
			p.state = P_RUNNING;
		anim.animate(p.state, p.body, p.totalRowSize, p.xToAnimate, p.yToAnimate, p.rectWidth, p.rectHeight);
		p.check_jump();
		win.clear(sf::Color(135, 206, 235, 1));
		win.draw(p.body);
		win.draw(platformArr[0].rect);
		win.draw(platformArr[1].rect);
		win.draw(platformArr[2].rect);
		win.draw(platformArr[3].rect);
		for (int i = 0; i < 10; i++)
		{
			particleGenerator(*ParticleArray[i]);
			win.draw(ParticleArray[i]->body);
		}
		gravity(p);
		if (!stop)
		platformGenerator(initial_clock, plt_speed, p);
		win.display();
	}
}