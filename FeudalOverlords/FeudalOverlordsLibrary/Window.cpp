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
	
	/*
	sf::RectangleShape rectangle(sf::Vector2f(40, 20)); // Shape
	rectangle.setPosition(sf::Vector2f(10, 20)); // Position
	rectangle.setFillColor(sf::Color::Red);
	rectangle.setOutlineThickness(2); // Outline
	rectangle.setOutlineColor(sf::Color(0, 0, 0));
	draw(rectangle);
	//display();
	*/
}
