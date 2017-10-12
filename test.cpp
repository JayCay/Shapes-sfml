#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

// DEFINES
#define RADIUS 30.0f
#define DIAMETER RADIUS * 2
#define WIDTH 800
#define HEIGHT 600
#define FPS 60
#define TIMESTEP 1.f/FPS
#define FORCE 160.0f * TIMESTEP
#define MASS 1.0f
#define FRICTION 0.2f * TIMESTEP
#define ELASTICITY 1.0f
#define ACCELERATION FORCE/MASS

// keybindings
#define keyUp sf::Keyboard::W
#define keyDown sf::Keyboard::S
#define keyLeft sf::Keyboard::A
#define keyRight sf::Keyboard::D
#define keyClose sf::Keyboard::Escape
#define keyFriction sf::Keyboard::F


void makeCircles(int x, sf::CircleShape circ[]) {
		int spacex = RADIUS; 
		int spacey = RADIUS;
		for ( int i = 0; i < x; i++ ) {
			circ[i].setRadius( RADIUS );
			circ[i].setFillColor( sf::Color::Green );
			if( i == 0 ){
				spacex =  spacex + DIAMETER + 15;
				circ[i].setPosition( spacex, spacey );
				spacex =  spacex + DIAMETER + 15;
			}
			else {
				if ( (spacex + DIAMETER) < ( WIDTH - DIAMETER ) ) {
					circ[i].setPosition( spacex, spacey );	
					spacex = spacex + DIAMETER + 15; 
				}	
				else if ( (spacex + DIAMETER) >= ( WIDTH - DIAMETER ) ) {
					circ[i].setPosition( spacex, spacey );	
					spacey = spacey + DIAMETER + 65;
					spacex = RADIUS;
				}
			}	
		}
	}

int main( int argc, char *argv[] ) {
	// init
	int x;
	sf::RenderWindow window( sf::VideoMode( WIDTH, HEIGHT ), "New" );
    window.setFramerateLimit( FPS );
    window.setActive( false );
    // input booleans
    bool keyUpPressed = false;
    bool keyDownPressed = false;
    bool keyLeftPressed = false;
    bool keyRightPressed = false;
    bool keyClosePressed = false;
    bool buttonLeftPressed = false;
    bool keyFrictionPressed = false;
    bool frictionMode = false;
    // definitions
    sf::Color color[2];
    color[0] = sf::Color::Red;
    color[1] = sf::Color::Green;
	// initialize player-circle 
	sf::CircleShape pcirc;
	pcirc.setRadius( 30.f );
    pcirc.setPosition( RADIUS, RADIUS );
    pcirc.setFillColor( sf::Color::Red );

	if ( argc != 2 ) {
		// if not enough or too many arguments
		cout << "USAGE: " << argv[0] << " <int>" << endl;
		cout << "The integer MUST be between 1 and 35, inclusive" << endl;
	}
	else {
		x = atoi( argv[1] ); // convert from chararray to int
		
		// cout << x << endl;
		if ( x >= 1 && x <= 35 ) {
			cout << "code for normal operation, perhaps call function" << endl;
		}
		else {
			// if argument out of range
			cout << "USAGE: " << argv[0] << " <int>" << endl;
			cout << "The integer MUST be between 1 and 35, inclusive" << endl;
		}
	}
	sf::CircleShape circ[x];
	
	makeCircles( x, circ );

	while ( window.isOpen() ) {
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
            }
            if ( event.type == sf::Event::KeyReleased ) {
                if ( event.key.code == keyUp ) keyUpPressed = false;
                if ( event.key.code == keyDown ) keyDownPressed = false;
                if ( event.key.code == keyLeft ) keyLeftPressed = false;
                if ( event.key.code == keyRight ) keyRightPressed = false;
                if ( event.key.code == keyClose ) keyClosePressed = false;
            }
        }

        if ( keyClosePressed ) {
            keyClosePressed = false;
            window.close();
        }

        window.clear( sf::Color::Black );
		window.draw( pcirc );
        for ( int n = 0; n < x; n++ ) window.draw( circ[n] );
        window.display();
    }
}