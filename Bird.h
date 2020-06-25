//Bird.h

#include "stdafx.h"
#include <vector>

#pragma once

class Bird
{
public:
	
	Bird(std::vector<Bird*> p_vFlock);
	~Bird();
	
	void update(sf::RenderWindow* p_rWindow);

private:
	
	sf::Vector2f calculate_Cohesion();
	sf::Vector2f calculate_Separation();
	sf::Vector2f calculate_Alignment();
	sf::Vector2f calculate_Route(sf::RenderWindow* p_rWindow);
	
	float calculate_distance(sf::Vector2f p_vBird);
	void normalize(sf::Vector2f &p_vNorm);

private:
	
	std::vector<Bird*> m_vFlock;
	sf::Vector2f m_rBird;
	sf::Vector2f m_vMovement;

public: 

	sf::Vector2f get_Movement();
	sf::Vector2f get_Position();

};

