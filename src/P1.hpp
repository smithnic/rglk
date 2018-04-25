#ifndef _P1_
#define _P1_
#include "Item.hpp"

class P1 {
  public:
    P1();
    P1(int r, int c);
    int getR(); 
    int getC();
    int getHealth();
    int getPower();
    int getRange();
    int addHealth(int val);
    int addPower(int val);
    int addRange(int val);
    void setLoc(int r, int c);
    bool move(int dir, char tile);  
    void takeItem(Item i);
    int takeDamage(int pwr);
    bool getWPen();
    void tick(); // Actions that should happen after every move
    void setWPen(int time);
  private:
    int p_r;
    int p_c;
    int health;
    int power;
    int range;
    bool w_pen;
    int w_pen_time;
};
#endif
