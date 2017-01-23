#pragma 
#include "Item.h"
class Kompas : public Item
{
public:
	Kompas();
	~Kompas();
	Kompas(int amountIn) : Item(amountIn) {};
	void useItem(Player* p);
	void setName();
};

