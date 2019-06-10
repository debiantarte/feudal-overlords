// Application.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "../FeudalOverlordsLibrary/Window.h"
#include "../FeudalOverlordsLibrary/GameManager.h"

#include <TGUI/TGUI.hpp>

using namespace std;

int main()
{
	vector<shared_ptr<Player>> players;
	players.push_back(make_shared<Player>((string) "xXXTesterXXx"));
	Window window(800, 600);
	GameManager gameManager(0, players, pair<int, int>(800, 500));
	tgui::Gui gui{ window };
	sf::Music music;
	if (music.openFromFile("../../Assets/Musics/lunar_dawn_1_0.ogg"))
		//return -1; // error
	{
		music.setLoop(true);
		music.play();
	}
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
				window.display();
			if (event.type == sf::Event::MouseButtonPressed) {
				gameManager.board.onClick(pair<int, int>(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y),
					event.mouseButton.button, window);
				
				c.setPosition(sf::Vector2f((float)sf::Mouse::getPosition(window).x, (float)sf::Mouse::getPosition(window).y));
				
			}

			gui.handleEvent(event); // tell all tgui widgets about events happening
		}
		
		window.clear();
		gameManager.board.display(window);
		gui.draw(); // Draw all widgets
		window.draw(c);
		window.display();
	}
}
