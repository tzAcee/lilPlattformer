
#pragma once
#include "SFML/Graphics.hpp"
#include "AnimatedSprite.hpp"
#include <iostream>
#include "Enemy.h"

class Enemy;

class Player
{
private:
	sf::RenderWindow* _win;

	std::vector<Enemy> *_enemies;

	int _hp;
	sf::Vector2f _pos;
	sf::Vector2f _vel;
	sf::Texture *_spriteTexture;
	bool GROUND = false;
	bool SIDEGROUND = false;
	int _force = 75;
	bool _isJumping = false;
	bool _isAttacking = false;
	int _deadTime = 0;

	sf::Vector2f _size;

	bool keyPressed = false;
	bool walkLeft = false;
	bool isfalling = false;

	Animation _idle;
	Animation _walkLeft;
	Animation _walkRight;
	Animation _walkUp;
	Animation _attack;
	Animation _falling;
	Animation _dead;
	Animation _crouching;
	Animation _sliding;

	Animation* _currentAnim;

	bool _isAttacked = false;


	void check_key(sf::Time &frameTime);
	void jump();
	void move(sf::Vector2f dir);
	void play_anim(sf::Time &frameTime);
	void applyForce(sf::Time &frameTime);
	void attack();

	int fallingTime = 0;
	int jumpTime = 0;
	int _initAttack = 0;
	bool _hasAttack = false;

	int _dmg = 35;

	float getDistanceToEnemy(int i);

	sf::View _view;
	sf::Vector2f calcViewPos();

	void checkDeath();

public:
	void setEnemies(std::vector<Enemy> &enemy);
	bool _isCrouching = false;
	void knock_back(sf::Vector2f val);
	void decrHp(int val);
	int getHP();
	sf::Vector2f& getSize();
	AnimatedSprite _animatedSprite;
	void setGround(bool val);
	void setSideGround(bool val);
	void kill();
	sf::View& getView();
	Player();
	~Player();
	Player(sf::RenderWindow* win);
	void update(sf::Time frameTime);
};
