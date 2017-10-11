#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace std;

// DEFINES
#define RADIUS 30.0f
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

int main() {
    sf::RenderWindow window( sf::VideoMode( WIDTH, HEIGHT ), "shape v6.10" );
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
    float circleInput = 20.0 / FPS;
    float autoMovement = 20.0 / FPS;
    // vector math
    //float getTime = TIMESTEP;
    float force = FORCE;
    float mass = 1.f/MASS;
    float friction = FRICTION;
    //sf::Vector2f cAcel(0.0f, 0.0f );
    sf::Vector2f cPos( 0.0f, 0.0f );
    sf::Vector2f cVel( 0.0f, 0.f );
    sf::Vector2f cAcel(0.0f, 0.0f );
    // initialise drawing the circle
    circ.setRadius( RADIUS );
    circ.setOrigin( RADIUS, RADIUS );
    circ.setFillColor( sf::Color::Red );
    circ.setPosition( WIDTH / 2.f, HEIGHT / 2.f );

    while ( window.isOpen() ) {
        // handle input
        sf::Event event;
        while ( window.pollEvent(event) ) {
            if ( event.type == sf::Event::Closed ) window.close();
            // keyboard
            if ( event.type == sf::Event::KeyPressed ) {
                if ( event.key.code == keyClose ) keyClosePressed = true;
                if ( event.key.code == keyFriction ) keyFrictionPressed = true;
            }
            if ( event.type == sf::Event::KeyReleased ) {
                if ( event.key.code == keyClose ) keyClosePressed = false;
                if ( event.key.code == keyFriction ) keyFrictionPressed = false;
            }
            if ( event.type == sf::Event::KeyPressed ) {
                if ( event.key.code == keyUp ) cAcel.y = -(force * mass);
                if ( event.key.code == keyDown ) cAcel.y =  force * mass;
                if ( event.key.code == keyLeft) cAcel.x = -(force * mass);
                if ( event.key.code == keyRight) cAcel.x = force * mass;
            }
            if ( event.type == sf::Event::KeyReleased ) {
                if ( event.key.code == keyUp ) cAcel.y = 0;
                if ( event.key.code == keyDown ) cAcel.y = 0;
                if ( event.key.code == keyLeft ) cAcel.x = 0;
                if ( event.key.code == keyRight ) cAcel.x = 0;
            } 

        }

        if ( keyClosePressed ) {
            keyClosePressed = false;
            window.close();
        }

        //friction mode toggle
        if ( keyFrictionPressed ) {
            keyFrictionPressed = false;
            frictionMode = !frictionMode;
        }

        //change ball's current velocity
        
           /*if( event.type == sf::Event::KeyReleased ) 
                switch(event.key.code){
                    case keyUp:
                    cAcel.y = 0;
                    break;
                    case keyLeft:
                    cAcel.x = 0;
                    break;
                    case keyDown:
                    cAcel.y = 0;
                    break;
                    case keyRight:
                    cAcel.x = 0;
                    break;
                }
                */
        circ.setFillColor( sf::Color::Red );

        

        cPos = circ.getPosition();
        cVel += (cAcel * TIMESTEP);

        

        //elasticity
        if ( cPos.y - RADIUS < 0.f ){   
            cPos.y = 0 + RADIUS;
            cVel.y = -ELASTICITY * cVel.y;
            }
        if (cPos.y + RADIUS > HEIGHT){
            cPos.y = HEIGHT - RADIUS;
            cVel.y = -ELASTICITY * cVel.y;
        }
        if ( cPos.x - RADIUS < 0.f){
            cPos.x = 0 + RADIUS;
            cVel.x = -ELASTICITY * cVel.x;
        }

        if(cPos.x + RADIUS > WIDTH ){
            cPos.x = WIDTH - RADIUS;
            cVel.x = -ELASTICITY * cVel.x;
        }

        cPos += (0.5f * cAcel * TIMESTEP * TIMESTEP) + (cVel * TIMESTEP);

        //friction  mode
        if ( frictionMode ) {
            cVel -= ((friction *cVel)/mass);
            circ.setFillColor( sf::Color::Blue );
        }

        //ball movement
        circ.setPosition( cPos.x, cPos.y );

        
        cout << cAcel.x << " " << cAcel.y << " " << cVel.x << " " << cVel.y << endl;

        // draw game to screen
        window.clear( sf::Color::Black );
        window.draw( circ );
        window.display();
    }

    return 0;
}