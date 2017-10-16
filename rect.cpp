#include <SFML/Graphics.hpp>
#include <iostream>

#define FPS 60
#define RecSIZE 5
#define WIDTH 800
#define HEIGHT 600

using namespace std;

sf::RectangleShape rect[RecSIZE];
float movement = 20.0 / FPS;

void threader( sf::RenderWindow* window ) {
	while(window->isOpen()) {
		window->clear( sf::Color::Black );
		for ( int i = 0; i < RecSIZE; i++ ) window->draw( rect[i] );
		window->display();
		//for ( int i = 0; i < RecSIZE; i++ ) rect[i].move( movement, 0 );
	}
}

int main() {
	srand( time( NULL ) );
	int width = 800;
	int height = 720;
	sf::RenderWindow window( sf::VideoMode( WIDTH, HEIGHT ), "AABB" );
	window.setFramerateLimit( FPS );
	window.setActive( false );
	int posw = 0;
	int posh = 0;
	int sizew = 0;
	int sizeh = 0;
	
	//Making the Rectangles
	rect[0].setSize( sf::Vector2f( 225.f, 100.f ) );
	rect[1].setSize( sf::Vector2f( 90.f, 160.f ) );
	rect[2].setSize( sf::Vector2f( 640.f, 90.f ) );
	rect[3].setSize( sf::Vector2f( 40.f, 80.f ) );
	rect[4].setSize( sf::Vector2f( 180.f, 70.f ) );
	
	for ( int i = 0; i < RecSIZE; i++ ) {
		//posw = rand() % WIDTH + 1;
		//posh = rand() % HEIGHT + 1;
		sizew = ( ( rect[i].getSize().x ) / 2 );
		sizeh = ( ( rect[i].getSize().y ) / 2 );
		rect[i].setOrigin( sizew, sizeh );
		//rect[i].setPosition( 400, 300 );
		rect[i].setFillColor( sf::Color::Green );
	}
	
	rect[0].setPosition( 220 , 125 );
	rect[1].setPosition( 640, 100 );
	rect[2].setPosition( 400, 300 );
	rect[3].setPosition( 85 , 510 );
	rect[4].setPosition( 595 , 455 );

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
