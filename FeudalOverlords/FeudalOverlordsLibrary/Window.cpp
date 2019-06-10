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

void Window::buildGUI(tgui::Gui& gui, sf::Texture& selectTex, sf::Texture& targetTex/*, Territory* selected, Territory* target*//*, GameManager* gm*/)
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

	auto target_canvas = tgui::Canvas::create({ 64 * 1.07 * (float)dimensions.first / 600, 65 * 1.04 * (float)dimensions.second / 699 });
	target_canvas->setPosition(687.0, (float)dimensions.second * 6 / 7 + 17.0);
	target_canvas->clear();
	target_canvas->draw(targetSpr);
	target_canvas->display();
	gui.add(target_canvas, "targetCanvas");

	auto button = tgui::Button::create();
	button->setPosition(dimensions.first/2.0 - 50.0, (dimensions.second * 6.0 / 7.0) + 0.5 * (dimensions.second / 7) - 15);
	button->setText("OK");
	button->setSize(100, 30);
	//button->connect("pressed", [=]() { gm->moveTroops(selected, target); });
}
