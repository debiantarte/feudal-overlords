#include "stdafx.h"
#include "Player.h"


Player::Player(string name) : name(name)
{
}

/*
Player::~Player()
{
}
*/

void Player::attack(Territory)
{

}

void Player::buy(Territory)
{

}

void Player::negociateWith(Lord&)
{

}

void Player::threaten(Lord&)
{

}

void Player::raiseTroops(Territory)
{

}

unique_ptr<sf::Drawable> Player::display(Window& window)
{
	return make_unique<sf::RectangleShape>(sf::RectangleShape());
}