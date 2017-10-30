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



sf::ConvexShape shapesArray[9999];
sf::FloatRect aabb[9999];
sf::RectangleShape drawaabb[9999] ;
sf::FloatRect oaabb[9999];
sf::Vector2f colcheck[9999];


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

        
        //get aabbs
        for(int i = 0; i < numShapes; i++){
		sf::Vector2f minimum = shapesArray[i].getTransform().transformPoint(shapesArray[i].getPoint(0));
		sf::Vector2f maximum = minimum;
		for(int x = 1; x < shapesArray[i].getPointCount(); ++x){
			sf::Vector2f point = shapesArray[i].getTransform().transformPoint(shapesArray[i].getPoint(x));
			minimum.x = min(minimum.x, point.x);
			maximum.x = max(maximum.x, point.x);
			minimum.y = min(minimum.y, point.y);
			maximum.y = max(maximum.y, point.y);
		}
		aabb[i] = sf::FloatRect(minimum, maximum - minimum);
		drawaabb[i].setSize(sf::Vector2f(aabb[i].width,aabb[i].height));
		drawaabb[i].setPosition(aabb[i].left,aabb[i].top);
		drawaabb[i].setFillColor(sf::Color::Transparent);
		drawaabb[i].setOutlineColor(sf::Color::Red);
		drawaabb[i].setOutlineThickness(1);
		colcheck[i] = sf::Vector2f(aabb[i].left,aabb[i].top);
	}
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
		
		for ( int i = 0; i < numShapes; i++ ){
			sf::Vector2f i2x;
			for (int x = 0;x < i;x++){
				if (i != x){
				i2x = colcheck[i] - colcheck[x];
				if(i2x.x > drawaabb[x].getSize().x|| -i2x.x > drawaabb[i].getSize().x || i2x.y > drawaabb[x].getSize().y || -i2x.y > drawaabb[i].getSize().y)
				{
					//no colllision
					}
				else{
					//collision detected
					//rectangle change color
					shapesArray[i].setFillColor(sf::Color::Green);
					shapesArray[x].setFillColor(sf::Color::Green);
					}
				}
			}
		}
		
		window.clear( sf::Color::Black );
		for ( int i = 0; i < numShapes; i++ ){
		window.draw( shapesArray[i] );
		window.draw( drawaabb[i] );
		}
		window.display();

	}

	return 0;
}
