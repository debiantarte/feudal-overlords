// Application.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "../FeudalOverlordsLibrary/Window.h"
#include "../FeudalOverlordsLibrary/GameManager.h"
#include <SFML/Graphics.hpp>

using namespace std;

int main()
{
	vector<shared_ptr<Player>> players;
	players.push_back(make_shared<Player>((string) "xXXTesterXXx"));
	GameManager gameManager = GameManager(0, players);
	Window window(800, 600);
	window.showUI();
	while (window.isOpen())
	{
		gameManager.board.display();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
			window.close();
		}
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}
}
