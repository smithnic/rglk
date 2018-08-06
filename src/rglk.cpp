#include <stdlib.h>
#include <time.h>
#include "rglk.hpp"
#include "Areas.hpp"
using namespace std;

// This function will hang until there is a character input to return
unsigned char inputWaiter() {
#ifdef _WIN32
  while (!kbhit());
  char c = getch();
  return c;
#endif
#ifdef __linux__
  char c = getch(); 
  return c;
#endif
}

void sysSleep(int ms) {
#ifdef _WIN32
  Sleep(ms);
#endif
#ifdef __linux__
  usleep(ms*1000);
#endif
}

void sysClear() {
#ifdef _WIN32
  system("cls");
#endif
#ifdef __linux__
  clear();
  refresh();
#endif
}

// Adds a character into our string based map model and returns the result
string Rglk::addChar(char tile, int r, int c, string bg) {
  int pos = r * MAX_C + c;
  if (pos >= bg.length() || pos < 0) return bg;
  string result = bg.substr(0, pos) + string(1, tile) + bg.substr(pos + 1); 
  return result; 
}

// Add the player at the given position
string Rglk::addP(int r, int c, string bg) {
  return Rglk::addChar('&', r, c, bg);
}

// Add an enemy at the current position
string Rglk::addEnemy(int r, int c, string bg) {
  return Rglk::addChar('$', r, c, bg);
}

State Rglk::getState() {
  return state;
}

void Rglk::setState(State s) {
  state = s;
} 

// Big switch for input while playing the game 
void Rglk::action(char c) {
  char cl = tolower(c, locale());
  switch (cl) {
    case 'w':
      if (entityPresent(p.getR() - 1, p.getC())) {
        // Just don't move
        break;
      }
      if (itemPresent(p.getR() - 1, p.getC())) {
        p.takeItem(getItem(p.getR() - 1, p.getC()));
        removeItem(p.getR() - 1, p.getC());
      }
      p.move(0, curArea.getTile(p.getR() - 1, p.getC()));
      break;
    case 'd':
      if (entityPresent(p.getR(), p.getC() + 1)) {
        break;
      }
      if (itemPresent(p.getR(), p.getC() + 1)) {
        p.takeItem(getItem(p.getR(), p.getC() + 1));
        removeItem(p.getR(), p.getC() + 1);
      }
      p.move(1, curArea.getTile(p.getR(), p.getC() + 1));
      break;
    case 's':
      if (entityPresent(p.getR() + 1, p.getC())) {
        break;
      }
      if (itemPresent(p.getR() + 1, p.getC())) {
        p.takeItem(getItem(p.getR() + 1, p.getC()));
        removeItem(p.getR() + 1, p.getC());
      }
      p.move(2, curArea.getTile(p.getR() + 1, p.getC()));
      break;
    case 'a':
      if (entityPresent(p.getR(), p.getC() - 1)) {
        break;
      }
      if (itemPresent(p.getR(), p.getC() - 1)) {
        p.takeItem(getItem(p.getR(), p.getC() - 1));
        removeItem(p.getR(), p.getC() - 1);
      }
      p.move(3, curArea.getTile(p.getR(), p.getC() - 1));
      break;
    case 'i':
      Rglk::laser(cl); 
      break;
    case 'l':
      Rglk::laser(cl); 
      break;
    case 'k':
      Rglk::laser(cl); 
      break;
    case 'j':
      Rglk::laser(cl); 
      break;
    case 'p':
      state = MENU;
      // skip enemy actions here
      return;
    default:
      break;
  }
  // Move enemies
  p.tick();
  enemyActions();
}

// Switch for input in the pause menu 
void Rglk::menuAction(char c) {
  char cl = tolower(c, locale());
  switch (cl) {
    case 'p':
      state = GAME;
      break;
    default:
      break;
  }
}

// Remove an item from the map at the given position
void Rglk::removeItem(int r, int c) {
  for (int i = 0; i < items.size(); i++) {
    if (items[i].getR() == r && items[i].getC() == c) {
      items.erase(items.begin() + i); 
    }
  }
}

// Return the Item at the given position
Item Rglk::getItem(int r, int c) {
  for (Item& i: items) {
    if (i.getR() == r && i.getC() == c) {
      return i;
    }
  }
  // If we got here there is no item
  //TODO Might want to change this to an exception or return some NoItem type
}

// Control enemy actions. Loop through each enemy and determine their movement
// and attacks. Break this down in the future
void Rglk::enemyActions() {
  for (Enemy& e: enemies) {
    if (e.isAggro()) {
      // move towards the player
      int dr = p.getR() - e.getR();
      int dc = p.getC() - e.getC();
      if (abs(dr) + abs(dc) >= 22) {
        //deaggro
        e.setAggro(false);
      }
      else if (abs(dr) + abs(dc) <= e.getRange()) {
        // Enemy attack
        enemyAttack(e.getR(), e.getC(), e.getRange(), e.getPower(), e.getName());
      }
      else {
        int vdir;
        int hdir;
        //attempt to move in the best direction
        //(no pathfinding)
        if (dr >= 0) {
          // down 
          vdir = 2;
        }
        else { //up
          vdir = 0;
        }
        if (dc >= 0) {
          // right
          hdir = 1;
        }
        else { // left
          hdir = 3;
        }
        int rng = rand() % 2;
        if (rng == 0) {
          char t;
          bool ent;
          if (hdir == 1) {
            ent = entityPresent(e.getR(), e.getC() + 1);
            t = curArea.getTile(e.getR(), e.getC() + 1); 
          }
          else {
            ent = entityPresent(e.getR(), e.getC() - 1);
            t = curArea.getTile(e.getR(), e.getC() - 1);
          }
          if (!ent) {
            e.move(hdir, t);
          }
        }
        else {
          char t;
          bool ent;
          if (vdir == 2) {
            ent = entityPresent(e.getR() + 1, e.getC());
            t = curArea.getTile(e.getR() + 1, e.getC()); 
          }
          else {
            ent = entityPresent(e.getR() - 1, e.getC());
            t = curArea.getTile(e.getR() - 1, e.getC());
          }
          if (!ent) {
            e.move(vdir, t);
          }
        }
      }
    }
    else {
      // move randomly
      int rn = rand() % 4;
      switch (rn) {
      case 0:
        if (entityPresent(e.getR() - 1, e.getC())) continue;
        e.move(0, curArea.getTile(e.getR() - 1, e.getC()));
        break;
      case 1:
        if (entityPresent(e.getR(), e.getC() + 1)) continue;
        e.move(1, curArea.getTile(e.getR(), e.getC() + 1));
        break;
      case 2:
        if (entityPresent(e.getR() + 1, e.getC())) continue;
        e.move(2, curArea.getTile(e.getR() + 1, e.getC()));
        break;
      case 3:
        if (entityPresent(e.getR(), e.getC() - 1)) continue;
        e.move(3, curArea.getTile(e.getR(), e.getC() - 1));
        break;
      default:
        break;
      }
      if (abs(p.getR() - e.getR()) + abs(p.getC() - e.getC()) < 7) {
        e.setAggro(true);
      }
    }
  }
}

// Use the players laser attack. Directions in "ilkj" == North East South West
void Rglk::laser(char direction) {
  // Make the display with the laser
  int curY = p.getR();
  int curX = p.getC();
  string bg = display();
  char rep;
  string enemy_dam = "";
  string enemy_ded = "";
  while (true) {
    switch (direction) {
      case 'i': // Negative y direction (up)
        curY--;
        rep = '^';
        break;
      case 'l': // Positive x direction (right)
        curX++;
        rep = '>';
        break;
      case 'k': // Positive y direction
        curY++;
        rep = 'v';
        break;
      case 'j': // Negative x direction
        curX--;
        rep = '<';
        break;
      default:
        //Should never reach here
        
        break;
    }
    char tile = curArea.getTile(curY, curX);
    if (tile == '|') {
      // Stop the laser if no Wall pen.
      if (!p.getWPen()) {
        break;
      }
      else {
        rep = '#';
      }
    }
    if (tile == '\0' 
        || abs(p.getR() - curY) + abs(p.getC() - curX) > p.getRange()) {
      // Laser is stopped
      break; 
    }
    else {
      // Damage enemies/remove killed
      for (int i = 0; i < enemies.size(); i++) {
        if (enemies[i].getR() == curY && enemies[i].getC() == curX) {
          enemies[i].setAggro(true);
          int hp = enemies[i].takeDamage(p.getPower());
          if (hp <= 0) {
            // Add to enemy_ded
            if (enemy_ded.length() == 0) {
              enemy_ded += enemies[i].getName();
            }
            else {
              enemy_ded += " ";
              enemy_ded += enemies[i].getName();
            }
            // Drop the item
            items.push_back(enemies[i].getDrop());
            // Remove the enemy
            enemies.erase(enemies.begin() + i); 
            i -= 1;
          }
          else {
            // Add to enemy_dam
            if (enemy_dam.length() == 0) {
              enemy_dam += enemies[i].getName();
            }
            else {
              enemy_dam += " ";
              enemy_dam += enemies[i].getName();
            }
          }
        }
      }
      if (!entityPresent(curY, curX)) {
        bg = Rglk::addChar(rep, curY, curX, bg);
      }
    }
  }
  // Draw the laser display and wait a second
  draw(bg); 
  sysSleep(SLEEPTIME_MS);
  if (enemy_dam.length() != 0 && enemy_ded.length() != 0) {
    message("Player: attacked " + enemy_dam + ", eliminated " + enemy_ded);
  }
  else if (enemy_dam.length() == 0 && enemy_ded.length() != 0) {
    message("Player: eliminated " + enemy_ded);
  }
  else if (enemy_dam.length() != 0 && enemy_ded.length() == 0) {
    message("Player: attacked " + enemy_dam);
  }
}

// Enemy cloud attack. Creates a diamond cloud around the enemy
void Rglk::enemyAttack(int r, int c, int range, int power, string name) {
  int curR;
  int curC;
  bool kill = false;
  string bg = display();
  for (curR = r - range; curR  < r + range + 1; curR++) {
    for (curC = c - range; curC < c + range + 1; curC++) {
      if (abs(r - curR) + abs(c - curC) > range) continue;
      else {
        if (p.getR() == curR && p.getC() == curC) {
          int hp = p.takeDamage(power);
          if (hp <= 0) {
            // Game over
            kill = true;
            state = GAMEOVER;
            p.setLoc(-1, -1);
          }
        }
        else {
          if (!entityPresent(curR, curC)
              && canWalk(curArea.getTile(curR, curC))) {
            bg = Rglk::addChar('x', curR, curC, bg);
          }
        }
      }
    }
  }
  // Draw the enemy attack
  draw(bg);
  sysSleep(SLEEPTIME_MS);
  if (kill) {
    message(name + " killed the player");
  }
  else {
    message(name + " attacked the player for " + to_string(power)); 
  }
}

Rglk::Rglk() {
      level = 1;
      curArea = getArea(level);
      p = P1(1, 1);
      state = GAME;
      enemies = addEnemies(level); 
      items = vector<Item>();
}

// Return a string representing the current map (attacks are done elsewhere)
string Rglk::display() {
  if (state == GAME) {
    string s = addP(p.getR(), p.getC(), curArea.background());
    for (Item& i: items) {
      s = addChar(i.getSymbol(), i.getR(), i.getC(), s);
    }
    for (Enemy& e: enemies) {
      s = addEnemy(e.getR(), e.getC(), s);
    }
    return s;
  }
  else if (state == MENU) {
    string healthString = to_string(p.getHealth());
    string powerString = to_string(p.getPower());
    string rangeString = to_string(p.getRange());
    if (healthString.length() == 1) healthString = "  " + healthString;
    else if (healthString.length() == 2) healthString = " " + healthString;
    if (powerString.length() == 1) powerString = "  " + powerString;
    else if (powerString.length() == 2) powerString = " " + powerString;
    if (rangeString.length() == 1) rangeString = "  " + rangeString;
    else if (rangeString.length() == 2) rangeString = " " + rangeString;
    string result = string(38, '*') + "MENU" + string(38, '*')
      + "*** HEALTH: " + healthString + " " + string(64, '*')
      + "*** POWER:  " + powerString + " " + string(64, '*')
      + "*** RANGE:  " + rangeString + " " + string(64, '*')
      + string(320, '*');
    int requiredLength = MAX_R * MAX_C;
    result.insert(result.length(), requiredLength - result.length(), ' ');
    return result;
  }
  else if (state == GAMEOVER) {
    string result =  string(80, '*')
      + "*** GAME OVER " + string(66, '*')
      + "*** Press 'n' to restart " + string(55, '*')
      + string(400, '*');
    int requiredLength = MAX_R * MAX_C;
    result.insert(result.length(), requiredLength - result.length(), ' ');
    return result;
  }
}

// Determine if a player/enemy exists at the given coords
bool Rglk::entityPresent(int r, int c) {
  if (p.getR() == r && p.getC() == c) return true;
  for (Enemy& e: enemies) {
    if (e.getR() == r && e.getC() == c) return true;
  }
  return false;
}

// Determine if an item exists at the given coords
bool Rglk::itemPresent(int r, int c) {
  for (Item& i: items) {
    if (i.getR() == r && i.getC() == c) return true;
  }
  return false;
}

// Prints a message at the top of the console
void Rglk::message(string msg) {
#ifdef _WIN32
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD coord;
  coord.X = 0;
  coord.Y = 3;
  if (!SetConsoleCursorPosition(hConsole, coord)) exit(1);
  cout << "*** " << msg << " ***";
#endif
#ifdef __linux__
  string outstring = string("*** ") + msg + string(" ***"); 
  mvwaddstr(mainwin, 0, 0, outstring.c_str()); 
  refresh();
#endif
  sysSleep(SLEEPTIME_MS);
}

void draw(string bg) {
#ifdef __linux__
  sysClear();
#endif
#ifdef _WIN32
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD coord;
  coord.X = 0;
  coord.Y = 3;
  if (!SetConsoleCursorPosition(hConsole, coord)) {
      // Something with the Windows console went wrong
      cerr << "The console host has stopped working, terminating..." << endl;
      exit(1);
  }
  for (int i = 0; i < (MAX_R - 1) * 80; i+=80) {
    cout << bg.substr(i, 80) << endl; 
  }
#endif
#ifdef __linux__
  for (int i = 0; i < (MAX_R - 1) * 80; i+=80) {
    string line = bg.substr(i, 80);
    line += "\n";
    printw(line.c_str()); 
  }
  refresh();
#endif
}

// Main game loop
int main(int argc, char* argv[]) {
  // Seed random numbers
  srand(time(NULL));
#ifdef __linux__
  mainwin = initscr();
#endif
  Rglk rglk = Rglk(); 
  unsigned char buf;
  sysClear();
  while (true) {
    sysClear(); 
    draw(rglk.display());
    buf = inputWaiter();
    if (buf == '0') {
#ifdef _WIN32
      system("cls");
#endif
#ifdef __linux__
      clear();
      refresh();
#endif
      break;
    }
#ifdef __linux__
    // Ignore extended characters spit out by resizing window
    else if (buf == 154) continue;
#endif
    if (rglk.getState() == GAME) {
      rglk.action(buf);
    }
    else if (rglk.getState() == MENU) {
      rglk.menuAction(buf);
    }
    else if (rglk.getState() == GAMEOVER) {
      char cl = tolower(buf, locale());
      if (cl == 'n') {
        rglk = Rglk();
        rglk.setState(GAME);
      }
    }
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord;
    coord.X = 0;
    coord.Y = 3;
    if (!SetConsoleCursorPosition(hConsole, coord)) exit(1);
#endif
#ifdef __linux__
    refresh();
#endif
  }
#ifdef __linux__
  endwin();
#endif
  exit(0);
}
