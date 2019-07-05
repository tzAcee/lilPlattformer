#include "SFML/Graphics.hpp"
#include "Player.h"
#include "World.h"
#include "Interface.h"
#include "Enemy.h"

class Game
{
private:
	bool _running;
	sf::RenderWindow _win;
	void _start();
	Player _player;
	std::vector<Enemy> _enemies;
	World _world;
	Interface _UI;

	int enemySize = 5;

	void initEnemies();

public:
	Game();
	~Game();
	Game(int w, int h);
};