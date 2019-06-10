// Application.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

#include <SFML/Graphics.hpp>

#include "../FeudalOverlordsLibrary/Window.h"
#include "../FeudalOverlordsLibrary/GameManager.h"

#include <TGUI/TGUI.hpp>

using namespace std;

int main()
{
	vector<shared_ptr<Player>> players;
	players.push_back(make_shared<Player>((string) "xXXTesterXXx"));
	Window window(800, 700);
	GameManager gameManager(0, players, pair<int, int>(window.dimensions.first, window.dimensions.second* 6/7));
	tgui::Gui gui{ window };
	sf::Texture selectTex;
	sf::Texture targetTex;
	try 
	{
		window.buildGUI(gui, selectTex, targetTex);
	}
	catch (const tgui::Exception& except)
	{
		std::cerr << "Failed to load TGUI widgets : " << except.what() << std::endl;
		return EXIT_FAILURE;
	}
	sf::CircleShape c(3);
	c.setFillColor(sf::Color::Red);
	
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
			{
				window.setView(sf::View(sf::FloatRect(0.0, 0.0, (float)event.size.width, (float)event.size.height)));
				window.display();
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				gameManager.board.onClick(pair<int, int>(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y),
					event.mouseButton.button, window);
				
				c.setPosition(sf::Vector2f((float)sf::Mouse::getPosition(window).x, (float)sf::Mouse::getPosition(window).y));
				
			}

			gui.handleEvent(event); // tell all tgui widgets about events happening
		}
		if (gameManager.board.selected != nullptr)
		{
			switch (gameManager.board.selected->getType())
			{
			case capital:
				selectTex = gameManager.board.cityTex;
				break;
			case grasslands:
				selectTex = gameManager.board.grassTex;
				break;
			case countryside:
				selectTex = gameManager.board.dirtTex;
				break;
			case highlands:
				selectTex = gameManager.board.mountainTex;
				break;
			}
		}
		else
		{
			selectTex = sf::Texture();
		}
		if (gameManager.board.target != nullptr)
		{
			switch (gameManager.board.target->getType())
			{
			case capital:
				targetTex = gameManager.board.cityTex;
				break;
			case grasslands:
				targetTex = gameManager.board.grassTex;
				break;
			case countryside:
				targetTex = gameManager.board.dirtTex;
				break;
			case highlands:
				targetTex = gameManager.board.mountainTex;
				break;
			}
		}
		else
		{
			targetTex = sf::Texture();
		}
		
		try
		{
			window.buildGUI(gui, selectTex, targetTex);
		}
		catch (const tgui::Exception& except)
		{
			std::cerr << "Failed to load TGUI widgets : " << except.what() << std::endl;
			return EXIT_FAILURE;
		}
		
		window.clear();
		gameManager.board.display(window);
		gui.draw(); // Draw all widgets
		window.draw(c);
		window.display();
	}
}
 