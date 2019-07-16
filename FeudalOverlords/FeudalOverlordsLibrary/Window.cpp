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

void Window::buildGUI(tgui::Gui& gui, sf::Texture& selectTex, sf::Texture& targetTex,
	string selTrp, string tgtTrp, string selOwner, string tgtOwner, string currentPlayer)
{
	// create UI background sprite
	sf::Texture uitex;
	bool texLoaded = uitex.loadFromFile("../../Assets/Textures/UItex.png");
	assert(texLoaded);
	sf::Sprite uiBackground(uitex);
	uiBackground.setScale((float)dimensions.first / uitex.getSize().x, ((float)dimensions.second / 7) / uitex.getSize().y);
	// apply it to a canvas and draw the canvas
	auto back_canvas = tgui::Canvas::create({ (float)dimensions.first, (float)dimensions.second / 7 });
	back_canvas->setPosition(0.0, (float)dimensions.second * 6 / 7);
	back_canvas->clear();
	back_canvas->draw(uiBackground);
	back_canvas->display();
	gui.add(back_canvas);

	// add a label displaying the name of the selected territory's owner
	auto selOwnerLabel = tgui::Label::create(selOwner);
	selOwnerLabel->setPosition((float)dimensions.first * 0.177, (float)dimensions.second * 0.9);
	gui.add(selOwnerLabel, "selectOwner");

	// add a picture reprensenting the selected territory's type
	auto selectSpr = tgui::Picture::create(selectTex);
	selectSpr->setSize(67 * (float)dimensions.first / 600, 65 * (float)dimensions.second / 700);
	selectSpr->setPosition(24.0, (float)dimensions.second * 6 / 7 + 17.0);
	gui.add(selectSpr, "selectPic");

	// add a label for the amount of troops in selected territory
	auto selLabel = tgui::Label::create(selTrp);
	selLabel->setPosition((float)dimensions.first * 0.177, (float)dimensions.second * 0.88);
	gui.add(selLabel, "selectTroops");

	// add a label displaying the name of the targeted territory's owner
	auto tgtOwnerLabel = tgui::Label::create(tgtOwner);
	tgtOwnerLabel->setPosition((float)dimensions.first * 0.530, (float)dimensions.second * 0.9);
	gui.add(tgtOwnerLabel, "targetOwner");

	// add a picture reprensenting the targeted territory's type
	auto targetSpr = tgui::Picture::create(targetTex);
	targetSpr->setSize(67 * (float)dimensions.first / 600, 65 * (float)dimensions.second / 700);
	targetSpr->setPosition(687.0, (float)dimensions.second * 6 / 7 + 17.0);
	gui.add(targetSpr, "targetPic");

	// add a label for the amount of troops in targeted territory
	auto tgtLabel = tgui::Label::create(tgtTrp);
	tgtLabel->setPosition((float)dimensions.first * 0.530, (float)dimensions.second * 0.88);
	gui.add(tgtLabel, "targetTroops");

	// add a label displaying which player should be playing now
	auto currentPlayerLabel = tgui::Label::create();
	currentPlayerLabel->setText(currentPlayer + " turn");
	currentPlayerLabel->setPosition(600.0, 598.0);
	gui.add(currentPlayerLabel, "currentPlayer");

	// add a list box to display notifications
	auto notifBox = tgui::ListBox::create();
	notifBox->setAutoScroll(true);
	notifBox->setSize(300.0, 75.0);
	notifBox->setPosition(5.0, 5.0);
	
	// change every possible property ever about anything that's about items' colors to make the list box look like it can't be clicked on
	notifBox->getRenderer()->setBackgroundColor(tgui::Color(uint8_t(0.0), uint8_t(0.0), uint8_t(0.0), uint8_t(125.0)));
	notifBox->getRenderer()->setTextColor(tgui::Color(uint8_t(250.0), uint8_t(250.0), uint8_t(250.0), uint8_t(100.0)));
	notifBox->getRenderer()->setSelectedBackgroundColorHover(tgui::Color(uint8_t(0.0), uint8_t(0.0), uint8_t(0.0), uint8_t(0.0)));
	notifBox->getRenderer()->setBackgroundColorHover(tgui::Color(uint8_t(0.0), uint8_t(0.0), uint8_t(0.0), uint8_t(0.0)));
	notifBox->getRenderer()->setTextColorHover(tgui::Color(uint8_t(250.0), uint8_t(250.0), uint8_t(250.0), uint8_t(100.0)));

	notifBox->getRenderer()->setSelectedBackgroundColor(tgui::Color(uint8_t(0.0), uint8_t(0.0), uint8_t(0.0), uint8_t(0.0)));
	notifBox->getRenderer()->setSelectedTextColor(tgui::Color(uint8_t(250.0), uint8_t(250.0), uint8_t(250.0), uint8_t(100.0)));
	notifBox->getRenderer()->setSelectedTextColorHover(tgui::Color(uint8_t(250.0), uint8_t(250.0), uint8_t(250.0), uint8_t(100.0)));

	// render the scrollbar mostly invisible
	notifBox->getRenderer()->setScrollbarWidth(0.001);
	gui.add(notifBox, "notifBox");

	auto winBox = tgui::MessageBox::create();
	winBox->addButton("Glory !");
	//winBox->addButton("Let's go again !");
	winBox->setTitle("The War Is Ended ! All Hail The Winner !");
	winBox->setPosition(400.0, 300.0);
	winBox->setVisible(false);
	gui.add(winBox, "winBox");
}

void Window::updateGUI(tgui::Gui& gui, sf::Texture& selectTex, sf::Texture& targetTex,
	string selTrp, string tgtTrp, string selOwner, string tgtOwner, string currentPlayer)
{
	gui.get("selectOwner")->cast<tgui::Label>()->setText(selOwner);
	gui.get("selectPic")->cast<tgui::Picture>()->getRenderer()->setTexture(selectTex);
	gui.get("selectTroops")->cast<tgui::Label>()->setText(selTrp);
	gui.get("targetOwner")->cast<tgui::Label>()->setText(tgtOwner);
	gui.get("targetPic")->cast<tgui::Picture>()->getRenderer()->setTexture(targetTex);
	gui.get("targetTroops")->cast<tgui::Label>()->setText(tgtTrp);
	gui.get("currentPlayer")->cast<tgui::Label>()->setText(currentPlayer);
}