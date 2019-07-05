#include "Player.h"

Player::Player() {}
Player::~Player() {}

sf::Vector2f Player::calcViewPos()
{
	sf::Vector2f ret;
	ret.x = _pos.x;
	ret.y = _pos.y - float(_win->getSize().y)/4.4;

	return ret;
}



Player::Player(sf::RenderWindow* win)
{
	_hp = 100;

	_win = win;
	_spriteTexture = new sf::Texture;
	if (!_spriteTexture->loadFromFile("C:/dev/vssStuff/terraria_is_out/terraria_is_out/assets/playerSprite.png"))
	{
		std::cout << "Failed to load player spritesheet!" << std::endl;
	}

	_idle.setSpriteSheet(*_spriteTexture);
	_idle.addFrame(sf::IntRect(50, 0, 50, 37));
	_idle.addFrame(sf::IntRect(100, 0, 50, 37));
	_idle.addFrame(sf::IntRect(50, 0, 50, 37));
	_idle.addFrame(sf::IntRect(0, 0, 50, 37));


	_walkRight.setSpriteSheet(*_spriteTexture);
	_walkRight.addFrame(sf::IntRect(100, 38, 50, 37));
	_walkRight.addFrame(sf::IntRect(150, 37, 50, 37));
	_walkRight.addFrame(sf::IntRect(200, 38, 50, 37));
	_walkRight.addFrame(sf::IntRect(250, 38, 50, 37));
	_walkRight.addFrame(sf::IntRect(200, 38, 50, 37));
	_walkRight.addFrame(sf::IntRect(150, 38, 50, 37));
	_walkRight.addFrame(sf::IntRect(100, 38, 50, 37));
	_walkRight.addFrame(sf::IntRect(50, 38, 50, 37));

	_walkLeft.setSpriteSheet(*_spriteTexture);
	_walkLeft.addFrame(sf::IntRect(100, 38, 50, 37));
	_walkLeft.addFrame(sf::IntRect(150, 38, 50, 37));
	_walkLeft.addFrame(sf::IntRect(200, 38, 50, 37));
	_walkLeft.addFrame(sf::IntRect(250, 38, 50, 37));
	_walkLeft.addFrame(sf::IntRect(200, 38, 50, 37));
	_walkLeft.addFrame(sf::IntRect(150, 38, 50, 37));
	_walkLeft.addFrame(sf::IntRect(100, 38, 50, 37));
	_walkLeft.addFrame(sf::IntRect(50, 38, 50, 37));

	_walkUp.setSpriteSheet(*_spriteTexture);
	_walkUp.addFrame(sf::IntRect(50, 74, 50, 37));
	_walkUp.addFrame(sf::IntRect(100, 74, 50, 37));
	_walkUp.addFrame(sf::IntRect(150, 74, 50, 37));
	_walkUp.addFrame(sf::IntRect(200, 74, 50, 37));
	_walkUp.addFrame(sf::IntRect(250, 74, 50, 37));
	_walkUp.addFrame(sf::IntRect(300, 74, 50, 37));
	_walkUp.addFrame(sf::IntRect(50, 111, 50, 37));
	_walkUp.addFrame(sf::IntRect(100, 111, 50, 37));

	_attack.setSpriteSheet(*_spriteTexture);
	_attack.addFrame(sf::IntRect(50, 222, 50, 37));
	_attack.addFrame(sf::IntRect(100, 222, 50, 37));
	_attack.addFrame(sf::IntRect(150, 222, 50, 37));
	_attack.addFrame(sf::IntRect(200, 222, 50, 37));
	_attack.addFrame(sf::IntRect(250, 222, 50, 37));
	_attack.addFrame(sf::IntRect(300, 222, 50, 37));
	_attack.addFrame(sf::IntRect(50, 259, 50, 37));
	_attack.addFrame(sf::IntRect(100, 259, 50, 37));
	_attack.addFrame(sf::IntRect(150, 259, 50, 37));
	_attack.addFrame(sf::IntRect(200, 259, 50, 37));
	_attack.addFrame(sf::IntRect(250, 259, 50, 37));
	_attack.addFrame(sf::IntRect(300, 259, 50, 37));
	_attack.addFrame(sf::IntRect(50, 297, 50, 37));
	_attack.addFrame(sf::IntRect(100, 297, 50, 37));

	_falling.setSpriteSheet(*_spriteTexture);
	_falling.addFrame(sf::IntRect(50, 111, 50, 37));
	_falling.addFrame(sf::IntRect(100, 111, 50, 37));

	_dead.setSpriteSheet(*_spriteTexture);
	_dead.addFrame(sf::IntRect(50, 370-37, 50, 37));
	_dead.addFrame(sf::IntRect(100, 370-37, 50, 37));
	_dead.addFrame(sf::IntRect(150, 370-37, 50, 37));
	_dead.addFrame(sf::IntRect(200, 370-37, 50, 37));
	_dead.addFrame(sf::IntRect(250, 370-37, 50, 37));

	_crouching.setSpriteSheet(*_spriteTexture);
	_crouching.addFrame(sf::IntRect(200, 0, 50, 37));
	_crouching.addFrame(sf::IntRect(250, 0, 50, 37));
	_crouching.addFrame(sf::IntRect(300, 0, 50, 37));
	_crouching.addFrame(sf::IntRect(0, 37, 50, 37));

	_sliding.setSpriteSheet(*_spriteTexture);
	_sliding.addFrame(sf::IntRect(150, 74+37, 50, 37));
	_sliding.addFrame(sf::IntRect(200, 74 + 37, 50, 37));
	_sliding.addFrame(sf::IntRect(250, 74 + 37, 50, 37));
	_sliding.addFrame(sf::IntRect(300, 74 + 37, 50, 37));

	_currentAnim = &_idle;

	_pos.x = _win->getSize().x / 2;
	_pos.y = _win->getSize().y / 2;
	_animatedSprite = AnimatedSprite(sf::seconds(0.2), true, false);
	_animatedSprite.setPosition(_pos);

	_size = sf::Vector2f(50, 37);


	_vel = sf::Vector2f(0.f, 0.f);

//	GROUND = _win->getSize().y - 100;
	sf::Vector2f res = (sf::Vector2f)_win->getSize();
	res *= 0.9f;
	_view.reset(sf::FloatRect(calcViewPos(), res));
}

sf::Vector2f& Player::getSize()
{
	return _size;
}

void Player::setEnemies(std::vector<Enemy> &enemy)
{
	_enemies = &enemy;
}

void Player::knock_back(sf::Vector2f val)
{
	move(val);
}

void Player::decrHp(int val)
{
	_hp -= val;
	_isAttacked = true;
}

void Player::play_anim(sf::Time &frameTime)
{

	_animatedSprite.play(*_currentAnim);
	_animatedSprite.move(_vel * frameTime.asSeconds());
	_pos = _animatedSprite.getPosition();

	_animatedSprite.update(frameTime);
	_animatedSprite.setOrigin(sf::Vector2f(_animatedSprite.getLocalBounds().width / 2.f, 0.f));
}

void Player::jump()
{
	if (!_isJumping && !isfalling)
	{
		move(sf::Vector2f(0.f, -155.f));
		_isJumping = true;
	}
}

void Player::kill()
{
	_hp = 0;
}

void Player::setGround(bool val)
{
	GROUND = val;
}

void Player::setSideGround(bool val)
{
	SIDEGROUND = val;
}

void Player::attack()
{
	if (!_isJumping)
	{
		_hasAttack = false;
		_isAttacking = true;
		_initAttack++;
		for (int i = 0; i < _enemies->size(); i++)
		{
			if (getDistanceToEnemy(i) < 35.f)
			{
				if (_animatedSprite.getScale().x < 0 && _pos.x >= _enemies->at(i)._enemySprite.getPosition().x)
				{
					if (_initAttack > 35)
					{
						_enemies->at(i).decrHp(_dmg);
						_enemies->at(i).knock_Back(sf::Vector2f(0.f, -150.f));
						_hasAttack = true;
					}

				}
				else if (_animatedSprite.getScale().x > 0 && _pos.x <= _enemies->at(i)._enemySprite.getPosition().x)
				{
					if (_initAttack > 35)
					{
						_enemies->at(i).decrHp(_dmg);
						_enemies->at(i).knock_Back(sf::Vector2f(0.f, -150.f));
						
						_hasAttack = true;
					}
				}
			}

			if (_hasAttack)
				_initAttack = 0;
		}
	}
}

float Player::getDistanceToEnemy(int i)
{
	float x = _pos.x - _enemies->at(i)._enemySprite.getPosition().x;
	x *= x;
	float y = _pos.y - _enemies->at(i)._enemySprite.getPosition().y;
	y *= y;

	return sqrt(x + y);
}

sf::View& Player::getView()
{
	return _view;
}

void Player::move(sf::Vector2f dir)
{
	if(!_isAttacking)
	_vel += dir;
}

void Player::check_key(sf::Time &frameTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !_isCrouching)
	{
		_currentAnim = &_walkRight;
		move(sf::Vector2f(5.f, 0.f));
		keyPressed = true;
		_animatedSprite.setScale({ 1, 1 });
		_isAttacking = false;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !_isCrouching)
	{
		_currentAnim = &_walkLeft;
		move(sf::Vector2f(-5.f, 0.f));
		keyPressed = true;
		_animatedSprite.setScale({ -1, 1 });
		_isAttacking = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !_isCrouching)
	{
		jump();
		keyPressed = true;
		_isAttacking = false;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		attack();
		keyPressed = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !_isJumping)
	{
		_isCrouching = true;
		keyPressed = true;
	}
	else
		_isCrouching = false;

	if (_vel.x == 0 && !keyPressed)
	{
		_currentAnim = &_idle;
		_isAttacking = false;
	}

	if (_isJumping && !isfalling)
	{
		_currentAnim = &_walkUp;
		jumpTime++;


	}
	else if (_isAttacking)
	{
		_currentAnim = &_attack;
		jumpTime = 0;
	}
	else
	{
		jumpTime = 0;
	}



	if (_vel.y > 0 && !_isJumping)
	{
		isfalling = true;
		_currentAnim = &_falling;
		fallingTime++;
	}
	else if (_vel.y > 0 && _isJumping && !isfalling)
	{
		fallingTime++;
	}
	else
	{
		isfalling = false;
		fallingTime = 0;
	}

	if (!_isAttacking)
	{
		_initAttack = 0;
	}


	if (_isCrouching)
	{
		_currentAnim = &_crouching;
		if (abs(_vel.x) > 0)
			_currentAnim = &_sliding;
	}

	if (jumpTime > 200)
		_isJumping = false;

	keyPressed = false;

	play_anim(frameTime);
}

void Player::checkDeath()
{
	if (GROUND)
	{
		if (fallingTime > 50)
			_hp -= fallingTime / 10;

		fallingTime = 0;
	}
	if (fallingTime > 250)
		_hp = 0;
}

int Player::getHP()
{
	return _hp;
}

void Player::applyForce(sf::Time& frameTime)
{
	if (_vel.x > 1.0)
		_vel.x -= _force * frameTime.asSeconds();
	else if( _vel.x < -1.0)
		_vel.x += _force * frameTime.asSeconds();
	else
		_vel.x = 0;

	if (SIDEGROUND)
	{
		_vel.x = 0;
	}


	if (!GROUND)
	{
		_vel.y += 3 * _force * frameTime.asSeconds();
	}
	else
	{
		_vel.y = 0;
		_isJumping = false;
	}
}

void Player::update(sf::Time frameTime)
{
	if (_hp > 0)
	{
		checkDeath();
		check_key(frameTime);


		_isAttacked = false;
	}
	else
	{
		_currentAnim = &_dead;
		if (_deadTime <= 50)
		{
			_deadTime++;
			play_anim(frameTime);
		}

		//_animatedSprite.stop();

	}
	applyForce(frameTime);
	_view.setCenter(calcViewPos());
	_win->draw(_animatedSprite);
}
