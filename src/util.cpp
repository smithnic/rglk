#include <stdlib.h>
#include <string>
#include "util.hpp"

bool canWalk(char c) {
  switch (c) {
    case '-': // Floor
      return true;
    case '|': // Wall
      return false;
    default: // Assume no
      return false;
  }
}

bool canLaser(char c) {
  // For now just canWalk
  return canWalk(c);
}

string nameGen() {
  int rpr = rand() % NAMES_PRE_LEN; 
  int rpo = rand() % NAMES_POST_LEN; 
  return string(NAMES_PRE[rpr]) + string(NAMES_POST[rpo]);
}
