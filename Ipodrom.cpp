// Ipodrom.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// Ipodrom.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
//  main.cpp
//  Ipodrom
//
//  Created by Anton Kogan on 2/17/20.
//  Copyright © 2020 Anton Kogan. All rights reserved.
//
#include <iostream>
#include <conio.h>
#include <list>
#include <windows.h>
#include <list>
#include <cstring>
#include "Ipodrom.h"
using namespace std;

bool gameOver;
const int width = 40;
const int height = 40;
const int maxProgress = 38 * 4 + 4; //156 - biggest round
int trapX, trapY, score;


int bitCarriage = -1;

bool trap;


enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN };
//eDirecton dir;


class Carriage {
public: int  x, y, progress, speed;
	  int name;
private: eDirecton dir;

public:
	Carriage(int newName) {
		x = newName; y = 0;
		name = newName;
		dir = STOP;
		progress = 0;
		speed = rand() % 2 + 1;
	}

	Carriage(int i, int j) {
		x = i;
		y = j;
		dir = STOP;
	}

	void setDirection(eDirecton newDir) {
		dir = newDir;
	}
	eDirecton  getDirection() {
		return dir;
	}


	int getName() {
		return name;
	}
};
list<Carriage> carriages;

void setup()
{
	HWND console = GetConsoleWindow();
	RECT ConsoleRect;
	GetWindowRect(console, &ConsoleRect);
	MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 800, 800, TRUE);
	for (int i = 1; i < 9; i++) carriages.push_back(Carriage(i)); // 8 carriages to choose
	trapX = rand() % 8 + rand() % 1 * 32;
	trapY = rand() % 8 + rand() % 1 * 32;
	score = 0;
}


void draw()
{
	system("cls");

	for (int w = 0; w < width + 1; w++)
		cout << "#";
	cout << endl;

	trap = false;

	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			bool print = false;

			if (w == 0) //|| i == 0
			{
				cout << "#";
				print = true;
			}
			else  if (h == trapY && w == trapX)
			{
				cout << "*";
				print = true;
			}
			else
			{
				list<Carriage>::iterator p = carriages.begin();
				while (p != carriages.end()) {
					if (trapY == p->y && trapX == p->x) {
						trap = true;
					}

					if (h == p->y && w == p->x && !print) {
						cout << p->getName();
						print = true;
					}
					p++;
				}

				if (!print)
					cout << " ";
			}

			if (w == width - 1)
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i < width + 1; i++)
		cout << "#";
	cout << endl;

	cout << "Score:" << score << endl;
	if (trap) {
		cout << "Your hourse is thrapped somwhere";
	}
}

void input()
{
	int choice = 0;
	do
	{
		cout << endl
			<< " 1 - Start the game.\n"
			<< " 2 - Help.\n"
			<< " 3 - Exit.\n"
			<< " Enter your choice and press return: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			cout << "Please enter your carriage number: ";
			cin >> bitCarriage;
			cout << "your carriage number is " << bitCarriage << " game start!\n";
			gameOver = false;
			Sleep(1500);
			break;
		case 2:
			cout << " first enter 1,\n next step is to choose Carriage number, \n after that game will start\n";
			break;
		case 3:
			gameOver = true;
			cout << "End of Program.\n";
			return;
		default:
			cout << "Not a Valid Choice. \n"
				<< "Choose again.\n";
			break;
		}

	} while (choice != 1);
}


void logic()
{
	bool hasWinner = false;
	list<Carriage>::iterator p = carriages.begin();
	while (p != carriages.end()) {
		if (p->getName() == bitCarriage) {
			score = p->progress * 100 / maxProgress;//percentage from all way
		}

		if (p->progress >= maxProgress) {
			gameOver = true;
			if (hasWinner)  cout << "also wins - carriage number: " << p->getName() << "\n";
			else {
				cout << "Winner is carriage number: " << p->getName() << "\n";
				hasWinner = true;
			}
		}

		p->speed += (rand() % 2 - 1); // speed change randomly every step, that will avarage speed defference


		if (p->getDirection() == STOP) p->setDirection(DOWN);

		if (trap)
		{
			Sleep(5000);
			p->speed -= 1;

		}

		if (p->speed < 0) p->speed = 1; // to prevent moving backwords 
		if (p->getDirection() == DOWN) {
			p->y = p->y + p->speed;
			trapX = (rand() % 8);
			trapY = rand() % 40;

		}
		else if (p->getDirection() == RIGHT) {
			p->x = p->x + p->speed;
			trapX = (rand() % 40);
			trapY = rand() % 8 + 32;
		}
		else if (p->getDirection() == UP) {
			p->y = p->y - p->speed;
			trapX = (rand() % 8 + 32);
			trapY = rand() % 40;
		}
		else if (p->getDirection() == LEFT) {
			p->x = p->x - p->speed;
			trapX = (rand() % 40);
			trapY = rand() % 8;
		}

		p->progress += p->speed;

		if (p->y >= height - p->getName()) {
			p->setDirection(RIGHT);
		}
		if (p->x >= width - p->getName()) {
			p->setDirection(UP);
		}
		if (p->x > 8 && p->y < p->getName()) p->setDirection(LEFT);
		if (p->y < 8 && p->x < p->getName() + 1) p->setDirection(DOWN);

		p++;
	}
}


int main(int argc, const char* argv[])
{



	input();
	setup();
	while (!gameOver)
	{
		draw();
		logic();
		Sleep(500);
	}
	return 0;
}