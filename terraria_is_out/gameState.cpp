#include "gameState.h"

Game::Game() {}
Game::~Game() {}

void Game::initEnemies()
{
	_enemies.resize(enemySize);
	for (int i = 0; i < _enemies.size(); i++)
	{
		srand(time(0) * i * i * i);
		_enemies[i] = Enemy(&_win, _player, _world, sf::Vector2f((rand()%(_win.getSize().x-36))+36, 50.f), ((i+1)*2));
	}
}

void Game::_start()
{
	_running = true;
	sf::Clock frameClock;

	_win.setView(_player.getView());

	while (_win.isOpen())
	{
		sf::Event ev;
		if (_win.pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed)
				_win.close();
		}

		sf::Time frameTime = frameClock.restart();

		_player.setEnemies(_enemies);

		_win.clear(sf::Color(150,150,150));

		_world.update(frameTime);
		_player.update(frameTime);

		for (int i = 0; i < _enemies.size(); i++)
		{
			_enemies[i].update(frameTime);
		}


		_UI.update(_player);

		_win.display();

		_win.setView(_player.getView());
	}

	_running = false;
}

Game::Game(int w, int h)
{
	_win.create(sf::VideoMode(w, h), "terraria_is_out");
		_win.setFramerateLimit(60);

	_player = Player(&_win);
	_world = World(&_win, _player);
	_UI = Interface(&_win);

	initEnemies();

	_start();
}