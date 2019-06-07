// Application.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "../FeudalOverlordsLibrary/Window.h"
#include "../FeudalOverlordsLibrary/GameManager.h"
#include <SFML/Graphics.hpp>

#include <libqhullcpp/Qhull.h>
#include <libqhullcpp/QhullFacetList.h>
#include <libqhullcpp/RboxPoints.h>

using namespace std;

int main()
{
	/* WIP : draft to use qhull and voronoi !
	*/
	
	/*
	RboxPoints rbox;
	rbox.appendRandomPoints("100");
	Qhull qhull;
	qhull.runQhull("", rbox);
	QhullFacetList facets(qhull);
	cout << facets;
	*/

	vector<shared_ptr<Player>> players;
	players.push_back(make_shared<Player>((string) "xXXTesterXXx"));
	Window window(800, 600);
	GameManager gameManager = GameManager(0, players, window);
	
	gameManager.board.display();
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
