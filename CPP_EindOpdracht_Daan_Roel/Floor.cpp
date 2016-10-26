#include "stdafx.h"
#include "Floor.h"

Floor::Floor(int width, int height, int level)
{
level: level;
rooms: new Room[width * height];
}


Floor::~Floor()
{
}
