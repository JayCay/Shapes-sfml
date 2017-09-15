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
		for ( int i = 0; i < CirSIZE; i++ ) circ[i].move( 0 , movement );
		for ( int i = 0; i < RecSIZE; i++ ) rect[i].move( movement, 0 );
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
			if ( event.type == sf::Event::Closed ) window.close();
		}
	}

	return 0;
}
