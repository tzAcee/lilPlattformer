#pragma once
#include "Interface.h"
Interface::Interface() {}
Interface::~Interface() {}

Interface::Interface(sf::RenderWindow* win)
{
	_win = win;

	_pos = sf::Vector2f(15, _win->getSize().y - _win->getSize().y / 10);
	_hpBack.setSize(sf::Vector2f(150, 10));
	_hpBack.setPosition(_pos);
	_hpBack.setFillColor(sf::Color(200, 50, 50, 180));
	_hpBack.setOutlineThickness(1.f);
	_hpBack.setOutlineColor(sf::Color::Black);

	_hpFront.setSize(sf::Vector2f(150, 10));
	_hpFront.setPosition(_pos);
	_hpFront.setFillColor(sf::Color(50, 200, 50, 220));
	_hpFront.setOutlineThickness(1.f);
	_hpFront.setOutlineColor(sf::Color::Black);

	_size = _hpBack.getSize();
}

void Interface::update(Player &player)
{
	_player = &player;
	_pos.x = _player->_animatedSprite.getPosition().x + 20;
	_pos.y = _player->_animatedSprite.getPosition().y + 50;
	_hpBack.setPosition(_pos);
	_hpFront.setPosition(_pos);
	_hpFront.setSize(sf::Vector2f((float(_player->getHP()) / 100.f)*_size.x, 10));

	if (_player->getHP() > 0)
	{
		_win->draw(_hpBack);
		_win->draw(_hpFront);
	}
}