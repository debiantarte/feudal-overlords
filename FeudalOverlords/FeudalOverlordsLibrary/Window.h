#pragma once
#include <utility>
#include <SFML/Graphics.hpp>
#include <memory>
#include <TGUI/TGUI.hpp>
#include <string>
//#include "Territory.h"
//#include "GameManager.h"

using namespace std;

class Window : public sf::RenderWindow
{
public:
	pair<int, int> dimensions;
	//unique_ptr<sf::RenderWindow> sfWindow;
	Window(int width, int height);
	~Window();
	void buildGUI(tgui::Gui&, sf::Texture&, sf::Texture&, string, string, string, string, string);
	void updateGUI(tgui::Gui&, sf::Texture&, sf::Texture&, string, string, string, string, string);
};

