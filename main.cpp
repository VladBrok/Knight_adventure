#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <cstdlib>
using namespace sf;

class Knight
{

};

class TileMap
{
	const int MAP_SIZE;
	float gridSize;
	Texture towerTexture;
	Texture treeTexture;
	RectangleShape tile;
	std::vector<std::vector<RectangleShape>> tileMap;
	std::vector<std::pair<int, int>> tilesWithtree;

public:

	TileMap(float gridSize_ = 100.f) : MAP_SIZE(10)
	{
		srand(time(0));

		if (gridSize_ <= 0.f)
			throw std::runtime_error("Invalid grid size.");
		gridSize = gridSize_;
		if (!treeTexture.loadFromFile("Textures/tree.png"))
			throw std::runtime_error("Could not load the tree texture");
		if (!towerTexture.loadFromFile("Textures/tower.png"))
			throw std::runtime_error("Could not load tower texture");
		
		// making one base tile
		tileMap.resize(MAP_SIZE, std::vector<RectangleShape>(MAP_SIZE));
		tile.setFillColor(Color(37, 149, 44));
		tile.setSize(Vector2f(gridSize, gridSize));
		tile.setOutlineColor(Color::Black);
		tile.setOutlineThickness(1.f); 

		// Filling the tile map
		for (int i = 0; i < tileMap.size(); ++i)
		{
			for (int j = 0; j < tileMap.size(); ++j)
			{
				tile.setPosition(i * gridSize, j * gridSize);
				tileMap[i][j] = tile;
			}
		}

		// Generating 4 random positions for trees
		for (int i = 0; i < 4; ++i)
		{
			tilesWithtree.push_back(std::make_pair(rand() % (tileMap.size() - 3) + 1, rand() % (tileMap.size() - 3) + 1));
		}
	}

	// Returns true if that tile is with tree, false otherwise
	bool withTree(int i, int j)
	{
		return std::find(tilesWithtree.begin(), tilesWithtree.end(), std::make_pair(i, j)) != tilesWithtree.end();
	}

	// Drawing all tiles, towers and trees
	void draw(RenderWindow& window)
	{
		for (int i = 0; i < tileMap.size(); ++i)
		{
			for (int j = 0; j < tileMap.size(); ++j)
			{
				window.draw(tileMap[i][j]);
				if (i == 0 || i == tileMap.size() - 1 || j == 0 || j == tileMap.size() - 1) // Drawing the walls on the perimeter
				{
					Sprite towerSprite;
					towerSprite.setPosition(i * gridSize, j * gridSize);
					towerSprite.setScale(gridSize / towerTexture.getSize().x, gridSize / towerTexture.getSize().y);
					towerSprite.setTexture(towerTexture);
					window.draw(towerSprite);
				}
				else if (withTree(i, j)) // Drawing trees
				{
					Sprite treeSprite;
					treeSprite.setScale(gridSize / treeTexture.getSize().x / 2, gridSize / treeTexture.getSize().y / 2);
					treeSprite.setTexture(treeTexture);
					treeSprite.setPosition(i * gridSize + gridSize / 2 - treeSprite.getGlobalBounds().width / 2,
										   j * gridSize + gridSize / 2 - treeSprite.getGlobalBounds().height / 2);
					window.draw(treeSprite);
				}
			}
		}
	}
	
};

class Game
{
	const unsigned FPS_LIMIT;
	const float GRID_SIZE;
	Knight player;
	TileMap map;

public:

	Game() : FPS_LIMIT(60), GRID_SIZE(100.f)
	{
	}

	void run()
	{
		RenderWindow window(VideoMode(800, 600), "Knight's adventure");
		window.setFramerateLimit(FPS_LIMIT);

		

		while (window.isOpen())
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == event.Closed)
				{
					window.close();
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape))
				window.close();

			// UPDATE
			


			// CLEAR, DRAW, DISPLAY
			window.clear();
			map.draw(window);
			window.display();
		}
	}

};


int main()
{
	Game game;
	game.run();

	return 0;
};