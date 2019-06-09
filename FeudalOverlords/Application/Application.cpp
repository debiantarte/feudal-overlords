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
#include <TGUI/TGUI.hpp>

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
	tgui::Gui gui{ window };
	
	try 
	{
		window.buildGUI(gui);
	}
	catch (const tgui::Exception& except)
	{
		std::cerr << "Failed to load TGUI widgets : " << except.what() << std::endl;
		return EXIT_FAILURE;
	}
	sf::CircleShape c(3);
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
			if (event.type == sf::Event::MouseButtonPressed) {
				gameManager.board.onClick(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, event.mouseButton.button);
				
				c.setPosition(sf::Vector2f((float)sf::Mouse::getPosition(window).x, (float)sf::Mouse::getPosition(window).y));
				c.setFillColor(sf::Color::Red);
			}

			gui.handleEvent(event); // tell all tgui widgets about events happening
		}
		
		window.clear();
		gameManager.board.display();
		gui.draw(); // Draw all widgets
		window.draw(c);
		window.display();
	}
}
