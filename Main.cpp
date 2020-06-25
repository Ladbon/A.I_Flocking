// Main.cpp


#include "stdafx.h"
#include "Bird.h"
#include <vector>

int main(int argc, char* argv[])
{
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1360, 768), "Hitchcock");
	window->setFramerateLimit(60);

	std::vector<Bird*> flock;

	sf::RectangleShape birdmodel;
	birdmodel.setSize(sf::Vector2f(3.0f, 10.0f));
	birdmodel.setFillColor(sf::Color::Red);

	for (int i = 0; i < 700; i++)
	{
		Bird* bird = new Bird(flock);
		flock.push_back(bird);
	}


	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window->close();
				break;
			case sf::Event::MouseButtonPressed:
				if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
				{
					window->close();
				}
				break;

			}

		}

		for (std::vector<Bird*>::iterator itr = flock.begin(); itr != flock.end(); itr++)
		{
			(*itr)->update(window);
			birdmodel.setPosition((*itr)->get_Position());
			birdmodel.setRotation(atan2((*itr)->get_Movement().y, (*itr)->get_Movement().x) * 180.0f / (atan(1) * 4) + 90);
			window->draw(birdmodel);
		}
		window->display();
		window->clear(sf::Color::Black);
	}

	delete window;
	window = nullptr;

	for (std::vector<Bird*>::iterator itr = flock.begin(); itr != flock.end(); itr++)
	{
		delete (*itr);
		(*itr) = nullptr;
	}
	flock.clear();

	return 0;
}

