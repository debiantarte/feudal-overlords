#include "stdafx.h"
#include "GameManager.h"
#include <cassert>



GameManager::GameManager(int nbrAIs, vector<shared_ptr<Player>> players, pair<int, int> dimensions) :
	GameManager(nbrAIs, players, dimensions, 5)
{
}

GameManager::GameManager(int nbrAIs, vector<shared_ptr<Player>> players, pair<int, int> dimensions, int finishTurn=5) :
	nbrPlayers(players.size()), nbrAIs(nbrAIs), players(players),
	board(players, dimensions.first, dimensions.second, NBR_POINTS),
	endingCond(turnLimit), turn(0), finishTurn(finishTurn), currentPlayerId(0)
{
	assert(nbrAIs >= 0);
}

void GameManager::nextTurn()
{
	// take all the players and iterate through them
	// then the AIs
	if (isGameFinished()) { // TODO : show this on the Window
		Lord& winner = winner();
	}
	if (board.selected != nullptr)
	{
		board.selected->setColor(sf::Color::White);
		board.selected = nullptr;
	}
	if (board.target != nullptr)
	{
		board.target->setColor(sf::Color::White);
		board.target = nullptr;
	}
	if (currentPlayerId < players.size() - 1)
	{
		currentPlayerId++;
	}
	else
	{
		turn++;
		currentPlayerId = 0;
		regenTerritories();
	}
	cout << "Turn [" << turn << "] Current player : " << players[currentPlayerId]->getName() << endl;
}

void GameManager::regenTerritories()
{
	for (auto& territory : board.territories)
	{
		int resetValue = territory->getTroops().getMaxAmount();
		territory->setTroops(resetValue);
	}
}

void GameManager::playerTurn()
{
	// it's player's turn
	// we should display that it's their turn
	// then act depending on their input
	// select territory : left click
	// to move troop or resources to another territory : right click on the destination territory
	auto player = players[currentPlayerId];
}


shared_ptr<Lord> GameManager::winner()
{
	if (not(isGameFinished()))
	{
		return nullptr;
	}
	// else, it is the player who has the most territories
	if (endingCond == turnLimit)
	{
		shared_ptr<	Lord> lord = nullptr;
		int count = 0;
		for (auto& mapElement : territoryCount())
		{
			if (count < mapElement.second)
			{
				lord = mapElement.first;
				count = mapElement.second;
			}
		}
		return lord;
	} elif (endingCond == conquest)
	{
		for (auto board.territories: &territory) {
			if (territory->getType() == capital) {
				return territory->getOwner()
			}
		}

	}
}

/**
	For now, it cannot act properly if the ending condition is conquest.
*/
bool GameManager::isGameFinished()
{
	// function to check whether there is only one owner of all the capitals

	// if total conquest has been achieved, or it is the last turn
	if (territoryCount().size() == 1
	|| (endingCond == turnLimit && turn >= finishTurn))
	{
		return true;
	} elif (endingCond == conquest)
	{
	for (auto board.territories: &territory) {
		string prevLordName = null;
		if (territory->getType() == capital) {
			string name = territory->getOwner()->getName();
			if (prevLordName == null) {
				prevLordName = name;
			} else if (prevLordName != name) {
				return false;
			}
		}
	}
	return true;
	}
	else
	{
		return false;
	}
}


map<shared_ptr<Lord>, int> GameManager::territoryCount()
{
	return board.territoryCount();
}

void GameManager::setTurn(int turn_)
{
	turn = turn_;
}

void GameManager::moveTroops(Territory* attacker, Territory* defender)
{
	if (attacker->getOwner() == players[currentPlayerId])
	{
		int defendingTroops = defender->getTroops().getAmount();
		int attackingTroops = attacker->getTroops().getAmount();
		if (defender->getOwner() != players[currentPlayerId])
		{
			int defenseMargin = (defendingTroops - attackingTroops < 0) ? 0 : defendingTroops - attackingTroops;
			int attackingMargin = (attackingTroops - defendingTroops < 0) ? 0 : attackingTroops - defendingTroops;
			defender->setTroops(defenseMargin);
			attacker->setTroops(attackingMargin);
			std::cout << "Attacker's troops reduced to : " << attacker->getTroops().getAmount() << std::endl;
			std::cout << "Defender's troops reduced to : " << defender->getTroops().getAmount() << std::endl;
			if (attackingMargin > 0 && defenseMargin == 0)
			{
				defender->setOwner(attacker->getOwner());
				std::cout << "Defender's owner becomes : " << getTargetOwner() << std::endl;
				defender->newOwnerColor(attacker->getColor());
			}
		}
		else
		{
			defender->setTroops(defendingTroops + attackingTroops);
			attacker->setTroops(0);
		}
	}
}

void GameManager::attack()
{
	if (board.selected != nullptr && board.target != nullptr && board.selected->getOwner() == players[currentPlayerId] && board.target->isAdjacent(board.selected->getShape()))
	{
		moveTroops(board.selected, board.target);
	}
}

string GameManager::getSelectedOwner()
{
	if (board.selected == nullptr)
	{
		return "";
	}
	return board.selected->getOwner()->getName();
}

string GameManager::getTargetOwner()
{
	if (board.target == nullptr)
	{
		return "";
	}
	return board.target->getOwner()->getName();
}
