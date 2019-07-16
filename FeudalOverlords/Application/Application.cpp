// Application.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "../FeudalOverlordsLibrary/Window.h"
#include "../FeudalOverlordsLibrary/GameManager.h"

#include <TGUI/TGUI.hpp>
#include <string>

using namespace std;

#define WINDOW_WIDTH	800
#define WINDOW_HEIGHT	700

int main()
{
	vector<shared_ptr<Player>> players;
	players.push_back(make_shared<Player>((string) "Princess Celestia"));
	players.push_back(make_shared<Player>((string) "Princess Luna"));
	Window window(WINDOW_WIDTH, WINDOW_HEIGHT);
	GameManager gameManager(0, players, pair<int, int>(window.dimensions.first, window.dimensions.second* 6/7), conquest);
	tgui::Gui gui{ window };
	sf::Music music;
	if (music.openFromFile("../../Assets/Musics/lunar_dawn_1_0.ogg"))
	{
		music.setLoop(true);
		music.play();
	}
	sf::Texture selectTex;
	sf::Texture targetTex;
	sf::Texture emptyTex;
	string selectTrp;
	string targetTrp;
	
	sf::RectangleShape background(sf::Vector2f(1000.0, 800.0));
	background.setFillColor(sf::Color::White);

	try 
	{
		window.buildGUI(gui, selectTex, targetTex, selectTrp, targetTrp,
			gameManager.getSelectedOwner(), gameManager.getTargetOwner(),
			gameManager.players[gameManager.currentPlayerId]->getName());
	}
	catch (const tgui::Exception& except)
	{
		std::cerr << "Failed to load TGUI widgets : " << except.what() << std::endl;
		return EXIT_FAILURE;
	}

#ifdef DEBUG
	sf::CircleShape c(3);
	c.setFillColor(sf::Color::Red);
#endif // DEBUG
	
	int notificationId = 0;
	
	while (window.isOpen())
	{

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
			music.stop();
			window.close();
		}
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Key::M) {
				if (music.getStatus() == sf::SoundSource::Status::Playing) {
					music.pause();
				}
				else if (music.getStatus() == sf::SoundSource::Status::Stopped || music.getStatus() == sf::SoundSource::Status::Paused) {
					music.play();
				}
			}
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
				
				#ifdef DEBUG
				c.setPosition(sf::Vector2f((float)sf::Mouse::getPosition(window).x, (float)sf::Mouse::getPosition(window).y));
				#endif // DEBUG
			}
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Key::Space) {
				string winner = gameManager.nextTurn();
				if (winner != "")
				{
					gui.get("winBox")->cast<tgui::MessageBox>()->setText(winner + " has won ! Hurray !");
					gui.get("winBox")->cast<tgui::MessageBox>()->setVisible(true);
				}
				else
				{
					gui.get("notifBox")->cast<tgui::ListBox>()->addItem("It's " + gameManager.players[gameManager.currentPlayerId]->getName() + "'s turn !", to_string(notificationId));
					notificationId++;
				}
			}
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Key::Enter)
			{
				string targetOwner = gameManager.getTargetOwner();
				string selectOwner = gameManager.getSelectedOwner();
				
				auto res = gameManager.attack();
				switch (res) {
				case impossible: gui.get("notifBox")->cast<tgui::ListBox>()->addItem("This movement is impossible.");
					break;
				case victory: gui.get("notifBox")->cast<tgui::ListBox>()->addItem(targetOwner + "'s " + gameManager.board.target->getTypeName()
					+ " has been conquered", to_string(notificationId));
					break;
				case defeat: gui.get("notifBox")->cast<tgui::ListBox>()->addItem(targetOwner + "'s " + gameManager.board.target->getTypeName()
					+ " has succesfully defended !", to_string(notificationId)); 
					break;
				case movement: gui.get("notifBox")->cast<tgui::ListBox>()->addItem(targetOwner + "'s " + gameManager.board.target->getTypeName()
					+ " has been reinforced !", to_string(notificationId)); 
					break;
				}
				notificationId++;
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
			selectTrp = to_string(gameManager.board.selected->getTroops().getAmount());
		}
		else
		{
			selectTex = emptyTex;
			selectTrp = "";
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
			targetTrp = to_string(gameManager.board.target->getTroops().getAmount());
		}
		else
		{
			targetTex = emptyTex;
			targetTrp = "";
		}

		window.clear();
		window.draw(background);
		gameManager.board.display(window);
		window.updateGUI(gui, selectTex, targetTex, selectTrp, targetTrp,
			gameManager.getSelectedOwner(), gameManager.getTargetOwner(),
			gameManager.players[gameManager.currentPlayerId]->getName()); //update all widgets' infos
		gui.draw(); // Draw all widgets

#ifdef DEBUG
		window.draw(c);
#endif // DEBUG
		
		window.display();
	}
}
 