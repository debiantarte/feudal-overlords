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

void Window::buildGUI(tgui::Gui& gui)
{
	
}
