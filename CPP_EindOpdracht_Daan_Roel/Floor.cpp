#include "stdafx.h"
#include "Floor.h"

Floor::Floor()
{
}

Floor::Floor(int w, int l, int lev)
{
	level = lev;
	rooms: new Room[w * l];
}


Floor::~Floor()
{
}
