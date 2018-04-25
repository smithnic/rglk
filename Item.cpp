#include <stdlib.h>
#include "Item.hpp"

Item::Item(int r, int c) {
  int rnd = rand() % 4;
  type = ItemType(rnd);
  val = 10;
  this->r = r;
  this->c = c;
}

Item::Item(ItemType t, int r, int c) {
  type = t;
  val = 10;
  this->r = r;
  this->c = c;
}


Item::Item(ItemType t, int v, int r, int c) {
  type = t;
  val = v;
  this->r = r;
  this->c = c;
}

ItemType Item::getType() { return type; }
int Item::getVal() { return val; }
int Item::getR() { return r; }
int Item::getC() { return c; }

char Item::getSymbol() {
  switch (type) {
    case HP:
      return '+';
    case POW:
      return '@';
    case RNG:
      return '~';
    case WPEN:
      return '#';
    default:
      return '\0';
  }
}

