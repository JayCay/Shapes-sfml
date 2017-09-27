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
    // movement constants
    float circleInput = 200.0/FPS;
    float autoMovement = 20.0/FPS;
    // vector constants
    float velocity = 0.0f;
    float acceleration = 2.0f;
    float friction = 0.0f;
    float elas = 0.0f;

    // initialise drawing the circle
    circ.setRadius( 30.f );
    circ.setFillColor( sf::Color::Red );

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
            // mouse
        }

        if ( keyClosePressed ) {
            keyClosePressed = false;
            window.close();
        }

        sf::Time ElapsedTime = Clock.getElapsedTime();

        // update game objects
        // circ input
        //f::Vector2f cVel = circ.getPosition();
        //sf::Vector2f cVel =  circ.getPosition();

        sf::Vector2f cPos = circ.getPosition();

        sf::Vector2f cVec(0.0f,0.0f);
        if ( keyUpPressed ) cVec.y -= circleInput;
        if ( keyDownPressed ) cVec.y += circleInput;
        if ( keyLeftPressed ) cVec.x -= circleInput;
        if ( keyRightPressed ) cVec.x += circleInput;



        sf::Vector2f normVec(cVec.x/sqrt(cVec.x * cVec.x + cVec.y * cVec.y),cVec.y/sqrt(cVec.x * cVec.x + cVec.y * cVec.y));
        
        normVec = normVec * acceleration;

        cVec.y += normVec.y;
        cVec.x += normVec.x;

        sf::Vector2f dVec(cVec.x,cVec.y);

        cPos.x += dVec.x;
        cPos.y += dVec.y;

        circ.setPosition(dVec.x,dVec.y);



        



        // draw game to screen
        window.clear( sf::Color::Black );
        window.draw( circ );
        window.display();
    }

    return 0;
}