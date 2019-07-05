#include "Enemy.h"

Enemy::Enemy() {}
Enemy::~Enemy() {}

Enemy::Enemy(sf::RenderWindow* win, Player& player, World& world, sf::Vector2f pos, int id)
{
	_win = win;
	_player = &player;
	_world = &world;
	_pos = pos;

	_hp = 100;

	srand(time(0) * id * id * id);
	_waitFrames = rand() % 250;

	_enemyAttack = new sf::Texture;
	_enemyIdle = new sf::Texture;
	_enemyDead = new sf::Texture;
	_enemyHit = new sf::Texture;
	_enemyWalk = new sf::Texture;

	if (!_enemyAttack->loadFromFile("C:/dev/vssStuff/terraria_is_out/terraria_is_out/assets/skeletton/attack.png"))
	{
		std::cout << "Failed to load enemy spritesheet!" << std::endl;
	}
	if (!_enemyIdle->loadFromFile("C:/dev/vssStuff/terraria_is_out/terraria_is_out/assets/skeletton/idle.png"))
	{
		std::cout << "Failed to load enemy spritesheet!" << std::endl;
	}
	if (!_enemyDead->loadFromFile("C:/dev/vssStuff/terraria_is_out/terraria_is_out/assets/skeletton/dead.png"))
	{
		std::cout << "Failed to load enemy spritesheet!" << std::endl;
	}
	if (!_enemyHit->loadFromFile("C:/dev/vssStuff/terraria_is_out/terraria_is_out/assets/skeletton/hit.png"))
	{
		std::cout << "Failed to load enemy spritesheet!" << std::endl;
	}
	if (!_enemyWalk->loadFromFile("C:/dev/vssStuff/terraria_is_out/terraria_is_out/assets/skeletton/walk.png"))
	{
		std::cout << "Failed to load enemy spritesheet!" << std::endl;
	}
	int width = 22;
	int height = 33;

	_walkRight.setSpriteSheet(*_enemyWalk);
	for (int i = 0; i < 13; i++)
	{
		_walkRight.addFrame(sf::IntRect(i * (width), 0, width - 2, height));
	}

	_hpBack.setSize(sf::Vector2f(3, 45));
	_hpBack.setPosition(sf::Vector2f(_pos.x + 15.f, _pos.y));
	_hpBack.setFillColor(sf::Color(220, 50, 50, 150));
	_hpBack.setOutlineThickness(2.f);
	_hpBack.setOutlineColor(sf::Color::White);

	_hpFront.setSize(sf::Vector2f(3, 45));
	_hpFront.setPosition(sf::Vector2f(_pos.x+15.f, _pos.y));
	_hpFront.setFillColor(sf::Color(50, 220, 50, 190));
	_hpFront.setOutlineThickness(2.f);
	_hpFront.setOutlineColor(sf::Color::White);

	_hpSize = _hpBack.getSize();

	width = 43;
	height = 37;
	_attack.setSpriteSheet(*_enemyAttack);
	for (int i = 0; i < 18; i++)
	{
		_attack.addFrame(sf::IntRect(i * (width), 0, width, height));
	}

	width = 30;
	height = 32;
	_hit.setSpriteSheet(*_enemyHit);
	for (int i = 0; i < 8; i++)
	{
		_hit.addFrame(sf::IntRect(i * width, 0, width, height));
	}

	width = 33;
	height = 32;
	_dead.setSpriteSheet(*_enemyDead);
	for (int i = 0; i < 15; i++)
	{
		_dead.addFrame(sf::IntRect(i * width, 0, width, height));
	}

	_currentAnim = &_walkRight;
	_enemySprite = AnimatedSprite(sf::seconds(0.1), true, false);
	_enemySprite.setPosition(_pos);
	_enemySprite.scale({ 1.2f, 1.2f });

	_vel.x = 35;
	_vel.y = 0;
}

void Enemy::applyForce(sf::Time frameTime)
{
	if (!GROUND)
	{
		_vel.y += 3 * 75 * frameTime.asSeconds();
	}
	else
	{
		_vel.y = 0;
	}
}

float Enemy::getDistanceToPlayer()
{
	float x = _pos.x - _player->_animatedSprite.getPosition().x;
	x *= x;
	float y = _pos.y - _player->_animatedSprite.getPosition().y;
	y *= y;
	return(sqrt(x + y));
}

void Enemy::playAnim(sf::Time frameTime)
{
	_enemySprite.play(*_currentAnim);
	_enemySprite.setPosition(_pos);
	_enemySprite.update(frameTime);
	_enemySprite.setOrigin(sf::Vector2f(_enemySprite.getLocalBounds().width / 2.f, 0.f));
}

void Enemy::checkGround()
{

	float r2x = _world->_tileSprite->getPosition().x;
	float r2y = _world->_tileSprite->getPosition().y;
	float r2h = _world->getTileSize().y;
	float r2w = 2*_world->getTileSize().x;
	float r3x = _world->_tileSprite2->getPosition().x;
	float r3y = _world->_tileSprite2->getPosition().y;
	float r3h = _world->getTileSize().y;
	float r3w = 2*_world->getTileSize().x;
	float r1x = _pos.x;
	float r1w = 20;
	float r1y = _pos.y;
	float r1h = 33;
	

	if (_pos.y >= 370)
	{
		GROUND = true;
	}
	else if (r1x + r1w >= r2x &&
			r1x<= r2x + r2w &&
		r1y + r1h >= r2y-10 && r1y <= (r2y)-35)
	{   
		GROUND = true;
	}
	else if (r1x + r1w >= r3x &&
		r1x <= r3x + r3w &&
		r1y + r1h >= r3y - 10 && r1y <= (r3y)-35)
	{
		GROUND = true;
	}
	else
		GROUND = false;
}

void Enemy::decrHp(int val)
{
	_hp -= val;
	_isAttacked = true;
}

void Enemy::knock_Back(sf::Vector2f val)
{
	_vel += val;
}

void Enemy::setGround(bool val)
{
	GROUND = val;
}

void Enemy::jump()
{
	if (_waitFrames > 200)
	{
		_vel.y -= 212.f;
		_waitFrames = 0;
	}
}

void Enemy::attack(sf::Vector2f knockBack)
{
	_isAttacking = true;
	_attackCount++;
	_initAttack++;
	_currentAnim = &_attack;
	if (_initAttack >= 48)
	{
		_player->knock_back(knockBack);
		_player->decrHp(15);
		_initAttack = 0;
	}
}

void Enemy::move(sf::Time frameTime)
{

	applyForce(frameTime);
	if (!_isAttacking)
	{
		jump();

		_pos.x += _vel.x * frameTime.asSeconds();
	}
	_pos.y += _vel.y * frameTime.asSeconds();

	if (_pos.x <= 35 || _pos.x >= _win->getSize().x - 35.f)
	{
		_vel.x *= -1;
		float scl = _enemySprite.getScale().x;
		scl *= -1;
		_enemySprite.setScale({ scl, 1.2 });
	}

	if (_vel.x != 0)
	{
		_currentAnim = &_walkRight;
	}

	if (getDistanceToPlayer() < 35.f && _attackCount < 50 && !_isAttacked && _player->getHP() > 0)
	{
		if ((_vel.x < 0 && _player->_animatedSprite.getPosition().x < _pos.x))
		{//links
			attack(sf::Vector2f(-50.f, -250.f));
		}
		else if (_vel.x > 0 && _player->_animatedSprite.getPosition().x > _pos.x)
		{//Rechts
			attack(sf::Vector2f(50.f, -250.f));
		}
		else
			_currentAnim = &_walkRight;
	}
	else
	{
		_attackCount = 0;
		_initAttack = 0;
		_isAttacking = false;
		_currentAnim = &_walkRight;
	}


	if (_isAttacked || (_isAttackedCount > 0 && _isAttackedCount < 50))
	{
		_isAttackedCount++;
		_currentAnim = &_hit;
	}



	checkGround();
	if (_isAttackedCount >= 50)
		_isAttackedCount = 0;
	playAnim(frameTime);
	_waitFrames++;
}

void Enemy::update(sf::Time frameTime)
{
	if (_hp > 0)
	{
		move(frameTime);

		_hpBack.setPosition(sf::Vector2f(_pos.x + 15.f, _pos.y));
		_hpFront.setPosition(sf::Vector2f(_pos.x + 15.f, _pos.y));
		_hpFront.setSize(sf::Vector2f(3, (float(_hp) / 100.f) * _hpSize.y));

		_win->draw(_hpBack);
		_win->draw(_hpFront);
	}
	else
	{
		applyForce(frameTime);
		_currentAnim = &_dead;
		_deadFrames++;
		if(_deadFrames < 80)
		playAnim(frameTime);
	}
	_win->draw(_enemySprite);

	_isAttacked = false;
}