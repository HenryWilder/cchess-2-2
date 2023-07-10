#ifndef OUTPUT_H
#define OUTPUT_H
#include <Windows.h>
#include "unit.h"

extern HDC hdc;

void InitBrushes();

void DrawEmptyTile(BoardPos pos);
void DrawHighlightedTile(BoardPos pos);

void DrawUnit(const Unit* unit);
void DrawSprite(int xPixel, int yPixel, UnitType type, UnitTeam team);

#endif // OUTPUT_H