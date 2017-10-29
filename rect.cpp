#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <stdlib.h>

#define FPS 60
#define RecSIZE 7
#define WIDTH 800
#define HEIGHT 600
#define TIMESTEP 1.f/FPS

#define keyUp sf::Keyboard::W
#define keyDown sf::Keyboard::S
#define keyLeft sf::Keyboard::A
#define keyRight sf::Keyboard::D
#define keyClose sf::Keyboard::Escape
#define keyRotate sf::Keyboard::F

using namespace std;

bool keyDownPressed = false;
bool keyUpPressed = false;
bool keyLeftPressed = false;
bool keyRightPressed = false;
bool keyClosePressed = false;
bool keyRotatePressed = false;
bool rotateMode = false;


sf::RectangleShape rect[RecSIZE];
sf::ConvexShape shapesArray[9999];
sf::FloatRect aabb[9999];
sf::FloatRect oaabb[9999];


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
	
	int numShapes;
	cin >> numShapes;

	for (int i = 0; i < numShapes; i++) {
		int numPoints;
		cin >> numPoints;
		shapesArray[i].setPointCount(numPoints);
		for (int j = 0; j < numPoints; j++) {
			float x, y;
			cin >> x;
			cin >> y;
			sf::Vector2f point(x,y);
			shapesArray[i].setPoint(j, point);
		}
		int posX, posY;
		cin >> posX;
		cin >> posY;
		shapesArray[i].setPosition(posX, posY);
		oaabb[i] = shapesArray[i].getLocalBounds();
		shapesArray[i].setOrigin(oaabb[i].left + oaabb[i].width/2, oaabb[i].top + oaabb[i].height/2);
		shapesArray[i].setFillColor(sf::Color::Blue);

	}

	while ( window.isOpen() ) {
		sf::Event event;
		while ( window.pollEvent( event ) ) {
            if ( event.type == sf::Event::Closed ) window.close();
            if ( event.type == sf::Event::KeyPressed ) {
                if ( event.key.code == keyUp ) keyUpPressed = true;
                if ( event.key.code == keyDown ) keyDownPressed = true;
                if ( event.key.code == keyLeft) keyLeftPressed = true;
                if ( event.key.code == keyRight) keyRightPressed = true;
                if ( event.key.code == keyClose ) keyClosePressed = true;
                if ( event.key.code == keyRotate ) keyRotatePressed = true;
            }
            if ( event.type == sf::Event::KeyReleased ) {
                if ( event.key.code == keyUp ) keyUpPressed =  false;
                if ( event.key.code == keyDown ) keyDownPressed = false;
                if ( event.key.code == keyLeft ) keyLeftPressed = false;
                if ( event.key.code == keyRight ) keyRightPressed = false;
                if ( event.key.code == keyClose ) keyClosePressed = false;
                if ( event.key.code == keyRotate ) keyRotatePressed = false;
            } 
		}

		
		//polygon movement
		if ( keyUpPressed ) shapesArray[0].move(0,-50*TIMESTEP);
        if ( keyDownPressed ) shapesArray[0].move(0,50*TIMESTEP);
        if ( keyLeftPressed ) shapesArray[0].move(-50*TIMESTEP,0);
        if ( keyRightPressed ) shapesArray[0].move(50*TIMESTEP,0);


        //rotate mode toggle
        if ( keyRotatePressed ) {
            keyRotatePressed = false;
            rotateMode = !rotateMode;
        }
        //polygon rotation
        if (rotateMode){
        	for(int i = 0; i < numShapes; i++){
			shapesArray[i].rotate(10 * TIMESTEP);
			}
        }

        /*
        //get aabbs
        for(int i = 0; i < numShapes; i++){
		sf::Vector2f min = shapesArray[i].getTransform().transformPoint(shapesArray[i].getPoint(0));
		sf::Vector2f max = min;
		for(int x = 1; x < shapesArray[i].getPointCount(); ++x){
			sf::Vector2f point = shapesArray[i].getTransform().transformPoint(shapesArray[i].getPoint(x));
			min.x = min(min.x, point.x);
			max.x = max(max.x, point.x);
			min.y = min(min.y, point.y);
			max.y = max(max.y, point.y);
		}
		aabb[i] = FloatRect(min, max-min);
		aabb[i].setFillColor(sf::Color::Transparent);
		aabb[i].setOutlineColor(sf::Color::Red);
		aabb[i].setOutlineThickness(1)
		//drawing new aabbs
		/*
		for ( int i = 0; i < RecSIZE; i++ ){
		float x_o = oaabb[i].getSize().x;
		float y_o = oaabb[i].getSize().y;		
		float x_n = (x_o * abs(cos((angle[i]* M_PI/180)))) + (y_o * abs(sin((angle[i]* M_PI/180))));
		float y_n = (y_o * abs(cos((angle[i]* M_PI/180)))) + (x_o * abs(sin((angle[i]* M_PI/180))));
		aabb[i].setSize(sf::Vector2f(x_n,y_n));
		aabb[i].setOrigin(x_n/2,y_n/2);
		aabb[i].setPosition(rect[i].getPosition());
		}
	*/
		//default polygon coflor
		for (int i = 0;i < numShapes;i++){
			shapesArray[i].setFillColor(sf::Color::Blue);
		}

		//collision detection
		
		/*for ( int i = 0; i < RecSIZE; i++ ){
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
		*/
		window.clear( sf::Color::Black );
		for ( int i = 0; i < numShapes; i++ ){
		window.draw( shapesArray[i] );
		//window.draw( aabb[i] );
		}
		window.display();

	}

	return 0;
}
