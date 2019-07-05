#pragma once
#include "Player.h"
#include "SFML/Graphics.hpp"

class Interface
{
private:
	sf::RenderWindow* _win;
	Player* _player;
	sf::RectangleShape _hpBack;
	sf::RectangleShape _hpFront;
	sf::Vector2f _size;
	sf::Vector2f _pos;

public:
	Interface();
	~Interface();
	Interface(sf::RenderWindow* win);
	void update(Player& player);
};