// CPP_EindOpdracht_Daan_Roel.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Controller.h"

int main()
{
	Controller gameController;

	gameController.StartGame();

	while (gameController.RunGame()) {
		// play game
	}

    return 0;
}

