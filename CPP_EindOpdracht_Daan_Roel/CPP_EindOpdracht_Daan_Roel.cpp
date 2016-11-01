// CPP_EindOpdracht_Daan_Roel.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Controller.h"

int main()
{
	Controller gameController;


	gameController.StartGame();
	gameController.hi();
	while (gameController.runGame());

    return 0;
}

