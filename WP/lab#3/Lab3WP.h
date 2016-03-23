#pragma once

#include "resource.h"

#include <windows.h>
#include "Line.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "FreeHand.h"
#include "Bezier.h"
#include "PolygonDrawing.h"
#include "Eraser.h"


#define NUMBER_OF_COLORS 5

#define IDHK_CHANGE_COLOR 1012
#define IDHK_DRAW_CIRCLE 1013
#define IDHK_DRAW_RECTANGLE 1014
#define IDHK_DRAW_LINE 1015
#define IDHK_DRAW_HAND 1016
#define IDHK_DRAW_BEZIER 1017
#define IDHK_DRAW_POLYGON 1018
#define IDHK_DRAW_ERASER 1019


#define IDHK_DRAW_UNDO 1999
#define IDHK_DRAW_WIDTH_INCREASE 2000
#define IDHK_DRAW_WIDTH_DECREASE 2001