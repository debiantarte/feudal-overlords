#pragma once
#include "Lord.h"
#include "Territory.h"
#include <memory>

using namespace std;

class Player :
	public Lord
{
public:
	Player(string name);
	//~Player();
	void attack(Territory);
	void buy(Territory);
	void negociateWith(Lord&);
	void threaten(Lord&);
	void raiseTroops(Territory);
	
	virtual void display();

private:
	string name;
};

