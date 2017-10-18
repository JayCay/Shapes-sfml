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
		rect[0].rotate(5 * TIMESTEP);
		rect[1].rotate(2 * TIMESTEP);
		rect[2].rotate(3 * TIMESTEP);
		rect[3].rotate(10 * TIMESTEP);
		rect[4].rotate(7 * TIMESTEP);

		//theta
		angle[0] +=  5 * TIMESTEP;
		angle[1] +=  2 * TIMESTEP;
		angle[2] +=  3 * TIMESTEP;
		angle[3] += 10 * TIMESTEP;
		angle[4] += 7 * TIMESTEP;

		//drawing new aabbs
		for ( int i = 0; i < RecSIZE; i++ ){
		float x_o = oaabb[i].getSize().x;
		float y_o = oaabb[i].getSize().y;		
		float x_n = (x_o * abs(std::cos((angle[i]* M_PI/180)))) + (y_o * abs(std::sin((angle[i]* M_PI/180))));
		float y_n = (y_o * abs(std::cos((angle[i]* M_PI/180)))) + (x_o * abs(std::sin((angle[i]* M_PI/180))));
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
