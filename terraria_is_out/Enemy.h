#pragma once
#ifndef ENEMY_H
#define ENEMY_H
#include "SFML/Graphics.hpp"
#include "Player.h"
#include "World.h"
#include "AnimatedSprite.hpp"

class Player;
class World;

class Enemy
{
private:
	sf::RenderWindow* _win;

	int _hp;

	sf::Texture* _enemyAttack;
	sf::Texture* _enemyIdle;
	sf::Texture* _enemyDead;
	sf::Texture* _enemyWalk;
	sf::Texture* _enemyHit;

	sf::RectangleShape _hpBack;
	sf::RectangleShape _hpFront;
	sf::Vector2f _hpSize;

	Animation _idle;
	Animation _dead;
	Animation _walkRight;
	Animation _attack;
	Animation _hit;

	Animation* _currentAnim;

	sf::Vector2f _pos;
	sf::Vector2f _vel;
	int _dmg;
	int _waitFrames = 0;
	bool _isAttacking = false;
	int _attackCount = 0;
	int _initAttack = 0;
	bool _isAttacked = false;
	int _isAttackedCount = 0;
	int _deadFrames = 0;

	Player* _player;
	World* _world;

	void playAnim(sf::Time frameTime);
	void applyForce(sf::Time frameTime);
	void move(sf::Time frameTime);
	void checkGround();
	void jump();
	void attack(sf::Vector2f knockback);
	float getDistanceToPlayer();

	bool GROUND = false;

public:

	void knock_Back(sf::Vector2f val);
	void decrHp(int val);
	AnimatedSprite _enemySprite;
	Enemy();
	~Enemy();
	Enemy(sf::RenderWindow* win, Player& player, World& world, sf::Vector2f pos, int id);
	void update(sf::Time frameTime);

	void setGround(bool val);
};

#endif ENEMY_H