#include "Board.h"
#include <assert.h>

Board::Board(Graphics& gfx)
	:
	gfx(gfx)
{
}

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
