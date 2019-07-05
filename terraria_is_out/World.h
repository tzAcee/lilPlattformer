#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include "Player.h"

class Player;

class World
{
private:
	sf::Texture* _dirtTexture;
	sf::Texture* _grasTexture;
	sf::Texture* _stoneTexture;

	sf::Texture* _tileTexture;

	sf::Texture* _treeTexture;

	sf::Texture* _backGroundTexture;

	sf::Texture* _cloudTexture;
	sf::Texture* _cloudTexture2;
	
	sf::Vector2i _pos;
	sf::Vector2i _size;

	sf::IntRect _rect;

	sf::RenderWindow* _win;

	Player *_player;

	std::vector<sf::Sprite*> _spriteGrass;
	std::vector<sf::Sprite*> _spriteDirt;
	std::vector<sf::Sprite*> _spriteStone;
	sf::Sprite* _spriteBack;
	sf::Sprite* _treeSprite;
	sf::Sprite* _cloudSprite;
	sf::Sprite* _cloudSprite2;

	
	bool grounded = false;
	bool sidegrounded = false;

	sf::Vector2f _tileSize;

	void createMap();

	void playerOnGround(sf::FloatRect rect);
	void playerOnCorner(sf::FloatRect rect);
	void checkLiteCol(sf::FloatRect rect);

public:

	sf::Sprite* _tileSprite;
	sf::Sprite* _tileSprite2;
	sf::Vector2f getTileSize();
	World();
	~World();
	World(sf::RenderWindow* win, Player &player);
	void update(sf::Time &frameTime);
};