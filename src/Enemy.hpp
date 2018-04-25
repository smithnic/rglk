#ifndef _ENEMY_
#define _ENEMY_
#include <string>
#include <stdlib.h>
#include "Item.hpp"
using namespace std;

class Enemy {
  public:
    Enemy(int r, int c); // Random enemy at (r, c)
    int getR();
    int getC();
    int getHealth();
    int getPower();
    int getRange();
    string getName();
    bool isAggro();
    bool move(int dir, char tile);
    int takeDamage(int power);
    void setAggro(bool b);
    Item getDrop();
  private:
    int r;
    int c;
    int health;
    int power;
    int range;
    string name;
    bool aggro;
    int newRange(int base, int d);
};


#endif
