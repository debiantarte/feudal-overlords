#pragma once
#include <utility>
#include <SFML/Graphics.hpp>
#include <memory>

using namespace std;

class Window : public sf::RenderWindow
{
public:
	pair<int, int> dimensions;
	//unique_ptr<sf::RenderWindow> sfWindow;
	Window(int width, int height);
	~Window();
	void showUI();
};

