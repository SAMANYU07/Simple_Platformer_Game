#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>


class GUI
{
public:
	long long score;
	std::stringstream sst;
	std::string tempscr;
	sf::Clock score_clock;
	sf::Font font;
	sf::Text text;
	GUI()
	{
		score = 0;
		if (!font.loadFromFile("fonts/Raleway-Regular.ttf"))
			std::cout << "unable to load fonts\n";
		text.setFont(font);
		text.setString("SCORE: 0");
		text.setCharacterSize(24);
		text.setFillColor(sf::Color::Black);
		text.setStyle(sf::Text::Bold);
		text.setPosition(1120, 40);
	}
	void updateScore()
	{
		if (this->score_clock.getElapsedTime().asSeconds() >= 5)
		{
			this->score += 10;
			this->sst << this->score;
			this->sst >> this->tempscr;
			this->sst.str("");
			this->sst.clear();
			this->text.setString("SCORE: " + this->tempscr);
			this->score_clock.restart();
		}
	}

};