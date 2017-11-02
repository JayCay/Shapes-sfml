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

//prependicular function
sf::Vector2f per(sf::Vector2f v){
	sf::Vector2f per(-v.y, v.x);
	return per;
}
//dot product function
float dotProduct(sf::Vector2f a, sf::Vector2f b){
	return ((a.x * b.x) + (a.y * b.y));
}


vector<sf::Vector2f> getAxes(sf::ConvexShape shape, sf::ConvexShape shape2){
	vector<sf::Vector2f> axesToCheck;

	for(int i = 0; i< shape.getPointCount() - 1; i++)
	{
		axesToCheck.push_back(per(shape.getTransform().transformPoint(shape.getPoint(i))- shape.getTransform().transformPoint(shape.getPoint(i+1))));
	}
	axesToCheck.push_back(per(shape.getTransform().transformPoint(shape.getPoint(shape.getPointCount() - 1)) - shape.getTransform().transformPoint(shape.getPoint(0))));
	for(int j = 0; j < shape2.getPointCount() - 1; j++){
		axesToCheck.push_back(per(shape2.getTransform().transformPoint(shape2.getPoint(j)) - shape2.getTransform().transformPoint(shape2.getPoint(j+1))));
	}
	axesToCheck.push_back(per(shape.getTransform().transformPoint(shape2.getPoint(shape2.getPointCount() - 1)) - shape2.getTransform().transformPoint(shape2.getPoint(0))));
	return axesToCheck;
}
//get minumum point
float getMin(sf::ConvexShape shape, sf::Vector2f u){
	float shapMin = dotProduct(shape.getTransform().transformPoint(shape.getPoint(0)),u);
	for(int i = 1;i<shape.getPointCount();i++){
		float minCheck = dotProduct(shape.getTransform().transformPoint(shape.getPoint(i)),u);
		if(minCheck < shapMin) shapMin = minCheck;
	}
	return shapMin;
}

//get maximum point
float getMax(sf::ConvexShape shape, sf::Vector2f u){
	float shapMax = dotProduct(shape.getTransform().transformPoint(shape.getPoint(0)),u);
	for(int i = 1;i<shape.getPointCount();i++){
		float maxCheck = dotProduct(shape.getTransform().transformPoint(shape.getPoint(i)),u);
		if(maxCheck > shapMax) shapMax = maxCheck;
	}
	return shapMax;
}

//SAT collision check
bool isSatCollide(sf::ConvexShape shape, sf::ConvexShape shape2)
{
	vector<sf::Vector2f> check = getAxes(shape, shape2);
	int overlapCounter = 0;
	for(int i = 0; i < check.size(); i++){
		float shapeMin = getMin(shape, check.at(i));
		float shape2Min = getMin(shape2, check.at(i));
		float shapeMax = getMax(shape, check.at(i));
		float shape2Max = getMax(shape2, check.at(i));
		if(shape2Min > shapeMax || shape2Max < shapeMin) break;
		else overlapCounter++;
	}
	if(overlapCounter == check.size()) return true; 
	else return false;

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
	
	int numShapes;
	cin >> numShapes;

	//draw shapes
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
		shapesArray[i].setFillColor(sf::Color::Green);
		shapesArray[i].setOutlineColor(sf::Color::Blue);
		shapesArray[i].setOutlineThickness(2);
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
		if ( keyUpPressed ) shapesArray[0].move(0,-80*TIMESTEP);
        if ( keyDownPressed ) shapesArray[0].move(0,80*TIMESTEP);
        if ( keyLeftPressed ) shapesArray[0].move(-80*TIMESTEP,0);
        if ( keyRightPressed ) shapesArray[0].move(80*TIMESTEP,0);


        //rotate mode toggle
        if ( keyRotatePressed ) {
            keyRotatePressed = false;
            rotateMode = !rotateMode;
        }
        //polygon rotation
        if (rotateMode){
        	for(int i = 0; i < numShapes; i++){
			shapesArray[i].rotate((i + 1) +(3 * TIMESTEP) );
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
		drawaabb[i].setOutlineColor(sf::Color::Blue);
		drawaabb[i].setOutlineThickness(1);
		colcheck[i] = sf::Vector2f(aabb[i].left,aabb[i].top);
	}
		
		//default polygon color
		for (int i = 0;i < numShapes;i++){
			shapesArray[i].setFillColor(sf::Color::Green);
		}

		//aabb collision 
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
					shapesArray[i].setFillColor(sf::Color::Yellow);
					shapesArray[x].setFillColor(sf::Color::Yellow);
					}
				}
			}
		}

		//SAT collision
		for(int i = 0; i < numShapes; i++){
			for(int j = 0; j < numShapes; j++){
				if(i != j){
					if(isSatCollide(shapesArray[i], shapesArray[j])){
						shapesArray[i].setFillColor(sf::Color::Red);
						shapesArray[j].setFillColor(sf::Color::Red);
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
