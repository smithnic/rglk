#include "util.hpp"
#include "Enemy.hpp"

Enemy::Enemy(int r, int c) {
  this->r = r;
  this->c = c;
  name = nameGen();
  aggro = false;
  power = 10;
  health = 30;
  range = newRange(4, 2);
}

// Returns a new range between base and (base + d)
int Enemy::newRange(int base, int d) {
  return base + (rand() % d);
}

int Enemy::getR() {
  return r;
}

int Enemy::getC() {
  return c;
}

int Enemy::getHealth() {
  return health;
}

int Enemy::getPower() {
  return power;
}

int Enemy::getRange() {
  return range;
}

string Enemy::getName() {
  return name;
}

bool Enemy::isAggro() {
  return aggro;
}

bool Enemy::move(int dir, char tile) {
  if (!canWalk(tile)) {
    return false;
  }
  switch (dir) {
    case 0: // North
      if (getR() > 0) {
        r -= 1;
      }
      else {
        return false;
      }
      break;
    case 1: // East 
      if (getC() < MAX_C - 1) {
        c += 1;
      }
      else {
        return false;
      }
      break;
    case 2: // South 
      if (getR() < MAX_R - 1) {
        r += 1;
      }
      else {
        return false;
      }
      break;
    case 3: // West 
      if (getC() > 0) {
        c -= 1;
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

// Returns the health left after damage
int Enemy::takeDamage(int power) {
  if (power < 0) return getHealth();
  health -= power;
  return getHealth();
}

void Enemy::setAggro(bool b) {
  aggro = b;
}

Item Enemy::getDrop() {
  return Item(getR(), getC());
}

