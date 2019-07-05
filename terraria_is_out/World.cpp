#pragma once
#include "World.h"

World::World() {}
World::~World() {}

void World::createMap()
{
	_tileSprite = new sf::Sprite;
	_tileSprite->setTexture(*_tileTexture);
	_tileSprite->scale({ 2, 1 });
	_tileSize = sf::Vector2f(_tileTexture->getSize().x, _tileTexture->getSize().y);
	_tileSprite->setPosition(sf::Vector2f(125, _win->getSize().y - 250));

	_tileSprite2 = new sf::Sprite;
	_tileSprite2->setTexture(*_tileTexture);
	_tileSprite2->scale({ 2, 1 });
	_tileSprite2->setPosition(sf::Vector2f(300, _win->getSize().y - 310));

	_spriteBack = new sf::Sprite;
	_spriteBack->setTexture(*_backGroundTexture);
	_spriteBack->scale({ 10000,1000 });
	_spriteBack->move(sf::Vector2f(-5000, -42 * 2000));

	_treeSprite = new sf::Sprite;
	_treeSprite->setTexture(*_treeTexture);
	_treeSprite->setPosition(sf::Vector2f(_win->getSize().x - 150, _win->getSize().y - 380));
	_treeSprite->scale({ 3.0,3.0 });

	_cloudSprite = new sf::Sprite;
	_cloudSprite->setTexture(*_cloudTexture);
	_cloudSprite->setPosition(sf::Vector2f(50, _win->getSize().y - 360));
	_cloudSprite->scale({ 4,4 });

	_cloudSprite2 = new sf::Sprite;
	_cloudSprite2->setTexture(*_cloudTexture2);
	_cloudSprite2->setPosition(sf::Vector2f(_win->getSize().x - 320, _win->getSize().y - 410));
	_cloudSprite2->scale({ 2,2 });

	for (int i = 0; i < _win->getSize().x; i += 16)
	{
		_spriteGrass.push_back(new sf::Sprite);

		_spriteGrass[i / 16]->setTexture(*_grasTexture);
		_spriteGrass[i / 16]->setPosition(sf::Vector2f(i, _win->getSize().y - 192));
	}
	for (int i = 0; i < _win->getSize().x; i += 16)
	{
		_spriteDirt.push_back(new sf::Sprite);

		_spriteDirt[i / 16]->setTexture(*_dirtTexture);
		_spriteDirt[i / 16]->setPosition(sf::Vector2f(i, _win->getSize().y - 176));
	}
	int setted = _spriteDirt.size();
	for (int i = 0; i < _win->getSize().x; i += 16)
	{
		_spriteDirt.push_back(new sf::Sprite);

		_spriteDirt[i / 16 + setted]->setTexture(*_dirtTexture);
		_spriteDirt[i / 16 + setted]->setPosition(sf::Vector2f(i, _win->getSize().y - 160));
	}

	for (int i = 0; i < _win->getSize().x; i += 16)
	{
		_spriteStone.push_back(new sf::Sprite);

		_spriteStone[i / 16]->setTexture(*_stoneTexture);
		_spriteStone[i / 16]->setPosition(sf::Vector2f(i, _win->getSize().y - 144));
	}

}

World::World(sf::RenderWindow* win, Player& player)
{
	_win = win;
	_player = &player;



	_pos = sf::Vector2i(0,0);
	_size = sf::Vector2i(32, 32);

	_rect = sf::IntRect(_pos, _size);

	_dirtTexture = new sf::Texture;
	_grasTexture = new sf::Texture;
	_stoneTexture = new sf::Texture;
	_backGroundTexture = new sf::Texture;
	_treeTexture = new sf::Texture;
	_cloudTexture = new sf::Texture;
	_cloudTexture2 = new sf::Texture;
	_tileTexture = new sf::Texture;

	if(!_cloudTexture->loadFromFile("assets/world/bg_cloud_B.png"))
	{ }
	if (!_cloudTexture2->loadFromFile("assets/world/bg_cloud_A.png"))
	{
	}

	if(!_tileTexture->loadFromFile("assets/world/tile.png"))
	{ }

	if (!_backGroundTexture->loadFromFile("assets/world/bg4.png"))
	{

	}

	if (!_treeTexture->loadFromFile("assets/world/tree01.png"))
	{

	}

	if (!_dirtTexture->loadFromFile("assets/world/terrain_corner_inner_top_left.png", _rect));
	{
		std::cout << "Failed to Load DIRT" << std::endl;
	}
	if (!_grasTexture->loadFromFile("assets/world/terrain_top_center.png", _rect));
	{
		std::cout << "Failed to Load GRAS" << std::endl;
	}
	if (!_stoneTexture->loadFromFile("assets/world/terrain_bottom_center.png", _rect));
	{
		std::cout << "Failed to Load STONE" << std::endl;
	}


	createMap();
}

void World::playerOnCorner(sf::FloatRect rect)
{
	float r1x = rect.left;
	float r1y = rect.top;
	float r1h = rect.height;
	float r1w = rect.width;
	float r2x = _player->_animatedSprite.getPosition().x;
	float r2w = _player->getSize().x;
	float r2y = _player->_animatedSprite.getPosition().y;
	float r2h = _player->getSize().y;

	if (r2x + r2w >= r1x && r2x <= r1x+r1w 
		&& r2y+r2h >= r1y+10 &&  r2y <= r1y+r1h)
	{
		sidegrounded = true;
	}
}

void World::playerOnGround(sf::FloatRect rect)
{
	float r1x = rect.left;
	float r1y = rect.top;
	float r1h = rect.height;
	float r1w = rect.width;
	float r2x = _player->_animatedSprite.getPosition().x;
	float r2w = _player->getSize().x;
	float r2y = _player->_animatedSprite.getPosition().y;
	float r2h = _player->getSize().y;

	if( r1x + r1w >= r2x &&     // r1 right edge past r2 left
		r1x <= r2x && r1y + r1h >= r2y &&       // r1 top edge past r2 bottom
		r1y <= r2y + r2h) {       // r1 bottom edge past r2 top
		grounded = true;
	}
}

sf::Vector2f World::getTileSize()
{
	return _tileSize;
}

void World::checkLiteCol(sf::FloatRect rect)
{
	float r1x = rect.left;
	float r1y = rect.top;
	float r1h = rect.height;
	float r1w = rect.width;
	float r2x = _player->_animatedSprite.getPosition().x;
	float r2w = _player->getSize().x;
	float r2y = _player->_animatedSprite.getPosition().y;
	float r2h = _player->getSize().y;
	if (r1x + r1w >= r2x &&     // r1 right edge past r2 left
		r1x <= r2x && r2y+r2h >= r1y && r2y+r2h <= r1y+4 && !_player->_isCrouching)   // r1 top edge past r2 bottom
 {       // r1 bottom edge past r2 top
		grounded = true;
	}


}

void World::update(sf::Time &frameTime)
{
	_win->draw(*_spriteBack);

	for (int i = 0; i<_spriteGrass.size(); i++)
	{
		playerOnGround(_spriteGrass[i]->getGlobalBounds());
		_win->draw(*_spriteGrass[i]);
	}
	for (int i = 0; i < _spriteDirt.size(); i++)
	{
		playerOnGround(_spriteDirt[i]->getGlobalBounds());
		_win->draw(*_spriteDirt[i]);
	}
	for (int i = 0; i < _spriteStone.size(); i++)
	{
		playerOnGround(_spriteStone[i]->getGlobalBounds());
		_win->draw(*_spriteStone[i]);
	}

	playerOnCorner(_spriteGrass[0]->getGlobalBounds());
	playerOnCorner(_spriteGrass[_spriteGrass.size()-1]->getGlobalBounds());
	playerOnCorner(_spriteDirt[0]->getGlobalBounds());
	playerOnCorner(_spriteDirt[_spriteDirt.size() - 1]->getGlobalBounds());
	playerOnCorner(_spriteStone[0]->getGlobalBounds());
	playerOnCorner(_spriteStone[_spriteStone.size() - 1]->getGlobalBounds());

	checkLiteCol(_tileSprite->getGlobalBounds());
	checkLiteCol(_tileSprite2->getGlobalBounds());

	if (grounded)
		_player->setGround(true);
	else
	{
		_player->setGround(false);
	}

	if (sidegrounded)
	{
		_player->setSideGround(true);
	}
	else
	{
		_player->setSideGround(false);
	}


	sidegrounded = false;
	grounded = false;

	_win->draw(*_treeSprite);
	_win->draw(*_cloudSprite);
	_win->draw(*_cloudSprite2);
	_win->draw(*_tileSprite);
	_win->draw(*_tileSprite2);
}