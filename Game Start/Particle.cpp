#include "Particle.h"

////////////////CONSTRUCTORS///////////////////
Particle::Particle()
{
	location = sf::Vector2f(0, 0);
	velocity = sf::Vector2f(0, 0);
	acceleration = sf::Vector2f(0, 0);
	boundary = sf::FloatRect();

	this->circle = sf::CircleShape(2);
	this->life = 255;
}

Particle::Particle(const sf::FloatRect &boundary)
{
	location = sf::Vector2f(0, 0);
	velocity = sf::Vector2f(1, 1);
	acceleration = sf::Vector2f(1, 1);

	this->boundary = boundary;
	this->circle = sf::CircleShape(2);
	this->life = 255;
}

Particle::Particle(const sf::FloatRect &boundary, const  sf::Vector2f &location, const  float &mass)
{
	this->location = location;
	this->velocity = sf::Vector2f();
	this->acceleration = sf::Vector2f();
	this->boundary = boundary;
	this->mass = mass;
	this->circle = sf::CircleShape(2);
	this->life = 255;
}

////////////////DESTRUCTOR///////////////////
Particle::~Particle()
{
}


///////////////////GET//////////////////////
sf::CircleShape& Particle::getCircleShape()
{
	return circle;
}

sf::Vector2f Particle::getVelocity()
{
	return velocity;
}

sf::Vector2f Particle::getAcceleration()
{
	return acceleration;
}

sf::Vector2f Particle::getLocation()
{
	return location;
}

float Particle::getLife()
{
	return life;
}

///////////////////SET//////////////////////
void Particle::setCircleShape(sf::CircleShape& circle)
{
	this->circle = circle;
}

void Particle::setVelocity(const sf::Vector2f &velocity)
{
	this->velocity = velocity;
}

void Particle::setAcceleration(const sf::Vector2f &acceleration)
{
	this->acceleration = acceleration;
}

void Particle::setLife(float &life)
{
	this->life = life;
}

///////////////////MISC/////////////////////
void Particle::applyForce(const sf::Vector2f &force)
{
	acceleration = acceleration + (force / mass);
}

void Particle::resetAcceleration()
{
	acceleration.x = 0.0f;
	acceleration.y = 0.0f;
}

// euler integration
void Particle::update(const sf::Time &deltaTime)
{
	velocity = velocity + (acceleration * deltaTime.asSeconds());
	location = location + (velocity * deltaTime.asSeconds());

	if (life > 0)
	{
		life-=15;
	}

	circle.setPosition(location);
}

// reverse the velocity vector when location outside of boundary
void Particle::checkEdges()
{
	if ((location.x > boundary.width) || (location.x < 0)) 
	{
		velocity.x = velocity.x * -1;
	}
	if ((location.y > boundary.height) || (location.y < 0)) 
	{
		velocity.y = velocity.y * -1;
	}
}
