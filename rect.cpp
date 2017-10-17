#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#define FPS 60
#define RecSIZE 5
#define WIDTH 800
#define HEIGHT 600
#define TIMESTEP 1.f/FPS

using namespace std;

sf::RectangleShape rect[RecSIZE];
sf::RectangleShape aabb[RecSIZE];
sf::RectangleShape oaabb[RecSIZE];
float o_angle[RecSIZE];
float n_angle[RecSIZE];

float movement = 20.0 / FPS;

//void threader( sf::RenderWindow* window ) {
	//while(window->isOpen()) {
		
		//for ( int i = 0; i < RecSIZE; i++ ) rect[i].move( movement, 0 );
//	}
//}

float d2r(float degree){
	return (degree * M_PI)/180;
}

void drawaabb(float x, float y, int i, sf::RectangleShape rect[]){

		aabb[i].setSize(sf::Vector2f(x, y));
		aabb[i].setFillColor(sf::Color::Transparent); 
		aabb[i].setOutlineColor(sf::Color::Red);
		aabb[i].setOutlineThickness(1);
		aabb[i].setOrigin(rect[i].getOrigin());
		aabb[i].setPosition(rect[i].getPosition());
	


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

	for (int i = 0;i < RecSIZE;i++){
		aabb[i].setSize(sf::Vector2f(rect[i].getSize()));
		oaabb[i].setSize(sf::Vector2f(rect[i].getSize()));
		aabb[i].setFillColor(sf::Color::Transparent); 
		aabb[i].setOutlineColor(sf::Color::Red);
		aabb[i].setOutlineThickness(1);
		aabb[i].setOrigin( rect[i].getOrigin() );
		aabb[i].setPosition(rect[i].getPosition());
	}

	//sf::Thread thread( &threader, &window );
	//thread.launch();

	while ( window.isOpen() ) {
		sf::Event event;
		while ( window.pollEvent( event ) ) {
			if ( event.type == sf::Event::Closed ) window.close();
		}

		for ( int i = 0; i <RecSIZE;i++){
			o_angle[i] = n_angle[i];
		}

		rect[0].rotate(5 * TIMESTEP);
		rect[1].rotate(2 * TIMESTEP);
		rect[2].rotate(3 * TIMESTEP);
		rect[3].rotate(10 * TIMESTEP);
		rect[4].rotate(7 * TIMESTEP);

		n_angle[0] +=  5 * TIMESTEP;
		n_angle[1] +=  2 * TIMESTEP;
		n_angle[2] +=  3 * TIMESTEP;
		n_angle[3] += 10 * TIMESTEP;
		n_angle[4] += 7 * TIMESTEP;

		for ( int i = 0; i < RecSIZE; i++ ){
		float x_o = oaabb[i].getSize().x;
		float y_o = oaabb[i].getSize().y;		
		float x_n = (x_o * std::cos((n_angle[i]* M_PI/180))) - (y_o * std::sin((n_angle[i]* M_PI/180)));
		float y_n = (y_o * std::cos((n_angle[i]* M_PI/180))) + (x_o * std::sin((n_angle[i]* M_PI/180)));
		drawaabb(x_n,y_n, i, rect);
		}

		window.clear( sf::Color::Black );
		for ( int i = 0; i < RecSIZE; i++ ){ window.draw( rect[i] );
		window.draw( aabb[i] );
		}
		window.display();

	}

	return 0;
}
