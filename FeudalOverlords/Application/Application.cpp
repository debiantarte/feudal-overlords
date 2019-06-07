// Application.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

#include <SFML/Graphics.hpp>
#include <libqhullcpp/Qhull.h>
#include <libqhullcpp/QhullFacetList.h>
#include <libqhullcpp/RboxPoints.h>

#include "../FeudalOverlordsLibrary/Window.h"
#include "../FeudalOverlordsLibrary/GameManager.h"

using namespace std;
using namespace orgQhull;

int main()
{
	/* WIP : draft to use qhull and voronoi !*/
	
	RboxPoints rbox("100");
	Qhull q(rbox, "qvoronoi s o");
	QhullFacetList facets = q.facetList();
	cout << facets;
	

	vector<shared_ptr<Player>> players;
	players.push_back(make_shared<Player>((string) "xXXTesterXXx"));
	Window window(1280, 720);
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
		}
	}
}
