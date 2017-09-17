#include <SFML/Graphics.hpp>
#include <iostream>

#define FPS 60
#define CSIZE 6
#define CirSIZE 60
#define RecSIZE 40

using namespace std;

sf::CircleShape circ[CirSIZE];
sf::RectangleShape rect[RecSIZE];
float movement = 20.0 / FPS;

// keybinding
#define keyUp sf::Keyboard::W
#define keyDown sf::Keyboard::S
#define keyLeft sf::Keyboard::A
#define keyRight sf::Keyboard::D
#define keyQuit sf::Keyboard::Escape

int colorcycle( int count ) {
	if ( count >= CSIZE ) {
		int n = count % CSIZE;
		return n;
	}
	else return count;
}

void threader( sf::RenderWindow* window ) {
	while(window->isOpen()) {
		window->clear( sf::Color::Black );
		for ( int n = 0; n < CirSIZE; n++ ) window->draw( circ[n] );
		for ( int i = 0; i < RecSIZE; i++ ) window->draw( rect[i] );
		window->display();
		// only moves 2nd to n objects (1 to size)
		for ( int i = 1; i < CirSIZE; i++ ) circ[i].move( 0 , movement );
		for ( int i = 1; i < RecSIZE; i++ ) rect[i].move( movement, 0 );
	}
}

int main() {
	srand( time( NULL ) );
	int width = 800;
	int height = 720;
	sf::RenderWindow window( sf::VideoMode( width, height ), "shapes v2" );
	sf::Color color[CSIZE];
	color[0] = sf::Color::Red;
	color[1] = sf::Color::Green;
	color[2] = sf::Color::Blue;
	color[3] = sf::Color::Yellow;
	color[4] = sf::Color::Cyan;
	color[5] = sf::Color::White;
	window.setFramerateLimit( FPS );
	window.setActive( false );
	int posw = 0;
	int posh = 0;
	int curr = 0;
	bool keyUpPressed = false;
	bool keyDownPressed = false;
	bool keyLeftPressed = false;
	bool keyRightPressed = false;
	bool keyQuitPressed = false;
	
	for ( int i = 0; i < CirSIZE; i++ ) {
		curr = colorcycle( i );
		posw = rand() % width + 1;
		posh = rand() % height + 1;
		circ[i].setRadius( 30.f );
		circ[i].setPosition( posw, posh );
		circ[i].setFillColor( color[curr] );
	}

	for ( int i = 0; i < RecSIZE; i++ ) {
		curr = colorcycle( i );
		posw = rand() % width + 1;
		posh = rand() % height + 1;
		rect[i].setSize( sf::Vector2f( 50.f, 50.f ) );
		rect[i].setPosition( posw, posh );
		rect[i].setFillColor( color[curr] );
	}

	sf::Thread thread( &threader, &window );
	thread.launch();

	while ( window.isOpen() ) {
		sf::Event event;
		while ( window.pollEvent( event ) ) {
			switch( event.type ) {
				case sf::Event::KeyPressed:
					switch( event.key.code ) {
						case keyUp:
							keyUpPressed = true;
							break;
						case keyDown:
							keyDownPressed = true;
							break;
						case keyLeft:
							keyLeftPressed = true;
							break;
						case keyRight:
							keyRightPressed = true;
							break;
						case keyQuit:
							keyQuitPressed = true;
							break;
					}
					break;
				case sf::Event::KeyReleased:
					switch( event.key.code ) {
						case keyUp:
							keyUpPressed = false;
							break;
						case keyDown:
							keyDownPressed = false;
							break;
						case keyLeft:
							keyLeftPressed = false;
							break;
						case keyRight:
							keyRightPressed = false;
							break;
						case keyQuit:
							keyQuitPressed = false;
							break;
					}
					break;
				case sf::Event::Closed:
					window.close();
					break;
			}
		}
	}

	// input/movement code
	while (keyUpPressed) circ[0].move(0, -200);

	return 0;
}
