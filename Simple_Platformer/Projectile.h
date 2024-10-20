#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "player.h"

class Projectile
{
public:
	sf::RectangleShape body;
	sf::Texture texture;
	bool shooted;
	Projectile() : shooted(false) {}
	void shootProjectile(const float &playerx, const float &playery)
	{
		this->body.setSize(sf::Vector2f(100, 10));
		this->body.setFillColor(sf::Color::Blue);
		this->body.setPosition(playerx, playery);
	}
};