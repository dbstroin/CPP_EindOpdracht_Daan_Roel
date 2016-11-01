// CPP_EindOpdracht_Daan_Roel.cpp : Defines the entry point for the console application.
//
#define _CRTDBG_MAP_ALLOC

#include "stdafx.h"
#include "Controller.h"
#include <iostream>
#include <crtdbg.h>
#include <stdlib.h>

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // leak dump enabled
	Controller gameController;


	gameController.StartGame();

    return 0;
}

