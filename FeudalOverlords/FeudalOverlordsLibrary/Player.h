#pragma once
#include "Lord.h"
#include "Territory.h"

class Player :
	public Lord
{
public:
	Player();
	//~Player();
	void attack(Territory);
	void buy(Territory);
	void negociateWith(Lord&);
	void threaten(Lord&);
	void raiseTroops(Territory);
};

