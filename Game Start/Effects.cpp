/*
*	Effects.cpp
*	Rumble
*
*	Created by: Reuben Dales, Lance Donnell, Lance Harris, Josh Prow.
*	Dated: 11 November 2015
*
*/

#include "Effects.h"

//Constructor
Effects::Effects(sf::View &view, sf::RenderWindow &window, Map &map, Hud & HUD, Player & player, std::vector<Projectile> &projectiles)
{
	_window = &window; 
	_player = &player;
	_view = &view;
	_map = &map;
	_hud = &HUD;
	_projectile = &projectiles;

	if(!dungeonMap.loadFromFile("dungeonMap.jpg"))
	{
		//error
	}
	dungeonStage.setTexture(dungeonMap);

	if(!shopMap.loadFromFile("shopMap.jpg"))
	{
		//error
	}
	shopStage.setTexture(shopMap);

	if(!lighting.loadFromFile("lightingTest.png"))
	{
		//failed
	}
	lightingSprite.setTexture(lighting);
	lightingSprite.setOrigin(lighting.getSize().x/2,lighting.getSize().y/2);
	lightingSprite.scale(2,2);

	//AMBIENCE
	this->rect = sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(_window->getSize())); //The size of the window, acts as a boundary

	for(int i = 0; i<25; i++)
	{
		float alpha = (rand() % 128) + 50;	

		sf::Color random = sf::Color(252,255,168,alpha);
		
		int x = rand() % _window->getSize().x;	
		int y = rand() % _window->getSize().y;

		sf::Vector2f location = sf::Vector2f(x,y);

		Particle particle = Particle(rect, location, 10);
		particle.setLife(alpha);

		sf::CircleShape circle = particle.getCircleShape();
		circle.setRadius(2);
		circle.setFillColor(random);
		circle.setPosition(location);

		particle.setCircleShape(circle);
		lightParticles.push_front(particle);
	}
}

//Destructor
Effects::~Effects(void)
{
}

//Draws the screen
void Effects::draw()
{
	_window->clear();
	lightingSprite.setPosition(_player->getSprite().getPosition().x, _player->getSprite().getPosition().y);
	_window->draw(_map->getSprite());
	//_map->drawMap(*_window,dungeonStage,shopStage);
	_window->draw(lightingSprite);
	_window->draw(_player->getSprite());

	/*
	for(std::vector<Projectile>::iterator it = _projectile.begin(); it != _projectile.end(); ++it)
	{
		int i = 0;
		it->updateProjectileLocation(_window);

		if(_map->isCollision(it->getRow(), it->getColumn() ))
		{
			_projectile.erase(_projectile.begin()+i);
		}
		/*
		else if(it->attackHit(enemies) != 1000){ //1000 = No hit
			it.erase(it.begin()+i);
			enemies[i].takeDamage(player.getAttack());
		}
		else if(it->getPosX() > 1080 || it->getPosX() < 0)
		{
			_projectile.erase(_projectile.begin()+i); //Since Projectile objects weren't allocated with new, erase should free the memory as well as removing the object from the array
		}
		else if(it->getPosY() > 840 || it->getPosY() < 0)
		{
			_projectile.erase(_projectile.begin()+i);
		}
		i++;
	}*/
	//_hud->drawHUD();						//Creates an odd effect
	_window->display();
}

//Pauses everything on screen for a given length of time (in seconds). Could be used for 'cutscene' sequence timing? Needs more work to be honest
void Effects::wait(int seconds)
{
	sf::Clock clock;
	int num = 0;
	while(clock.getElapsedTime().asSeconds() < seconds)
	{
		draw();
		num++;
		//Could add a bool here, and check for it in other methods like walking.
	}
}

//Zooms in or out depending on your input when calling the method - freezes the player while doing so
//interval is by default set to 0.05 (see header file), but can be altered to anything when calling the method (though anything over 0.05 becomes jumpy)
void Effects::zoomFreeze(float maxZoomPercent, float seconds, float interval)
{
	sf::Clock clock;
	sf::Time time = sf::Time::Zero;

	sf::Clock clock2;					//To keep track of how long the zoom actually took for debugging
	sf::Time time2 = sf::Time::Zero;

	float windowXPercent = (_window->getSize().x / 100) * maxZoomPercent;
	float windowYPercent = (_window->getSize().y / 100) * maxZoomPercent; //Gives you the current percentage of the window

	float step;
	if(maxZoomPercent > 100)
	{
		step = 1.01;
	}
	else if (maxZoomPercent < 100)
	{
		step = 0.99;
	}
	else //zoom is 100
	{
		if(((_view->getSize().x / _window->getSize().x) * 100) < 100) //Find out the current percent the view is zoomed in
		{
			std::cout<<_view->getSize().x / _window->getSize().x * 100<<std::endl;
			step = 1.01; // because it's less than 100%
		}
		else
		{
			step = 0.99;
		}
	}

	float stepPercent; 
	int wSCopy = windowXPercent;		//The lower percent
	int wSMax = _window->getSize().x;
	int iterations = 0;					//This is not the same iterations as used in the main.cpp
	
	//An attempt to find the factor that should be used to take the given seconds (ie zoom in by 1% to get to 50% in 5 seconds)
	//If you are zooming out
	if(step > 1)
	{
		while(iterations*interval <= seconds)
		{
			stepPercent = (step * 100) - 100;			//eg 1.01 * 100 = 101, then 101 - 100 gives 1 so 1%

			while(wSCopy >= wSMax && iterations*interval <= seconds)
			{
				float subAmount = (wSMax/100)*stepPercent; 
				wSMax += subAmount;
				iterations++;						   //the amount of times it had to add 1%
			}
			if(iterations*interval <= seconds)
			{
				step -= 0.001;
				wSCopy = windowXPercent;
				wSMax = _window->getSize().x;
				iterations = 0;
			}
			else
			{
				continue;
			}
		}
	}
	//If you are zooming in
	else if (step < 1)
	{
		while(iterations*interval <= seconds)
		{
			stepPercent = abs(step * 100) - 100;		//eg 0.99 * 100 = 99 then 99 - 100 gives -1 so the value has to be absolute. 1%
		
			while(wSCopy <= wSMax && iterations*interval <= seconds)
			{
				float subAmount = (wSMax/100)*stepPercent; 
				wSMax -= subAmount;
				iterations++;			 //the amount of times it had to subtract by 1%
			}
			if(iterations*interval <= seconds)
			{
				step += 0.001;
				wSCopy = windowXPercent;
				wSMax = _window->getSize().x;
				iterations = 0;
			}
			else
			{
				continue;
			}
		}
	}
	else
	{
		std::cout<<"You can't have 1.0! If you want to increase or decrease back to 100% you have to use 0.99 (to decrease) or 1.01 (to increase).";
	}

	//Zooming in
	if(windowXPercent <= _view->getSize().x && windowYPercent <= _view->getSize().y)
	{
		while(windowXPercent <= _view->getSize().x && windowYPercent <= _view->getSize().y)
		{
			time = clock.getElapsedTime();
			if(time.asSeconds() >= interval)
			{
				_view->zoom(step);
				_window->setView(*_view);

				_view->setCenter(_player->getSprite().getPosition().x+12, _player->getSprite().getPosition().y+12);

				draw();

				clock.restart();
			}
		}
	}
	//Zooming out
	else if(windowXPercent >= _view->getSize().x && windowYPercent >= _view->getSize().y)
	{
		while(windowXPercent >= _view->getSize().x && windowYPercent >= _view->getSize().y)
		{
			time = clock.getElapsedTime();
			if(time.asSeconds() >= interval)
			{
				_view->zoom(step);
				_window->setView(*_view);

				_view->setCenter(_player->getSprite().getPosition().x+12, _player->getSprite().getPosition().y+12);

				draw();

				clock.restart();
			}
		}
	}
	//Helpful to know how long it took to zoom!
	//std::cout << clock2.getElapsedTime().asSeconds() << std::endl;
}

//Initialises the screen shaking data ready for the update to run
void Effects::screenShake(int power, float shakeFrames)
{
	this->power = power;
	this->shakeFrames = shakeFrames;
	this->shakeTimer = 0;
	this->shakeScreen = true;
}

//To be placed in the main game loop and continue shaking the screen
void Effects::screenShakeUpdate()
{
	if (shakeScreen)
    {
		int xShake = rand() % 10; //gives a random number between 0 and 10 for the X axis
		int yShake = rand() % 5;
		_view->move(sf::Vector2f((float)xShake * power, (float)yShake * power));

        // Increase the shake timer by one frame and check if we have been shaking long enough
        shakeTimer++;
        if (shakeTimer >= shakeFrames)
        {
            shakeScreen = false;
            shakeTimer = 0;
            shakeFrames = 0;
        }
    }
}

//Quick method to fade the screen out any colour you like - 0,0,0 is black, 255,255,255 white - 0 alpha is transparent, 255 opaque
void Effects::fade(int red, int green, int blue, float alpha, float frames, int finalAlpha)
{
	this->fadeIncrement = 255/frames;
	this->alpha = alpha;
	this->fadeFrames = frames;			//60 frames = 1 second
	this->fadeTimer = 0;
	this->fadeScreen = true;
	this->red = red;
	this->green = green;
	this->blue = blue;
	this->finalAlpha = finalAlpha;

	transition.setFillColor(sf::Color(red,green,blue,alpha));
	transition.setSize(sf::Vector2f(_window->getSize().x, _window->getSize().y));
	transition.setPosition(0,0);
}

//Allows the player to move around while the screen fades, must be drawn last
void Effects::fadeUpdate()
{
	if(fadeScreen)
	{
		if(finalAlpha == 255)
		{
			alpha += fadeIncrement;
		}
		else
		{
			alpha -= fadeIncrement;
		}

		transition.setFillColor(sf::Color(red,green,blue,alpha));
		_window->draw(transition);

		fadeTimer++;
		if(fadeTimer >= fadeFrames)
		{
			fadeScreen = false;
            fadeTimer = 0;
            fadeFrames = 0;
		}
	}
}

//Spray blood out of a character! (player or enemy) to be used on death animation and when hit with axes
void Effects::blood(Character &target)
{
	_target = &target;
	
	for(int i = 0; i<BLOOD_SIZE; i++)
	{
		sf::Color random = sf::Color(217,24,24,255);
		sf::Vector2f location;
		int x = rand() % 250;      //gives a random number between 0 and 250 for the X axis	
		int y = (rand() % 150)-50; //generates a number between 0 and 150 minus 50 so, -50 and 100

		if(target.getFacing() == 0)//UP
		{
			location = sf::Vector2f(target.getSprite().getPosition().x, target.getSprite().getPosition().y);
			x = (rand() % 150)-50; 	
			y = (rand() % 200)-250; 
		}
		else if(target.getFacing() == 1)//RIGHT
		{
			location = sf::Vector2f(target.getSprite().getPosition().x+5, target.getSprite().getPosition().y+2);
			x = rand() % 250;      	
			y = (rand() % 150)-50; 
		}
		else if (target.getFacing() == 2)//DOWN
		{
			location = sf::Vector2f(target.getSprite().getPosition().x, target.getSprite().getPosition().y+5);
			x = (rand() % 150)-50; 	
			y = rand() % 250; 
		}
		else if (target.getFacing() == 3)//LEFT
		{
			location = sf::Vector2f(target.getSprite().getPosition().x-2, target.getSprite().getPosition().y-2);
			x = (rand() % 200)-250; 	
			y = (rand() % 150)-50; 
		}

		Particle particle = Particle(rect, location, 10);
		particle.setVelocity(sf::Vector2f(x, y));

		sf::CircleShape circle = particle.getCircleShape();
		circle.setRadius(PARTICLE_RADIUS);
		circle.setFillColor(random);

		particle.setCircleShape(circle);
		bloodParticles.push_front(particle);
	}

	this->bloodEffect = true;
}

//Update the blood spray!
void Effects::bloodUpdate(sf::Time TimePerFrame)
{
	int emptyBlood = 0;
	if(bloodEffect)
	{
		for (std::list<Particle>::iterator it = bloodParticles.begin(); it != bloodParticles.end(); ++it)
		{
			it->update(TimePerFrame);
			sf::CircleShape circle = it->getCircleShape();

			sf::Color random = circle.getFillColor();
			random.a = it->getLife();
			circle.setFillColor(random);

			_window->draw(circle);
		}

		for (std::list<Particle>::iterator it = bloodParticles.begin(); it != bloodParticles.end();)
		{
			if (it->getLife() < 1)
			{
				it = bloodParticles.erase(it);
			}
			else
			{
				++it;
			}
		}

		//Reset bool if all the elements have been erased
		if(bloodParticles.size() == 0)
		{
			this->bloodEffect = false;	
		}
	}
}

//Particle effect, floating orbs of light
void Effects::ambience()
{
	for (std::list<Particle>::iterator it = lightParticles.begin(); it != lightParticles.end(); ++it)
	{
		sf::Color colourAlpha = it->getCircleShape().getFillColor();

		//If the alpha (life) is greater than 0 decrease it's alpha by 0.1
		if (it->getLife() > 0)
		{
			float currentLife = it->getLife();
			currentLife-=0.1;
			it->setLife(currentLife);
			colourAlpha.a = it->getLife();
			it->getCircleShape().setFillColor(colourAlpha);
		}

		//If the alpha (life) is less than one, change the location and give it a new random alpha level
		if (it->getLife() < 1)
		{
			float alpha = (rand() % 128) + 50;	//Between 50 and 178	
			int x = rand() % _window->getSize().x;	
			int y = rand() % _window->getSize().y;

			sf::Vector2f location = sf::Vector2f(x,y);
			sf::Color colour = sf::Color(252,255,168,alpha);
			it->getCircleShape().setPosition(location);
			it->getCircleShape().setFillColor(colour);
			it->setLife(alpha);
		}
		_window->draw(it->getCircleShape());
	}
}

//Particle effect that follows the player's weapon (fireball or axe)
//particle list, add particles, a lot at first then less as the distance travelled increases
//could create a variable that measures the distance from the thrown position
void Effects::weaponTrail()
{
	attacked = true; //This method feels a little redundant...
}

//Creates 4 particles at the position of the projectile every frame 
//(ie every 9 pixel the projectile travels) + random number + offset (based on width and/or height of projectile)
void Effects::weaponTrailUpdate(std::vector<Projectile> &weapon, Player &player)
{
	float currentLife; //of the particle

	//If you chose the wizard
	//if(player.getChoice() == 1)
	//{
		//If you have attacked
		if(attacked)
		{
			//For each projectile in existence
			for (std::vector<Projectile>::iterator it = weapon.begin(); it != weapon.end(); ++it)
			{
				int trail = (rand() % 6)+1; //between 1 and 7

				//create 4 new particles
				for(int i = 0; i<trail; i++)
				{
					sf::Color colour = sf::Color(255,255,255,100);
					Particle particle = Particle();
					int x = rand() % 15;	
					int y = rand() % 10;

					sf::CircleShape circle = particle.getCircleShape();
					circle.setRadius(2.5);
					circle.setFillColor(colour);

					//Check which direction they are going before you position them - sorry about all the literals, this needed a bunch of fine tuning. But I will try figure out an equation!
					if(it->getDirection() == 0) //UP
					{
						circle.setPosition((it->getPosX()+x+5), (it->getPosY()+y+15));
					}
					else if(it->getDirection() == 1) //RIGHT
					{
						circle.setPosition((it->getPosX()-x+10), (it->getPosY()+y+10));
					}
					else if(it->getDirection() == 2) //DOWN
					{
						circle.setPosition((it->getPosX()+x+5), (it->getPosY()-y+10));
					}
					else if(it->getDirection() == 3) //LEFT
					{
						circle.setPosition((it->getPosX()+x+10), (it->getPosY()+y+10));
					}

					float alpha = 255;
					particle.setLife(alpha);

					particle.setCircleShape(circle);
					weaponParticles.push_front(particle);
				}
			}

			for (std::list<Particle>::iterator it = weaponParticles.begin(); it != weaponParticles.end(); ++it)
			{
			
				currentLife = it->getLife();
				currentLife-=15; //decides how quickly the effect fades, ie how long the trail is
				it->setLife(currentLife);
				sf::CircleShape circle = it->getCircleShape();
				sf::Color random = circle.getFillColor();
				random.a = it->getLife();
				circle.setFillColor(random);

				_window->draw(it->getCircleShape());
			}

			//Check if any of the particles have 0 alpha
			for (std::list<Particle>::iterator it = weaponParticles.begin(); it != weaponParticles.end();)
			{
				if (it->getLife() < 1)
				{
					it = weaponParticles.erase(it);
				}
				else
				{
					++it;
				}
			}

			if(weaponParticles.size() == 0)
			{
				attacked = false;	
			}
		}
	//}
}