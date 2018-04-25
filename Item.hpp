#ifndef _ITEM_
#define _ITEM_

enum ItemType { HP, POW, RNG, WPEN };

class Item {
  public:
    Item(int r, int c);
    Item(ItemType t, int r, int c);
    Item(ItemType t, int v, int r, int c);
    ItemType getType();
    int getVal();
    int getR();
    int getC();
    char getSymbol();
  private:
    ItemType type;
    int val;
    int r;
    int c;
};


#endif
