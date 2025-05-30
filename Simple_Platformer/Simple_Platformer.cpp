#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <SFML/OpenGL.hpp>
#include "player.h"
#include <time.h>
#include <random>
#include <sstream>
#include "AnimateSprite.h"
#include "platform.h"
#include "Particle.h"
#include "GUI.h"
#include "Crow.h"
#include "Projectile.h"
#define P_IDLE 0
#define P_RUNNING 1
#define P_JUMPING 2
#define P_BLOCKING 3

void gravity(player &p, float deltaTime)
{
	if (!p.body.getGlobalBounds().intersects(platformArr[0].rect.getGlobalBounds()) &&
		!p.body.getGlobalBounds().intersects(platformArr[1].rect.getGlobalBounds()) &&
		!p.body.getGlobalBounds().intersects(platformArr[2].rect.getGlobalBounds()) &&
		!p.body.getGlobalBounds().intersects(platformArr[3].rect.getGlobalBounds())
		)
		p.body.move(0, 1400 * deltaTime);
}

void gameOverCheck(player &p, sf::RenderWindow &win, bool &gameOver, GUI &gui, Crow &crow)
{
	if ((p.body.getPosition().x == -100 || p.body.getPosition().y > win.getSize().y) || (p.body.getGlobalBounds().intersects(crow.body.getGlobalBounds()) && p.state != P_BLOCKING && (!crow.dead && !crow.deflected)))
	{
		if (gui.score > gui.highScore)
		{
			gui.highScore = gui.score;
			gui.sst << gui.highScore;
			gui.sst >> gui.tempscr;
			gui.sst.str("");
			gui.sst.clear();
			gui.gameOverText.setString("GAME OVER \nPress 'Backspace' to Restart\nHighScore: " + gui.tempscr);
		}
		gameOver = true;
	}
}

int main()
{
	sf::RenderWindow win(sf::VideoMode(1920, 1080), "Game", sf::Style::Close | sf::Style::Fullscreen);
	bool gameOver = false;
	player p;
	platform plt;
	GUI gui(win);
	Crow crow;
	Projectile projectile;
	platformInit();
	for (int i = 0; i < 10; i++)
	{
		float rs = randomSpeed();
		ParticleArray[i] = new Particle(rs);
		particleInit(*ParticleArray[i]);
	}
	sf::Clock initial_clock;
	sf::Clock deltaClock;
	float plt_speed = -800;
	bool stop = false;
	srand(static_cast<unsigned int>(time(0)));
	AnimateSprite anim;
	const GLubyte* renderer = glGetString(GL_RENDERER);
	std::cout << "GPU Renderer: " << renderer << std::endl;
	//win.setFramerateLimit(60);
	while (win.isOpen())
	{
		float deltaTime = deltaClock.restart().asSeconds(); 
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
		{
			p.body.setPosition(100, 100);
			gameOver = false;
			gui.score = 0;
			gui.text.setString("SCORE: 0");
		}
		if (gameOver)
		{
			win.draw(gui.gameOverText);
			win.display();
			continue;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			p.body.move(1000 * deltaTime, 0);
			anim.animate(p.state ,p.body, 4096, p.xToAnimate, p.yToAnimate, p.rectWidth, p.rectHeight);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			p.body.move(-1000 * deltaTime, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			stop = !stop;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) || sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			p.block();
			p.state = P_BLOCKING;
			p.yToAnimate = 200;
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !projectile.shooted)
		{
			projectile.shooted = true;
			projectile.shootProjectile(p.body.getPosition().x, p.body.getPosition().y);
		}
		if (!p.JUMP_STATE && !p.BLOCK_STATE && (p.body.getGlobalBounds().intersects(platformArr[0].rect.getGlobalBounds()) ||
			p.body.getGlobalBounds().intersects(platformArr[1].rect.getGlobalBounds()) ||
			p.body.getGlobalBounds().intersects(platformArr[2].rect.getGlobalBounds()) ||
			p.body.getGlobalBounds().intersects(platformArr[3].rect.getGlobalBounds())
			))
			p.state = P_RUNNING;
		if ((p.BLOCK_STATE && p.body.getGlobalBounds().intersects(crow.body.getGlobalBounds())) || (crow.body.getGlobalBounds().intersects(projectile.body.getGlobalBounds()) && projectile.shooted))
		{
			crow.deflected = true;
			crow.yToAnimate = 100;
			projectile.shooted = false;
			projectile.body.setPosition(0, 0);
		}
		if (projectile.shooted)
		{
			projectile.body.move(5000 * deltaTime, 0);
			if (projectile.body.getPosition().x >= win.getSize().x)
			{
				projectile.shooted = false;
				projectile.body.setPosition(0, 0);
			}
		}
		gameOverCheck(p, win, gameOver, gui, crow);
		gui.updateScore();
		anim.animate(p.state, p.body, p.totalRowSize, p.xToAnimate, p.yToAnimate, p.rectWidth, p.rectHeight);
		anim.animteCrow(crow.deflected, crow.dead, crow.body, crow.crowClock, crow.totalRowSize, crow.xToAnimate, crow.yToAnimate, crow.rectWidth, crow.rectHeight);
		p.check_jump(deltaTime);
		p.check_block();
		win.clear();
		win.draw(p.body);
		win.draw(platformArr[0].rect);
		win.draw(platformArr[1].rect);
		win.draw(platformArr[2].rect);
		win.draw(platformArr[3].rect);
		win.draw(gui.text);
		if (projectile.shooted)
			win.draw(projectile.body);
		if (!crow.dead)
			win.draw(crow.body);
		for (int i = 0; i < 10; i++)
		{
			particleGenerator(*ParticleArray[i], deltaTime);
			win.draw(ParticleArray[i]->body);
		}
		gravity(p, deltaTime);
		if (!stop)
		platformGenerator(initial_clock, plt_speed, p, deltaTime);
		crow.spawn(deltaTime);
		win.display();
	}
}