#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

// DEFINES
#define FPS 60
#define numCircle 60
#define numRect 40
#define numColor 6
// keybindings
#define keyUp sf::Keyboard::W
#define keyDown sf::Keyboard::S
#define keyLeft sf::Keyboard::A
#define keyRight sf::Keyboard::D
#define keyClose sf::Keyboard::Escape

int colorcycle( int count ) {
    if ( count >= numColor ) {
        int n = count % numColor;
        return n;
    }
    else return count;
}

int main() {
    srand( time( NULL ) );
    int width = 800; int height = 720;
    sf::RenderWindow window( sf::VideoMode( width, height ), "shapes v3" );
    window.setFramerateLimit( FPS );
    window.setActive( false );
    sf::CircleShape circ[numCircle];
    sf::RectangleShape rect[numRect];
    // colors
    sf::Color color[numColor];
    color[0] = sf::Color::Red;
    color[1] = sf::Color::Green;
    color[2] = sf::Color::Blue;
    color[3] = sf::Color::Yellow;
    color[4] = sf::Color::Cyan;
    color[5] = sf::Color::White;
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

    // initialise drawing circles
    for ( int i = 0; i < numCircle; i++ ) {
        circ[i].setRadius( 30.f );
        circ[i].setPosition( rand() % width + 1, rand() % height + 1 );
        circ[i].setFillColor( color[colorcycle(i)] );
    }

    // initialise drawing squares
    for ( int i = 0; i < numRect; i++ ) {
        rect[i].setSize( sf::Vector2f( 50.f, 50.f ) );
        rect[i].setPosition( rand() % width + 1, rand() % height + 1 );
        rect[i].setFillColor( color[colorcycle(i)] );
    }

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
            if ( event.type == sf::Event::MouseButtonPressed ) if ( event.mouseButton.button == sf::Mouse::Left ) buttonLeftPressed = true;
            if ( event.type == sf::Event::MouseButtonReleased ) if ( event.mouseButton.button == sf::Mouse::Left ) buttonLeftPressed = false;
        }

        if ( keyClosePressed ) {
            keyClosePressed = false;
            window.close();
        }

        // update game objects
        // other circles and other rectangles auto movement, note the int i = 1
        for ( int i = 1; i < numCircle; i++ ) circ[i].move( 0 , autoMovement );
        for ( int i = 1; i < numRect; i++ ) rect[i].move( autoMovement, 0 );
        // circ[0] input
        if ( keyUpPressed ) circ[0].move( 0, -circleInput );
        if ( keyDownPressed ) circ[0].move( 0, circleInput );
        if ( keyLeftPressed ) circ[0].move( -circleInput, 0 );
        if ( keyRightPressed ) circ[0].move( circleInput, 0 );
        // rect[0] input        
        if ( buttonLeftPressed ) {
            cout << "mouse coords: " << event.mouseButton.x << ", " << event.mouseButton.y << endl;
        }
        // draw game to screen
        window.clear( sf::Color::Black );
        for ( int n = 0; n < numCircle; n++ ) window.draw( circ[n] );
        for ( int i = 0; i < numRect; i++ ) window.draw( rect[i] );
        window.display();
    }

    return 0;
}