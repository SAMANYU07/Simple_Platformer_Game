#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>


class GUI
{
public:
	long long score, highScore;
	std::stringstream sst;
	std::string tempscr;
	sf::Clock score_clock;
	sf::Font font;
	sf::Text text, gameOverText;
	GUI(sf::RenderWindow &win)
	{
		score = 0;
		if (!font.loadFromFile("fonts/Raleway-Regular.ttf"))
			std::cout << "unable to load fonts\n";
		text.setFont(font);
		gameOverText.setFont(font);
		text.setString("SCORE: 0");
		text.setCharacterSize(24);
		gameOverText.setString("GAME OVER \nPress 'Backspace' to Restart");
		gameOverText.setCharacterSize(24);
		text.setFillColor(sf::Color::White);
		gameOverText.setFillColor(sf::Color::Red);
		text.setStyle(sf::Text::Bold);
		gameOverText.setStyle(sf::Text::Bold);
		text.setPosition(1120, 40);
		gameOverText.setPosition(win.getSize().x / 2, 100);
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