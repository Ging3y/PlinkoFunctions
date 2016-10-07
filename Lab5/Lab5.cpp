// Lab5.cpp : Defines the entry point for the console application.

/*HEADER
*/

#include "stdafx.h"
#include "stdafx.h"
#include <iomanip>
#include <iostream>
#include <string>
#include <stdlib.h>    
#include <time.h>

using namespace std;

int prizeMoney(int slot)
{
	// local variable declaration
	int prizeMoney;
	prizeMoney = 0;
	//Make constant
	const int ZERO_EIGHT = 100;
	const int ONE_SEVEN = 500;
	const int TWO_SIX = 1000;
	const int THREE_FIVE = 0;
	const int FOUR = 10000;

	if (slot == 0 || slot == 8)
	{
		prizeMoney = ZERO_EIGHT;
	}

	if (slot == 1 || slot == 7)
	{
		prizeMoney = ONE_SEVEN;
	}

	if (slot == 2 || slot == 6)
	{
		prizeMoney = TWO_SIX;
	}

	if (slot == 3 || slot == 5)
	{
		prizeMoney = THREE_FIVE;
	}

	if (slot == 4)
	{
		prizeMoney = FOUR;
	}

	return prizeMoney;
}

int getChoice(int choice)
{
	cin >> choice;

	
	while((cin.fail()))
	{ 
		cout << "Thats not a number!";
		cout << "Choice:";
		cin >> choice;
	}
	

	return choice;
}

int main()
{

//Initialize Variables
#pragma region myVariables
	int menuChoice = -1;
	const string MENU = "Plinko Menu:\n0 - Quit\n1 - Drop one chip\n2 - Drop multiple chips\n";
	const string WELCOME = "Welcome to a game of Plinko! \n";
	const string BREAK = "==========\n";
	string chipPath = "[";
	int pegChoice = 0;
	int dropMultiple = 0;
	int randNum = 0;
	double chipPos = 0.0;
	double totalPrizeMoney = 0.0;

	//***Control Panel for board***
	const int HEIGHT = 13; //Height
	double chipShift = .5; //Horizontal shift per level the puck can make
	const double leftCap = 0.0; //Left Bound
	const double rightCap = 8.0; //Right Bound
#pragma endregion

	srand(time(NULL));
	cout << WELCOME;

	while (menuChoice != 0)
	{
		//RESET VARIABLES
		int HEIGHT = 13;
		chipPath = "[";
		totalPrizeMoney = 0.0;

		cout << MENU;

		menuChoice = getChoice(menuChoice);

		switch (menuChoice)
		{
		case 0:
#pragma region quitProgarm
			cout << BREAK;
			cout << "Closing\n";
			break;
#pragma endregion

		case 1:
#pragma region dropOne
			cout << BREAK;
			cout << "Which peg do you want to drop it in?(1-8)\n";
			cout << "Peg: ";
			cin >> pegChoice;

			if (pegChoice < leftCap || pegChoice > rightCap)
			{
				cout << "Incorrect Value\n";
				break;
			}

			chipPos = pegChoice;
			chipPath = chipPath + to_string(pegChoice) + ".0, ";

			//Random falling (Binary: 0 - Left, 1 - Right)
			for (HEIGHT > 0; HEIGHT = HEIGHT - 1;)
			{
				//Get Random Number
				randNum = (rand() % 2);
				chipShift = .5;

				//MOVE LEFT - Go left 1, if you get left and pos isn't all to the left
				if (randNum == 0)
				{
					//If chip is far left, invert falling
					if (chipPos == leftCap) { chipShift = chipShift * -1; }

					chipPos = chipPos - chipShift;
					if (HEIGHT == 1)
					{
						chipPath = chipPath + to_string(chipPos).substr(0, 3);
					}
					else
					{
						chipPath = chipPath + to_string(chipPos).substr(0, 3) + ", ";
					}

					//Reverts chipshift back to -.5 for LEFT random numbers
					if (chipPos == leftCap + .5) { chipShift = chipShift * -1; }
				}
				else
				{
					//If chip is far right, invert falling
					if (chipPos == rightCap)
					{
						chipShift = chipShift * -1;
					}

					chipPos = chipPos + chipShift;

					if (HEIGHT == 1)
					{
						chipPath = chipPath + to_string(chipPos).substr(0, 3);
					}
					else
					{
						chipPath = chipPath + to_string(chipPos).substr(0, 3) + ", ";
					}
					//Reverts chipshift back to .5 for RIGHT random numbers
					if (chipPos == rightCap + .5) { chipShift = chipShift * -1; }
				}

			}

			chipPath = chipPath + "]\n";
			chipPath = chipPath + "\n" + "You won: $" + to_string(prizeMoney(chipPos))
				+ ".00 \n";
			cout << chipPath;
			cout << BREAK;

			break;
#pragma endregion

		case 2:
#pragma region dropMultiple
			cout << BREAK;
			cout << "How many chips would you like to drop?\n";
			cout << "Chips to drop: ";
			cin >> dropMultiple;

			//Chip amount drop validation
			if (dropMultiple < 2)
			{
				cout << "Incorrect Value\n";
				break;
			}

			//Peg number validation
			cout << "\nWhich peg do you want to drop them in?(1-8)\n";
			cout << "Peg: ";
			cin >> pegChoice;

			if (pegChoice < leftCap || pegChoice > rightCap)
			{
				cout << "Incorrect Value\n";
				break;
			}

			for (int i = 0; i < dropMultiple; i = i + 1)
			{
				//Make sure variables are kept constant during the loop
				chipPos = pegChoice;
				HEIGHT = 13;

				//Random falling (Binary: 0 - Left, 1 - Right)
				for (HEIGHT > 0; HEIGHT = HEIGHT - 1;)
				{
					//Get Random Number
					randNum = (rand() % 2);
					chipShift = .5;

					//MOVE LEFT - Go left 1, if you get left and pos isn't all to the left
					if (randNum == 0)
					{
						//If chip is far left, invert falling
						if (chipPos == leftCap) { chipShift = chipShift * -1; }
						chipPos = chipPos - chipShift;
					}

					else
					{

						//If chip is far right, invert falling
						if (chipPos == rightCap) { chipShift = chipShift * -1; }
						chipPos = chipPos + chipShift;
					}

				}
				totalPrizeMoney = totalPrizeMoney + prizeMoney(chipPos);
			}

			cout << fixed << setprecision(2);
			cout << "You won a total of: $" << totalPrizeMoney << "\n";
			cout << "Average winnings per chip: $" << (totalPrizeMoney / dropMultiple) << "\n\n";

			cout << BREAK;
			break;
#pragma endregion

		default:
#pragma region defaultCase
			cout << "Incorrect choice, please try again.";
			break;
#pragma endregion
		}
	}

	system("pause");


	

    return 0;
}

