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
#define OMASS 0.5f

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
float omass = OMASS;
float friction = FRICTION;

sf::CircleShape circ[36];
sf::Vector2f cPos[36];
sf::Vector2f cVel[36];
sf::Vector2f cAcel[36];

sf::RenderWindow window( sf::VideoMode( WIDTH, HEIGHT ), "shape me" );

void makeCircles(int x, sf::CircleShape circ[]) {
        int spacex = ORADIUS; 
        int spacey = ORADIUS;
        for ( int i = 1; i < x; i++ ) {
            circ[i].setRadius( ORADIUS );
            circ[i].setFillColor( sf::Color::Green );
            if( i == 1 ){
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

void moveball( int size){
    for ( int i = 0; i < size; i++ ) {
    cPos[i] = circ[i].getPosition();
    cVel[i] += ( cAcel[i] * TIMESTEP );
    cPos[i] += ( 0.5f * cAcel[i] * TIMESTEP * TIMESTEP ) + ( cVel[i] * TIMESTEP );
    if ( frictionMode )cVel[i] -= ( ( friction *cVel[i] ) / mass );
    circ[i].setPosition( cPos[i] );
    }
}

void boing(int size){
    for ( int i = 0; i < size; i++ ) {
    cPos[i] = circ[i].getPosition();
        //elasticity
        if ( cPos[i].y  < 0.f + RADIUS ){   
            cPos[i].y = 0 + RADIUS;
            cVel[i].y = -ELASTICITY * cVel[i].y;
            circ[i].setPosition( cPos[i] );
            }
        if (cPos[i].y > HEIGHT - 1.f - RADIUS){
            cPos[i].y = HEIGHT - RADIUS -1.f;
            cVel[i].y = -ELASTICITY * cVel[i].y;
            circ[i].setPosition( cPos[i] );
        }
        if ( cPos[i].x < 0.f + RADIUS ){
            cPos[i].x = 0 + RADIUS;
            cVel[i].x = -ELASTICITY * cVel[i].x;
            circ[i].setPosition( cPos[i] );
        }

        if(cPos[i].x  > WIDTH -1.f - RADIUS ){
            cPos[i].x = WIDTH - RADIUS -1.f;
            cVel[i].x = -ELASTICITY * cVel[i].x;
            circ[i].setPosition( cPos[i] );
        }
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
        if ( x >= 1 && x <= 35 ) size = x + 1;
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

    //sf::CircleShape circ[size];
    // initialise drawing the circle
    circ[0].setRadius( RADIUS );
    circ[0].setOrigin( RADIUS, RADIUS );
    circ[0].setFillColor( sf::Color::Red );
    circ[0].setPosition( 50, 50 );
    
     
    
    makeCircles( size, circ );

    while ( window.isOpen() ) {
        // handle input
        sf::Event event;
        while ( window.pollEvent(event) ) {
            if ( event.type == sf::Event::Closed ) window.close();
            if ( event.type == sf::Event::KeyPressed ) {
                if ( event.key.code == keyUp ) cAcel[0].y -= (force * mass);
                if ( event.key.code == keyDown ) cAcel[0].y +=  force * mass;
                if ( event.key.code == keyLeft) cAcel[0].x -= (force * mass);
                if ( event.key.code == keyRight) cAcel[0].x += force * mass;
                if ( event.key.code == keyClose ) keyClosePressed = true;
                if ( event.key.code == keyFriction ) keyFrictionPressed = true;
            }
            if ( event.type == sf::Event::KeyReleased ) {
                if ( event.key.code == keyUp ) cAcel[0].y = 0;
                if ( event.key.code == keyDown ) cAcel[0].y = 0;
                if ( event.key.code == keyLeft ) cAcel[0].x = 0;
                if ( event.key.code == keyRight ) cAcel[0].x = 0;
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
        circ[0].setFillColor( sf::Color::Red ); 
        for ( int i = 1; i < size; i++ ) {
            circ[i].setFillColor( sf::Color::Green );
            }
        // friction mode color
        if ( frictionMode ) {circ[0].setFillColor( sf::Color::Blue );
            for( int i = 1; i < size; i++) circ[i].setFillColor( sf::Color::White );
        } 
        boing(size); // ball elasticity function
        moveball(size); // ball movement function
        cout << cAcel[0].x << " " << cAcel[0].y << " " << cVel[0].x << " " << cVel[0].y << endl; // DEBUG print data to console

        // draw game to screen
        window.clear( sf::Color::Black );
        window.draw( circ[0] );
        for( int i = 1; i < size; i++) window.draw( circ[i] );
        window.display();
    }

    return 0;
}