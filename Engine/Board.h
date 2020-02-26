#pragma once

#include "Graphics.h"
#include "Location.h"
#include <random>

class Board
{
public:
	Board(Graphics& gfx);
	void DrawCell(const Location& loc, Color c);
	void DrawBorder();
	int GetGridWidth() const;
	int GetGridHeight() const;
	bool IsInsideBoard(const Location &loc) const;
	bool CheckForObstacle(const Location &loc) const;
	void SpawnObstacle(std::mt19937_64& rng, const class Snake& snake, const class Goal& goal);
	void DrawObstacles();
	void ResetObstacles();
private:
	static constexpr int 
		dimension{ 20 },
		width{35},
		height{25},
		padding{3},
		border{5},
		xOffset{50},
		yOffset{40};
	static constexpr Color	borderColor = Colors::White,
							obstacleColor = Colors::Gray;
	bool hasObstacle[width * height] = { false };
	Graphics& gfx;
};