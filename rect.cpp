#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#define FPS 60
#define RecSIZE 7
#define WIDTH 800
#define HEIGHT 600
#define TIMESTEP 1.f/FPS
#define THETA1 1
#define THETA2 4
#define THETA3 8
#define THETA4 12
#define THETA5 15
#define THETA6 20
#define THETA7 50

using namespace std;

sf::RectangleShape rect[RecSIZE];
sf::RectangleShape aabb[RecSIZE];
sf::RectangleShape oaabb[RecSIZE];
float angle[RecSIZE];

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
	rect[0].setSize( sf::Vector2f( 65.f, 190.f ) );
	rect[1].setSize( sf::Vector2f( 50.f, 200.f ) );
	rect[2].setSize( sf::Vector2f( 20.f, 28.f ) );
	rect[3].setSize( sf::Vector2f( 200.f, 200.f ) );
	rect[4].setSize( sf::Vector2f( 280.f, 50.f ) );
	rect[5].setSize( sf::Vector2f( 310.f, 70.f ) );
	rect[6].setSize( sf::Vector2f( 300.f, 45.f ) );

	for ( int i = 0; i < RecSIZE; i++ ) {
		//posw = rand() % WIDTH + 1;
		//posh = rand() % HEIGHT + 1;
		sizew = ( ( rect[i].getSize().x ) / 2 );
		sizeh = ( ( rect[i].getSize().y ) / 2 );
		rect[i].setOrigin( sizew, sizeh );
		//rect[i].setPosition( 400, 300 );
		rect[i].setFillColor( sf::Color::Green );
	}
	rect[0].setPosition( 120 , 495 );
	rect[1].setPosition( 100, 140 );
	rect[2].setPosition( 640, 415 );
	rect[3].setPosition( 375 , 310 );
	rect[4].setPosition( 600 , 489 );
	rect[5].setPosition( 400 , 600 );
	rect[6].setPosition( 430 , 50 );


	//Making the first aabbs
	for (int i = 0;i < RecSIZE;i++){
		aabb[i].setSize(sf::Vector2f(rect[i].getSize()));
		oaabb[i].setSize(sf::Vector2f(rect[i].getSize()));
		aabb[i].setFillColor(sf::Color::Transparent); 
		aabb[i].setOutlineColor(sf::Color::Red);
		aabb[i].setOutlineThickness(1);
		aabb[i].setOrigin( rect[i].getOrigin() );
		aabb[i].setPosition(rect[i].getPosition());
	}

	while ( window.isOpen() ) {
		sf::Event event;
		while ( window.pollEvent( event ) ) {
			if ( event.type == sf::Event::Closed ) window.close();
		}

		
		//Rectangle rotation
		rect[0].rotate(THETA1 * TIMESTEP);
		rect[1].rotate(THETA2 * TIMESTEP);
		rect[2].rotate(THETA3 * TIMESTEP);
		rect[3].rotate(THETA4 * TIMESTEP);
		rect[4].rotate(THETA5 * TIMESTEP);
		rect[5].rotate(THETA6 * TIMESTEP);
		rect[6].rotate(THETA7 * TIMESTEP);

		//theta
		angle[0] +=  THETA1 * TIMESTEP;
		angle[1] +=  THETA2 * TIMESTEP;
		angle[2] +=  THETA3 * TIMESTEP;
		angle[3] +=  THETA4 * TIMESTEP;
		angle[4] +=  THETA5 * TIMESTEP;
		angle[5] +=  THETA6 * TIMESTEP;
		angle[6] +=  THETA7 * TIMESTEP;

		//drawing new aabbs
		for ( int i = 0; i < RecSIZE; i++ ){
		float x_o = oaabb[i].getSize().x;
		float y_o = oaabb[i].getSize().y;		
		float x_n = (x_o * abs(cos((angle[i]* M_PI/180)))) + (y_o * abs(sin((angle[i]* M_PI/180))));
		float y_n = (y_o * abs(cos((angle[i]* M_PI/180)))) + (x_o * abs(sin((angle[i]* M_PI/180))));
		aabb[i].setSize(sf::Vector2f(x_n,y_n));
		aabb[i].setOrigin(x_n/2,y_n/2);
		aabb[i].setPosition(rect[i].getPosition());
		}

		//default rectangle color
		for (int i = 0;i < RecSIZE;i++){
			rect[i].setFillColor(sf::Color::Green);
		}

		//collision detection
		for ( int i = 0; i < RecSIZE; i++ ){
				float c1x = aabb[i].getPosition().x;
				float c1y = aabb[i].getPosition().y;

				float rad1x = aabb[i].getSize().x / 2;
				float rad1y = aabb[i].getSize().y / 2;
			for (int x = 0;x < i;x++){
				if (i != x){
				float c2x = aabb[x].getPosition().x;
				float c2y = aabb[x].getPosition().y;

				float rad2x = aabb[x].getSize().x / 2;
				float rad2y = aabb[x].getSize().y / 2;
			 
				if(abs(c1x - c2x) > (rad1x + rad2x) || abs(c1y - c2y)  > (rad1y + rad2y))
				{
					//no colllision
					}
				else{
					//collision detected
					//rectangle change color
					rect[i].setFillColor(sf::Color::Blue);
					rect[x].setFillColor(sf::Color::Blue);
					}
				}
			}
		}
		window.clear( sf::Color::Black );
		for ( int i = 0; i < RecSIZE; i++ ){
		window.draw( rect[i] );
		window.draw( aabb[i] );
		}
		window.display();

	}

	return 0;
}
