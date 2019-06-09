// Application.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

#include <SFML/Graphics.hpp>

#include "../FeudalOverlordsLibrary/Window.h"
#include "../FeudalOverlordsLibrary/GameManager.h"

using namespace std;

int main()
{
	/* WIP : draft to use MyGAL and voronoi !*/
	
	

	vector<shared_ptr<Player>> players;
	players.push_back(make_shared<Player>((string) "xXXTesterXXx"));
	Window window(1280, 720);
	GameManager gameManager = GameManager(0, players, 5, 1280, 720);
	
	gameManager.board.display(window);
	window.showUI();
	window.display();
	while (window.isOpen())
	{
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
			window.close();
		}
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::Resized)
				window.display();
		}
	}
}
