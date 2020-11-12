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
#include <list>
#include <list>
#include <cstring>


#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
   //define something for Windows (32-bit and 64-bit, this part is common)
#include <windows.h>
#include <conio.h>
   #ifdef _WIN64
      //define something for Windows (64-bit only)
   #else
      //define something for Windows (32-bit only)
   #endif
#elif __APPLE__
    #include <TargetConditionals.h>
    #include <unistd.h>
    #if TARGET_IPHONE_SIMULATOR
         // iOS Simulator
    #elif TARGET_OS_IPHONE
        // iOS device
    #elif TARGET_OS_MAC
        // Other kinds of Mac OS
    #else
    #   error "Unknown Apple platform"
    #endif
#elif __linux__
    // linux
#elif __unix__ // all unices not caught above
    // Unix
#elif defined(_POSIX_VERSION)
    // POSIX
#else
#   error "Unknown compiler"
#endif


using namespace std;

bool gameOver;
const int width = 40;
const int height = 40;
const int maxProgress = 38 * 4 + 4; //156 - biggest round
int trapX, trapY, score;


int bitCarriage = -1;

int trapHourse;


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
//    HWND console = GetConsoleWindow();
//    RECT ConsoleRect;
//    GetWindowRect(console, &ConsoleRect);
//    MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 800, 800, TRUE);
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

    trapHourse = 0;

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
                        trapHourse = p->name;
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
    if (trapHourse != 0) {
        cout << "carriage " << trapHourse << " is trapped somewhere; speed -1 \n";
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
            usleep(1500);
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

        if (p->x == trapX && p->y == trapY)//horse trapped
        {
            usleep(5000);
            p->speed -= 1;

        }

        if (p->progress >= maxProgress) {
            gameOver = true;
            if (hasWinner)  cout << "right after winner comes carriage number: " << p->getName() << "\n";
            else {
                cout << "Winner is carriage number: " << p->getName() << "\n";
                hasWinner = true;
                if (bitCarriage == p->getName()) {
                    cout << "H     H HHHHHHH H     H    H     H HHH H     H HHH \n";
                    cout << " H   H  H     H H     H    H  H  H  H  HH    H HHH \n";
                    cout << "  H H   H     H H     H    H  H  H  H  H H   H HHH \n";
                    cout << "   H    H     H H     H    H  H  H  H  H  H  H  H  \n";
                    cout << "   H    H     H H     H    H  H  H  H  H   H H     \n";
                    cout << "   H    H     H H     H    H  H  H  H  H    HH HHH \n";
                    cout << "   H    HHHHHHH  HHHHH      HH HH  HHH H     H HHH \n";
                }
                else {
                    cout << "H     H HHHHHHH H     H    H       HHHHHHH  HHHHH  HHHHHH \n";
                    cout << " H   H  H     H H     H    H       H     H H     H H       \n";
                    cout << "  H H   H     H H     H    H       H     H H       H       \n";
                    cout << "   H    H     H H     H    H       H     H  HHHHH  HHHHH   \n";
                    cout << "   H    H     H H     H    H       H     H       H H       \n";
                    cout << "   H    H     H H     H    H       H     H H     H H       \n";
                    cout << "   H    HHHHHHH  HHHHH     HHHHHHH HHHHHHH  HHHHH  HHHHHH \n";
                }
            }
        }

        if (p->getName() == bitCarriage) {
            score = p->progress * 100 / maxProgress;//percentage from all way
        }

        p->speed += (rand() % 2 - 1);// speed change randomly every step, that will average speed difference
        if (p->speed < 0) p->speed = 1; // to prevent moving backwards
        p->progress += p->speed;

        if (p->getDirection() == STOP) p->setDirection(DOWN);
        //here is logic to put carriages on their tails, based on index that is name here. For simplicity
        if (p->y >= height - p->getName()) { p->setDirection(RIGHT); }
        if (p->x >= width - p->getName()) { p->setDirection(UP); }
        if (p->x > 8 && p->y < p->getName()) p->setDirection(LEFT);
        if (p->y < 8 && p->x < p->getName() + 1) p->setDirection(DOWN);

        //new trap is placed only on the way
        if (p->name == 8) {
            if (p->getDirection() == DOWN) {
                trapX = (rand() % 8);
                trapY = rand() % 40;
            }
            else if (p->getDirection() == RIGHT) {
                trapX = (rand() % 40);
                trapY = rand() % 8 + 32;
            }
            else if (p->getDirection() == UP) {
                trapX = (rand() % 8 + 32);
                trapY = rand() % 40;
            }
            else if (p->getDirection() == LEFT) {
                trapX = (rand() % 40);
                trapY = rand() % 8;
            }
        }

        if (p->getDirection() == DOWN) {
            p->y = p->y + p->speed;
        }
        else if (p->getDirection() == RIGHT) {
            p->x = p->x + p->speed;
        }
        else if (p->getDirection() == UP) {
            p->y = p->y - p->speed;
        }
        else if (p->getDirection() == LEFT) {
            p->x = p->x - p->speed;
        }
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
#if __APPLE__
        #include "TargetConditionals.h"
        usleep(500);
        #if TARGET_OS_IPHONE && TARGET_IPHONE_SIMULATOR
            printf("iPhone stimulator\n");
        #elif TARGET_OS_IPHONE
            printf("iPhone\n");
        #elif TARGET_OS_MAC
            printf("MacOS\n");
        #else
            printf("Other Apple OS\n");
        #endif
#else
        printf("Not an Apple OS\n");
    #endif
        
      
    }
    return 0;
}
