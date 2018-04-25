#include "P1.hpp"
#include "util.hpp"

P1::P1() {
  p_r = 0;
  p_c = 0;
  health = 100;
  power = 10;
  range = 6;
  w_pen = false;
  w_pen_time = 0;
}

P1::P1(int r, int c) {
  p_r = r;
  p_c = c;
  health = 100;
  power = 10;
  range = 6;
  w_pen = false;
  w_pen_time = 0;
}

int P1::getR() { return p_r; }
int P1::getC() { return p_c; }
int P1::getHealth() { return health; }
int P1::getPower() { return power; }
int P1::getRange() { return range; }
bool P1::getWPen() { return w_pen; }
void P1::setLoc(int r, int c) { p_r = r; p_c = c; }

void P1::setWPen(int time) {
  if (time > 0) {
    w_pen = true;
    w_pen_time = time;
  }
  else {
    w_pen = false;
    w_pen_time = 0;
  }
}

int P1::takeDamage(int pwr) {
  health -= pwr;
  return getHealth();
}

bool P1::move(int dir, char tile) {
  if (!canWalk(tile)) {
    return false;
  }
  switch (dir) {
    case 0: // North
      if (getR() > 0) {
        p_r -= 1;
      }
      else {
        return false;
      }
      break;
    case 1: // East 
      if (getC() < MAX_C - 1) {
        p_c += 1;
      }
      else {
        return false;
      }
      break;
    case 2: // South 
      if (getR() < MAX_R - 1) {
        p_r += 1;
      }
      else {
        return false;
      }
      break;
    case 3: // West 
      if (getC() > 0) {
        p_c -= 1;
      }
      else {
        return false;
      }
      break;
    default:
      break;
  }
  return true;
}

int P1::addHealth(int val) {
  health += val;
  return getHealth();
}

int P1::addPower(int val) {
  power += val;
  return getPower();
}

int P1::addRange(int val) {
  range += val;
  return getRange();
}

void P1::takeItem(Item i) {
  switch (i.getType()) {
    case HP:
      addHealth(i.getVal());
      break;
    case POW:
      addPower(i.getVal() / 5);
      break;
    case RNG:
      addRange(i.getVal() / 10);
      break;
    case WPEN:
      setWPen(i.getVal() * 3);
    default:
      break;
  }
}

void P1::tick() {
  if (w_pen) {
    w_pen_time--;
    if (w_pen_time <= 0) {
      w_pen = false;
      w_pen_time = 0;
    }
  }
}

