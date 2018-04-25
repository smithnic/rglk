#ifndef _AREA_
#define _AREA_
#include <string.h>
#include <stdexcept>
#include <string>
#include "util.hpp"
using namespace std;

class Area {
  public:
    Area();
    Area(string bg);
    string background();
    char getTile(int r, int c);
  private:
    char map[MAX_R][MAX_C + 1];
};


#endif
