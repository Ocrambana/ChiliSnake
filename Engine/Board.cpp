#include "Board.h"
#include "Snake.h"
#include "Goal.h"
#include <assert.h>

Board::Board(Graphics& gfx)
	:
	gfx(gfx)
{}

void Board::DrawCell(const Location & loc, Color c)
{
	assert( loc.x >= 0);
	assert( loc.x <= width);
	assert( loc.y >= 0);
	assert( loc.y <= height);
	gfx.DrawRectDim(xOffset + loc.x * dimension, yOffset + loc.y * dimension, dimension - padding, dimension - padding, c);
}

void Board::DrawBorder()
{
	int xLimit{ xOffset + width * dimension },
		yLimit{ yOffset + height * dimension };

	for (int j{ yOffset - border }; j <= yLimit + border; j++)
		for (int i{ xOffset - border }; i <= xLimit + border; i++)
		{
			bool conditionToBeColored =
				(i > 0 && j > 0) && (i < Graphics::ScreenWidth && j < Graphics::ScreenHeight) &&
				(i < xOffset || i > xLimit) || (j < yOffset || j > yLimit);

			if (conditionToBeColored)
			{
				gfx.PutPixel(i,j, borderColor);
			}
		}
}

int Board::GetGridWidth() const
{
	return width;
}

int Board::GetGridHeight() const
{
	return height;
}

bool Board::IsInsideBoard(const Location & loc) const
{
	return loc.x >= 0 && loc.x < width && loc.y >= 0 && loc.y < height;
}

bool Board::CheckForObstacle(const Location & loc) const
{
	return hasObstacle[loc.y * width + loc.x];
}

void Board::SpawnObstacle(std::mt19937_64 & rng, const Snake & snake, const Goal& goal)
{
	std::uniform_int_distribution<int> xDist(0, width - 1);
	std::uniform_int_distribution<int> yDist(0, height - 1);

	Location newLoc;
	do
	{
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);
	} while (snake.IsInTile(newLoc) || CheckForObstacle(newLoc) || goal.GetLocation() == newLoc);

	hasObstacle[newLoc.y * width + newLoc.x] = true;
}

void Board::DrawObstacles()
{
	for (int j{ 0 }; j < height; j++)
		for (int i{ 0 }; i < width; i++)
		{
			if (CheckForObstacle({ i,j }))
			{
				DrawCell({i,j}, obstacleColor);
			}
		}
}

void Board::ResetObstacles()
{
	const int length = width * height;
	for (int i{ 0 }; i < length; i++)
	{
		hasObstacle[i] = false;
	}
}
