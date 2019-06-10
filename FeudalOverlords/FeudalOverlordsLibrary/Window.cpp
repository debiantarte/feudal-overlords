#include "stdafx.h"
#include "Window.h"


Window::Window(int width, int height) : sf::RenderWindow(sf::VideoMode(width, height), "Feudalism Overlords"),
	dimensions(make_pair(width, height))
{
	display();
}


Window::~Window()
{
}

void Window::buildGUI(tgui::Gui& gui, sf::Texture& selectTex, sf::Texture& targetTex, string selTrp, string tgtTrp, string currentPlayer)
{
	sf::Texture uitex;
	assert(uitex.loadFromFile("../../Assets/Textures/UItex.png"));
	sf::Sprite background(uitex);
	background.setScale((float)dimensions.first / uitex.getSize().x, ((float)dimensions.second / 7) / uitex.getSize().y);

	auto back_canvas = tgui::Canvas::create({ (float)dimensions.first, (float)dimensions.second / 7 });
	back_canvas->setPosition(0.0, (float)dimensions.second * 6 / 7);
	back_canvas->clear();
	back_canvas->draw(background);
	back_canvas->display();
	gui.add(back_canvas);

	auto selLabel = tgui::Label::create(selTrp);
	selLabel->setPosition((float)dimensions.first * 0.177, (float)dimensions.second * 0.88);
	gui.add(selLabel, "selection label");

	auto tgtLabel = tgui::Label::create(tgtTrp);
	tgtLabel->setPosition((float)dimensions.first * 0.530, (float)dimensions.second * 0.88);
	gui.add(tgtLabel, "target label");

	sf::Sprite selection(selectTex);
	selection.setScale(1.07 * (float)dimensions.first / 600, 1.04 * (float)dimensions.second / 699);

	auto selec_canvas = tgui::Canvas::create({ 64 * 1.07 * (float)dimensions.first / 600, 65 * 1.04 * (float)dimensions.second / 699 });
	selec_canvas->setPosition(24.0, (float)dimensions.second * 6 / 7 + 17.0);
	selec_canvas->clear();
	selec_canvas->draw(selection);
	selec_canvas->display();
	gui.add(selec_canvas, "selecCanvas");

	sf::Sprite targetSpr(targetTex);
	targetSpr.setScale(1.07 * (float)dimensions.first / 600, 1.04 * (float)dimensions.second / 699);

	auto currentPlayerLabel = tgui::Label::create(currentPlayer + " turn");
	currentPlayerLabel->setPosition((float)dimensions.first * 0.495, (float)dimensions.second * 0.86);
	gui.add(currentPlayerLabel, "currentPlayer");

	auto target_canvas = tgui::Canvas::create({ 64 * 1.07 * (float)dimensions.first / 600, 65 * 1.04 * (float)dimensions.second / 699 });
	target_canvas->setPosition(687.0, (float)dimensions.second * 6 / 7 + 17.0);
	target_canvas->clear();
	target_canvas->draw(targetSpr);
	target_canvas->display();
	gui.add(target_canvas, "targetCanvas");
	/*
	auto button = tgui::Button::create();
	button->setPosition(dimensions.first/2.0 - 50.0, (dimensions.second * 6.0 / 7.0) + 0.5 * (dimensions.second / 7) - 15);
	button->setText("OK");
	button->setSize(100, 30);
	*/
}
