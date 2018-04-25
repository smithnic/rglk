#ifndef _RGLKUTIL_
#define _RGLKUTIL_
#include <string>
using namespace std;

static const int MAX_R = 24;
static const int MAX_C = 80;
static int TOTAL_SPACE = MAX_R * MAX_C;

static const char* NAMES_PRE[] = {"Er", "Bea", "Na", "Su", "Gi", "Vic", "Con",
  "Roc", "Mau", "Po", "Zac"};
static const int NAMES_PRE_LEN = 11;
static const char* NAMES_POST[] = {"san", "cino", "rad", "rine", "ssepe", 
  "nice", "appersan", "eek", "muel", "ony"};
static const int NAMES_POST_LEN = 10;

bool canWalk(char c);
bool canLaser(char c);

string nameGen();

#endif
