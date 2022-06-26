#include"GameMenu.h"

void GameMenu::printMenu()
{
	char choice;

	while (1)
	{
		cout << "(1) Start a new game without color" << endl << "(2) Start a new game with color" << endl << "(8) Present instructions and keys" << endl << "(9) EXIT " << endl;
		choice = _getch();

		system("cls");

		switch (choice)
		{
		case '1':
			startNewGame(false);
			break;
		case'2':
			startNewGame(true);
			break;
		case '8':
			intructions();
			break;
		case '9':
			exit(1);
			break;
		default:
			cout << "Error! Please enter valid number\n" << endl;
		}
	}
}

void GameMenu::startNewGame(bool color)
{
	delete game;
	game = new Game(color);
	game->GameLoop();
}

void GameMenu::intructions()
{
	cout << "As PACMAN your mission is simple:" << endl
		<< "EAT ALL THE BREADCRUBS!" << endl
		<< "Navigate through the board using the keyboard's following:" << endl
		<< "D- Right" << endl << "A- Left " << endl << "W - Up" << endl << "X- Down" << endl << "S- Stay" << endl
		<< "There are ghosts hunting you and your job is to avoid them!" << endl
		<< "Notice! The Pacman has 3 lives. " << endl
		<< "Every time the Pacman is eaten by the ghosts the Pacman losing one life." << endl
		<< "If the Pacman has 0 lives - the game is OVER" << endl
		<< "Collect as many breadcrumbs as possible to earn the highest score." << endl
		<< "* You can always pause and unpause your game using the ESC button." << endl
		<< "GOOD LUCK! :) \n" << endl;
}
