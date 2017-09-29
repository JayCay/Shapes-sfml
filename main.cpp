#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace std;

// DEFINES
#define RADIUS 30.0f
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
    float mass = MASS;
    float friction = FRICTION;
    float acceleration = ACCELERATION;
    sf::Vector2f cPos( 0.0f, 0.0f );
    sf::Vector2f cVel( 0.0f, 0.f );
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

        //friction mode toggle
        if ( keyFrictionPressed ) {
            keyFrictionPressed = false;
            frictionMode = !frictionMode;
        }

        //change ball's current velocity
        if ( keyUpPressed ) cVel.y -= acceleration;
        if ( keyDownPressed ) cVel.y +=  acceleration;
        if ( keyLeftPressed ) cVel.x -= acceleration;
        if ( keyRightPressed ) cVel.x += acceleration;
        circ.setFillColor( sf::Color::Red );

        //friction  mode
        if ( frictionMode ) {
            cVel -= ((friction *cVel)/mass);
            circ.setFillColor( sf::Color::Blue );
        }

        cPos = circ.getPosition();

        //elasticity
        if ( cPos.y - RADIUS < 0.f || cPos.y == 0.f || cPos.y + RADIUS > HEIGHT || cPos.x == HEIGHT ) cVel.y = -ELASTICITY * cVel.y;
        if ( cPos.x - RADIUS < 0.f || cPos.x == 0.f || cPos.x + RADIUS > WIDTH  || cPos.x == WIDTH ) cVel.x = -ELASTICITY * cVel.x;

        cPos += cVel;

        //ball movement
        circ.setPosition( cPos.x, cPos.y );

        // draw game to screen
        window.clear( sf::Color::Black );
        window.draw( circ );
        window.display();
    }

    return 0;
}