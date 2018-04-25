#include "Area.hpp"
using namespace std;

Area::Area() {
  for (int i = 0; i < MAX_R; i++) {
    for (int j = 0; j < MAX_C; j++) {
      map[i][j] = '-';
    } 
    map[i][MAX_C] = 0;
  }
}

Area::Area(string bg) {
  int c = 0;
  for (int i = 0; i < MAX_R; i++) {
    for (int j = 0; j < MAX_C; j++) {
      map[i][j] = bg[c];
      c += 1;
    }
    map[i][MAX_C] = '\0';
  }
} 

string Area::background() {
  string result = "";
  for (int i = 0; i < MAX_R; i++) {
    result += map[i];
  }
  return result;
}

char Area::getTile(int r, int c) {
  // If not in range return a null byte
  if (r >= MAX_R || c >= MAX_C || r < 0 || c < 0) {
    return '\0';
  }
  else {
    return map[r][c];
  }
}
