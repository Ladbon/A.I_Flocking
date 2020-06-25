//Bird.cpp

#include "Bird.h"


Bird::Bird(std::vector<Bird*> p_vFlock)
{
	m_rBird = sf::Vector2f(rand() % 500, rand() % 500);

	m_vFlock = p_vFlock;
	m_vMovement = sf::Vector2f((rand()%200)/100.0f -1, (rand()%200)/100.0f - 1);
}
Bird::~Bird()
{
}
void Bird::update(sf::RenderWindow* p_rWindow)
{
	m_vMovement.x += 
		calculate_Cohesion().x * 0.1f + 
		calculate_Separation().x * 0.2f + 
		calculate_Alignment().x * 0.1f + 
		calculate_Route(p_rWindow).x * 0.5f;

	m_vMovement.y +=
		calculate_Cohesion().y * 0.1f +
		calculate_Separation().y * 0.2f +
		calculate_Alignment().y * 0.1f +
		calculate_Route(p_rWindow).y * 0.5f;

	normalize(m_vMovement);
	
	m_rBird += m_vMovement*6.0f;

	if (m_rBird.x < 0.0f ||
		m_rBird.x > 1360.0f)
	{
		m_vMovement.x *= -1.0f;

	}

	if (m_rBird.y < 0.0f ||
		m_rBird.y > 760.0f)
	{
		m_vMovement.y *= -1.0f;

	}
}
void Bird::normalize(sf::Vector2f &p_vNorm)
{
	p_vNorm /= sqrt(pow(p_vNorm.x, 2) + pow(p_vNorm.y, 2));
}
float Bird::calculate_distance(sf::Vector2f p_vBird)
{
	return sqrt(pow(m_rBird.x - p_vBird.x, 2) + pow(m_rBird.y - p_vBird.y, 2));
}
sf::Vector2f Bird::calculate_Cohesion()
{
	sf::Vector2f v_Cohesion = sf::Vector2f(0.0f, 0.0f);
	float bird_count = 0;

	for (std::vector<Bird*>::iterator itr = m_vFlock.begin(); itr != m_vFlock.end(); itr++)
	{
		if ((*itr) != this)
		{
			if (calculate_distance((*itr)->get_Position()) < 50.0f)
			{
				v_Cohesion += (*itr)->get_Position();
				bird_count++;
			}
		}
	}
	
	if (bird_count == 0)
	{
		return v_Cohesion;
	}

	v_Cohesion /= bird_count;

	v_Cohesion -= m_rBird;

	normalize(v_Cohesion);

	return v_Cohesion;
}
sf::Vector2f Bird::calculate_Separation()
{
	sf::Vector2f v_Separation = sf::Vector2f(0.0f, 0.0f);
	float bird_count = 0;

	for (std::vector<Bird*>::iterator itr = m_vFlock.begin(); itr != m_vFlock.end(); itr++)
	{
		if ((*itr) != this)
		{
			if (calculate_distance((*itr)->get_Position()) < 20.0f)
			{
				v_Separation += (*itr)->get_Position() - m_rBird;
				bird_count++;
			}
		}
	}

	if (bird_count == 0)
	{
		return v_Separation;
	}

	v_Separation /= bird_count;

	v_Separation *= - 1.0f;

	normalize(v_Separation);

	return v_Separation;
}
sf::Vector2f Bird::calculate_Alignment()
{
	sf::Vector2f v_Alignment = sf::Vector2f(0.0f, 0.0f);
	float bird_count = 0;

	for (std::vector<Bird*>::iterator itr = m_vFlock.begin(); itr != m_vFlock.end(); itr++)
	{
		if ((*itr) != this)
		{
			if (calculate_distance((*itr)->get_Position()) < 50.0f)
			{
				v_Alignment += (*itr)->get_Movement();
				bird_count++;
			}
		}
	}

	if (bird_count == 0)
	{
		return v_Alignment;
	}

	v_Alignment /= bird_count;

	normalize(v_Alignment);

	return v_Alignment;
}
sf::Vector2f Bird::calculate_Route(sf::RenderWindow* p_rWindow)
{
	sf::Vector2f v_Route = sf::Vector2f(0.0f, 0.0f);
	if(calculate_distance(sf::Vector2f(sf::Mouse::getPosition(*p_rWindow))) <= 250)
	{
	v_Route = sf::Vector2f(sf::Mouse::getPosition(*p_rWindow)) - m_rBird;
	normalize(v_Route);
	}
	return v_Route;
}
sf::Vector2f Bird::get_Movement()
{
	return m_vMovement;
}
sf::Vector2f Bird::get_Position()
{
	return m_rBird;
}