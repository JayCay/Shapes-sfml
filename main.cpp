#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>


using namespace std;

// DEFINES
#define FPS 60
#define numCircle 1
// keybindings
#define keyUp sf::Keyboard::W
#define keyDown sf::Keyboard::S
#define keyLeft sf::Keyboard::A
#define keyRight sf::Keyboard::D
#define keyClose sf::Keyboard::Escape
#define keyFriction sf::Keyboard::F

void move(){
    
}

int main() {
    srand( time( NULL ) );
    sf::Clock Clock;
    int width = 800; int height = 720;
    sf::RenderWindow window( sf::VideoMode( width, height ), "shape v0" );
    window.setFramerateLimit( FPS );
    window.setActive( false );
    sf::CircleShape circ;
    // input booleans
    bool keyUpPressed = false;
    bool keyDownPressed = false;
    bool keyLeftPressed = false;
    bool keyRightPressed = false;
    bool keyClosePressed = false;
    bool buttonLeftPressed = false;
	bool keyFrictionPressed = false;
	bool frictionMode = false;
    // movement constants
    float circleInput = 20.0/FPS;
    float autoMovement = 20.0/FPS;
    // vector constants
    float velocity = 0.0f;
    float force = 10.0f;
    float mass = 1.0f;
	float friction = 0.2f;

    sf::Vector2f cPos(0.0f,0.0f);
    sf::Vector2f cVel(0.0f,0.f);

    // initialise drawing the circle
    circ.setRadius( 30.f );
    circ.setOrigin(30.f,30.f);
    circ.setFillColor( sf::Color::Red );
    circ.setPosition(width/2.f, height/2.f);

    while ( window.isOpen() ) {
        
        sf::Time dt = Clock.restart();

        // handle input
        sf::Event event;
        while ( window.pollEvent(event) ) {
            if ( event.type == sf::Event::Closed )
                window.close();
            // keyboard
            if ( event.type == sf::Event::KeyPressed ) {
                if ( event.key.code == keyUp ) keyUpPressed = true;
                if ( event.key.code == keyDown ) keyDownPressed = true;
                if ( event.key.code == keyLeft ) keyLeftPressed = true;
                if ( event.key.code == keyRight ) keyRightPressed = true;
                if ( event.key.code == keyClose ) keyClosePressed = true;
				if ( event.key.code == keyFriction ) keyFrictionPressed = true;
            }
            if ( event.type == sf::Event::KeyReleased ) {
                if ( event.key.code == keyUp ) keyUpPressed = false;
                if ( event.key.code == keyDown ) keyDownPressed = false;
                if ( event.key.code == keyLeft ) keyLeftPressed = false;
                if ( event.key.code == keyRight ) keyRightPressed = false;
                if ( event.key.code == keyClose ) keyClosePressed = false;
				if ( event.key.code == keyFriction ) keyFrictionPressed = false;
            }
        }

        if ( keyClosePressed ) {
            keyClosePressed = false;
            window.close();
        }
		
		if ( keyFrictionPressed ) {
			keyFrictionPressed = false;
			frictionMode = !frictionMode;
		}

            

        //change ball's current velocity
		
		if ( frictionMode == false )
		{
			if ( keyUpPressed ) cVel.y -= (force/mass) * dt.asSeconds();
				 
			if ( keyDownPressed ) cVel.y += (force/mass) * dt.asSeconds();
						  
			if ( keyLeftPressed ) cVel.x -= (force/mass) * dt.asSeconds();
				   
			if ( keyRightPressed ) cVel.x += (force/mass) * dt.asSeconds();
			
			circ.setFillColor( sf::Color::Red );
		}
  
		else if ( frictionMode )
		{	
			cVel.x = cVel.x - ( (friction * cVel.x)/ mass );
			cVel.y = cVel.y - ( (friction * cVel.y)/ mass );
			circ.setFillColor( sf::Color::Blue );
		}
		
             
         cPos = circ.getPosition();


        //elasticity
        if (cPos.y - 30.f < 0.f || cPos.y == 0.f){
            cVel.y = -1.f * cVel.y; 
        }
        if (cPos.y + 30.f > height || cPos.x == height ){
            cVel.y = -1.f* cVel.y;
        }
        if (cPos.x - 30.f < 0.f || cPos.x == 0.f){
            cVel.x = -1.f * cVel.x;
        }
        if (cPos.x + 30.f > width  || cPos.x == width ){
            cVel.x = -1.f* cVel.x;
        }
        
        //show ball's current velocity (will remove soon)
        cout << cVel.x << " " << cVel.y << endl;

        //ball movement
        circ.move(cVel.x, cVel.y);

        // draw game to screen
        window.clear( sf::Color::Black );
        window.draw( circ );
        window.display();
    }

    return 0;
}