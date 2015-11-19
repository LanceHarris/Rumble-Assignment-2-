#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

#pragma once
class Particle
{
	private:
		sf::CircleShape circle;
		sf::Vector2f location;     // difference between location and the origin
		sf::Vector2f velocity;     // the rate of change in location
		sf::Vector2f acceleration; // the rate of change in velocity
		float mass;
		sf::FloatRect boundary;
		float life;

	public:
		//Constructors
		Particle(const sf::FloatRect &boundary);
		Particle(const sf::FloatRect &boundary, const  sf::Vector2f &location, const float &mass);
		Particle();

		//Destructor
		~Particle();

		//Get
		sf::CircleShape& getCircleShape();
		sf::Vector2f getVelocity();
		sf::Vector2f getAcceleration();			
		sf::Vector2f getLocation();
		float getLife();

		//Set
		void setCircleShape(sf::CircleShape& circle);
		void setVelocity(const sf::Vector2f &velocity);
		void setAcceleration(const sf::Vector2f &acceleration);
		void setLife(float &life);
		
		//Misc
		void applyForce(const sf::Vector2f &force);
		void resetAcceleration();
		// euler integration
		void update(const sf::Time &deltaTime);
		// boundary check
		void checkEdges(); //not used for blood
};

