#ifndef _RGLK_
#define _RGLK_
#include <iostream>
#include <string>
#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#endif
#ifdef __linux__
#include <unistd.h>
#include <ncurses.h>
#endif
#include <stdlib.h>
#include <vector>
#include "Area.hpp"
#include "P1.hpp"
#include "Enemy.hpp"
using namespace std;

#ifdef __linux__
WINDOW* mainwin;
#endif

static const int SLEEPTIME_MS = 500;
char inputWaiter();
void draw(string bg);
void sysSleep(int ms);

enum State { GAME, MENU, GAMEOVER };

class Rglk {
  public:
    Rglk();
    string display();
    void action(char input);
    void menuAction(char input);
    void laser(char direction);
    void enemyActions();
    State getState();
    void setState(State s);
    void message(string msg);
  private:
    P1 p;
    vector<Enemy> enemies;
    vector<Item> items;
    Area curArea;
    State state;
    int level;
    string addP(int r, int c, string bg);
    string addEnemy(int r, int c, string bg);
    string addItem(int r, int c, string bg);
    string addChar(char tile, int r, int c, string bg);
    void removeItem(int r, int c);
    void enemyAttack(int r, int c, int range, int power, string name);
    bool entityPresent(int r, int c);
    bool itemPresent(int r, int c);
    Item getItem(int r, int c);
};


#endif
