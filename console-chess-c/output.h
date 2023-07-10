#ifndef OUTPUT_H
#define OUTPUT_H
#include <Windows.h>
#include "unit.h"

extern HDC hdc;

void InitBrushes();

void DrawEmptyTile(BoardPos pos);
void DrawHighlightedTile(BoardPos pos);

void DrawSprite(int xPixel, int yPixel, UnitType type, UnitTeam team);
void DrawUnit(const Unit* unit);

#endif // OUTPUT_H