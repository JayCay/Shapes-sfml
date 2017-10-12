#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace std;

// DEFINES
#define RADIUS 30.0f
#define ORADIUS 25.f
#define WIDTH 800
#define HEIGHT 600
#define FPS 60.f
#define TIMESTEP 1.f/FPS
#define FORCE 160.0f 
#define MASS 1.0f
#define FRICTION 0.2f * TIMESTEP
#define ELASTICITY 1.0f

// keybindings
#define keyUp sf::Keyboard::W
#define keyDown sf::Keyboard::S
#define keyLeft sf::Keyboard::A
#define keyRight sf::Keyboard::D
#define keyClose sf::Keyboard::Escape
#define keyFriction sf::Keyboard::F

// input booleans
bool keyClosePressed = false;
bool keyFrictionPressed = false;
bool frictionMode = false;
// movement constants
float circleInput = 20.0 / FPS;
float autoMovement = 20.0 / FPS;
// vector math
//float getTime = TIMESTEP;
float force = FORCE;
float mass = 1.f/MASS;
float friction = FRICTION;

sf::Vector2f cPos( 0.0f, 0.0f );
sf::Vector2f cVel( 0.0f, 0.f );
sf::Vector2f cAcel( 0.0f, 0.0f );
sf::CircleShape circ;
sf::RenderWindow window( sf::VideoMode( WIDTH, HEIGHT ), "shape me" );

void makeCircles(int x, sf::CircleShape circ[]) {
        int spacex = ORADIUS; 
        int spacey = ORADIUS;
        for ( int i = 0; i < x; i++ ) {
            circ[i].setRadius( ORADIUS );
            circ[i].setFillColor( sf::Color::Green );
            if( i == 0 ){
                spacex =  spacex + (ORADIUS * 2) + 35;
                circ[i].setPosition( spacex, spacey );
                spacex =  spacex + (ORADIUS * 2) + 35;
            }
            else {
                if ( (spacex + (ORADIUS * 2)) < ( WIDTH - (ORADIUS * 2) ) ) {
                    circ[i].setPosition( spacex, spacey );  
                    spacex = spacex + (ORADIUS * 2) + 35; 
                }   
                else if ( (spacex + (ORADIUS * 2)) >= ( WIDTH - (ORADIUS * 2) ) ) {
                    circ[i].setPosition( spacex, spacey );  
                    spacey = spacey + (ORADIUS * 2) + 75;
                    spacex = ORADIUS;
                }
            }   
        }
    }

void moveball(){
    cPos = circ.getPosition();
    cVel += ( cAcel * TIMESTEP );
    cPos += ( 0.5f * cAcel * TIMESTEP * TIMESTEP ) + ( cVel * TIMESTEP );
    if ( frictionMode )cVel -= ( ( friction *cVel ) / mass );
    circ.setPosition( cPos );
}

void boing(){
    cPos = circ.getPosition();
        //elasticity
        if ( cPos.y  < 0.f + RADIUS ){   
            cPos.y = 0 + RADIUS;
            cVel.y = -ELASTICITY * cVel.y;
            circ.setPosition( cPos );
            }
        if (cPos.y > HEIGHT - 1.f - RADIUS){
            cPos.y = HEIGHT - RADIUS -1.f;
            cVel.y = -ELASTICITY * cVel.y;
            circ.setPosition( cPos );
        }
        if ( cPos.x < 0.f + RADIUS ){
            cPos.x = 0 + RADIUS;
            cVel.x = -ELASTICITY * cVel.x;
            circ.setPosition( cPos );
        }

        if(cPos.x  > WIDTH -1.f - RADIUS ){
            cPos.x = WIDTH - RADIUS -1.f;
            cVel.x = -ELASTICITY * cVel.x;
            circ.setPosition( cPos );
        }
}

int main( int argc, char *argv[] ) {
    // get number of other circles through cmd args
    int size = 0;
    if ( argc != 2 ) {
        // if not enough or too many arguments
        cout << "USAGE: " << argv[0] << " <int>" << endl;
        cout << "The integer MUST be between 1 and 35, inclusive" << endl;
        return 1; // terminate with errorlevel 1
    }
    else {
        int x = atoi( argv[1] ); // convert from chararray to int
        // cout << x << endl;
        if ( x >= 1 && x <= 35 ) size = x;
        else {
            // if argument out of range
            cout << "USAGE: " << argv[0] << " <int>" << endl;
            cout << "The integer MUST be between 1 and 35, inclusive" << endl;
            return 1; // terminate with errorlevel 1
        }
    }

    window.setFramerateLimit( FPS );
    window.setActive( false );
    window.setKeyRepeatEnabled(false);

    // initialise drawing the circle
    circ.setRadius( RADIUS );
    circ.setOrigin( RADIUS, RADIUS );
    circ.setFillColor( sf::Color::Red );
    circ.setPosition( 50, 50 );
    
     sf::CircleShape ocirc[size];
    
    makeCircles( size, ocirc );

    while ( window.isOpen() ) {
        // handle input
        sf::Event event;
        while ( window.pollEvent(event) ) {
            if ( event.type == sf::Event::Closed ) window.close();
            if ( event.type == sf::Event::KeyPressed ) {
                if ( event.key.code == keyUp ) cAcel.y -= (force * mass);
                if ( event.key.code == keyDown ) cAcel.y +=  force * mass;
                if ( event.key.code == keyLeft) cAcel.x -= (force * mass);
                if ( event.key.code == keyRight) cAcel.x += force * mass;
                if ( event.key.code == keyClose ) keyClosePressed = true;
                if ( event.key.code == keyFriction ) keyFrictionPressed = true;
            }
            if ( event.type == sf::Event::KeyReleased ) {
                if ( event.key.code == keyUp ) cAcel.y = 0;
                if ( event.key.code == keyDown ) cAcel.y = 0;
                if ( event.key.code == keyLeft ) cAcel.x = 0;
                if ( event.key.code == keyRight ) cAcel.x = 0;
                if ( event.key.code == keyClose ) keyClosePressed = false;
                if ( event.key.code == keyFriction ) keyFrictionPressed = false;
            } 

        }
        // close window
        if ( keyClosePressed ) {
            keyClosePressed = false;
            window.close();
        }

        // friction mode toggle
        if ( keyFrictionPressed ) {
            keyFrictionPressed = false;
            frictionMode = !frictionMode;
        }

        // default colors
        circ.setFillColor( sf::Color::Red ); 
        for ( int i = 0; i < size; i++ ) {
            ocirc[i].setFillColor( sf::Color::Green );
            }
        // friction mode color
        if ( frictionMode ) {circ.setFillColor( sf::Color::Blue );
            for( int i = 0; i < size; i++) ocirc[i].setFillColor( sf::Color::White );
        } 
        boing(); // ball elasticity function
        moveball(); // ball movement function
        cout << cAcel.x << " " << cAcel.y << " " << cVel.x << " " << cVel.y << endl; // DEBUG print data to console

        // draw game to screen
        window.clear( sf::Color::Black );
        window.draw( circ );
        for( int i = 0; i < size; i++) window.draw( ocirc[i] );
        window.display();
    }

    return 0;
}