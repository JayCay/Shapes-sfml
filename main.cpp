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
    sf::Vector2f cAcel(0.0f, 0.0f );
    sf::CircleShape circ;
    sf::RenderWindow window( sf::VideoMode( WIDTH, HEIGHT ), "shape v6.10" );

void moveball(){
    cPos = circ.getPosition();
    cVel += (cAcel * TIMESTEP);
    cPos += (0.5f * cAcel * TIMESTEP * TIMESTEP) + (cVel * TIMESTEP);
    if ( frictionMode )cVel -= ((friction *cVel)/mass);
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

int main() {

    window.setFramerateLimit( FPS );
    window.setActive( false );
    window.setKeyRepeatEnabled(false);

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
        //close window
        if ( keyClosePressed ) {
            keyClosePressed = false;
            window.close();
        }

        //friction mode toggle
        if ( keyFrictionPressed ) {
            keyFrictionPressed = false;
            frictionMode = !frictionMode;
        }

        //default color
        circ.setFillColor( sf::Color::Red );
        //friction  mode
        if ( frictionMode ) {
            circ.setFillColor( sf::Color::Blue );
        }


        //elasticity
        boing();

        //ball movement
        moveball();
       

        
        cout << cAcel.x << " " << cAcel.y << " " << cVel.x << " " << cVel.y << endl;

        // draw game to screen
        window.clear( sf::Color::Black );
        window.draw( circ );
        window.display();
    }

    return 0;
}