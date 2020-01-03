#pragma once

#include "Graphics.h"
#include "Location.h"

class Board
{
public:
	Board(Graphics& gfx);
	void DrawCell(const Location& loc, Color c);
	void DrawBorder();
	int GetGridWidth() const;
	int GetGridHeight() const;
	bool IsInsideBoard(const Location& loc) const;
private:
	static constexpr int 
		dimension{ 20 },
		width{25},
		height{25},
		padding{3},
		border{5},
		xOffset{150},
		yOffset{40};
	const Color borderColor{ Colors::White };
	Graphics& gfx;
};