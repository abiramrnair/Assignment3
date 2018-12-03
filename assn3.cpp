// Student Name: Abiram Nair
// Student Number: 250961634
// Assignment 3
// Instructor: J.Brasse, COMPSCI-1037

#include <iostream>
#include "Drawable.h"
#include "Drawing.h"
#include <string>
#include <forward_list>
using namespace std;

// Helper Functions (for the COORD and COLOUR)

void setCoordinate(int x, int y, COORD &obj) { // Coordinate helper function
	obj.row = x; 
	obj.col = y;
}

void setColour(int R, int G, int B, COLOUR &obj) { // Colour helper function 
	obj.rgb[0] = R;
	obj.rgb[1] = G;
	obj.rgb[2] = B;
}

// Main Program starts 
int main(int argc, char *argv[]) {
	cout << "Welcome to Assignment 3" << endl;
	cout << endl;
	char c;
	
	//cout << "The program is going to use " << (argc - 7) << " arguments" << endl; // File name(1) + command line arguments to make canvas (6) make up actual arguments for program
	std::forward_list<DrawObject*>CommandList; // Initialize a forward_list with DrawOjbect pointers
	int loopIterator = 6; // indicates which index contains the letter specifying P L S.

	// Main

	for (int i = 7; i < argc; i++) { // For storing inside the forward_list
		loopIterator++;
		//int miniLoopCounter = 0;

		switch (*argv[i]) {

		case 'P':
		{
			//cout << loopIterator << endl;
			//cout << "Point created" << endl;
			COLOUR clr_obj;
			setColour(atoi(argv[loopIterator + 1]), atoi(argv[loopIterator + 2]), atoi(argv[loopIterator + 3]), clr_obj);
			COORD crd_coord;
			setCoordinate(atoi(argv[loopIterator + 4]), atoi(argv[loopIterator + 5]), crd_coord);
			CommandList.push_front(new Point(clr_obj, crd_coord));
			break;
		}
		case 'L':
		{
			//cout << loopIterator << endl;
			//cout << "Line created" << endl;
			COLOUR clr_obj;
			setColour(atoi(argv[loopIterator + 1]), atoi(argv[loopIterator + 2]), atoi(argv[loopIterator + 3]), clr_obj);
			COORD crd_coordstart;
			setCoordinate(atoi(argv[loopIterator + 4]), atoi(argv[loopIterator + 5]), crd_coordstart);
			COORD crd_coordend;
			setCoordinate(atoi(argv[loopIterator + 6]), atoi(argv[loopIterator + 7]), crd_coordend);
			CommandList.push_front(new Line(clr_obj, crd_coordstart, crd_coordend));
			break;
		}
		case 'S':
		{
			//cout << loopIterator << endl;
			//cout << "Shape created" << endl;
			COLOUR clr_obj;
			setColour(atoi(argv[loopIterator + 1]), atoi(argv[loopIterator + 2]), atoi(argv[loopIterator + 3]), clr_obj);
			Shape *shp_obj = new Shape(clr_obj);
			//miniLoopCounter = (atoi(argv[loopIterator + 4]));
			//cout << "Number of coords: " << miniLoopCounter << endl;

			for (int i = 0; i < atoi(argv[loopIterator + 4]); i++) {
				COORD crd_obj;
				setCoordinate(atoi(argv[loopIterator + (2 * i) + 5]), atoi(argv[loopIterator + (2 * i) + 6]), crd_obj);
				shp_obj->getShapeCoord(crd_obj);

			}
			CommandList.push_front(shp_obj);
			break;
		}		
		}
	}
	 
	// Initial number of shape count
	cout << "Number of shape objects are: " << Shape::getShapeCount() << endl;

	// Make canvas for the picture
	COLOUR canvasBackground;
	setColour(atoi(argv[4]), atoi(argv[5]), atoi(argv[6]), canvasBackground);
	Drawing canvasFinal(atoi(argv[2]), atoi(argv[3]), canvasBackground);
	
	// Extract values from the forward_list, draw it and then delete it.
	do{
		CommandList.front()->draw(canvasFinal);		
		delete CommandList.front();
		CommandList.pop_front();		
	} while (CommandList.empty() != true);
		
	// File BMP Save + checking to see whether successful	
	string filename = argv[1]; // TA inputs file name at index 2, which is [1]
	bool checksave = canvasFinal.saveBMP(argv[1]);
	if (checksave = true && (CommandList.empty() == true)) {
		cout << filename << " successfuly saved." << endl;
	}
	else {
		cout << filename <<  " was unsuccessful." << endl;
	}

	// Shape count after virtual destructor activated
	cout << "Number of shape objects are: " << Shape::getShapeCount() << endl;

	cin >> c;

} // Main program ends


/*GENERAL TESTING PROGRAM, making of a line, point and shape
	// Create a coordinate object using struct defn.
		COORD testingLocation;
		testingLocation.row = 25;
		testingLocation.col = 70;
		COORD testingLocation2;
		testingLocation2.row = 400;
		testingLocation2.col = 350;
		COORD testingLocation3;
		testingLocation3.row = 200;
		testingLocation3.col = 250;
		COORD shapeLocation1;
		shapeLocation1.row = 35;
		shapeLocation1.col = 80;
		COORD shapeLocation2;
		shapeLocation2.row = 20;
		shapeLocation2.col = 40;
		COORD shapeLocation3;
		shapeLocation3.row = 74;
		shapeLocation3.col = 60;
	// Create a colour object using struct defn.
		COLOUR testingColour;
		testingColour.rgb[0] = 250;
		testingColour.rgb[1] = 0;
		testingColour.rgb[2] = 0;
		COLOUR backgroundColour;
		backgroundColour.rgb[0] = 0;
		backgroundColour.rgb[1] = 0;
		backgroundColour.rgb[2] = 0;
		COLOUR shapeColour;
		shapeColour.rgb[0] = 0;
		shapeColour.rgb[1] = 255;
		shapeColour.rgb[2] = 0;
	// Make the object
		Point testPoint(testingColour, testingLocation); // individual point
		Point testPoint2(testingColour, testingLocation2); // Line point #1
		Point testPoint3(testingColour, testingLocation3); // Line point #2
	// Setting the canvas
		Drawing testObject(500, 500, backgroundColour);
	// Draw the Point Object
		testPoint.draw(testObject);
	// Draw the Line Object
		Line testLine(testingColour, testingLocation2, testingLocation3);
		testLine.draw(testObject);
	// Draw the Shape Object (make a simple triangle)
		cout << "Shape Count: " << Shape::getShapeCount() << endl; // initial shape count
		Shape shape1(shapeColour);
		shape1.getShapeCoord(shapeLocation1);
		shape1.getShapeCoord(shapeLocation2);
		shape1.getShapeCoord(shapeLocation3);
		shape1.draw(testObject);
		cout << "Shape Count: " << Shape::getShapeCount() << endl; // after creating two shapes
	// Save to .bmp + testing for successful file save
		/*string filename = "test.bmp";
		bool checksave = testObject.saveBMP(filename);
		if (checksave = true) {
			cout <<"Bitmap saving was successful!";
		}
		else {
			cout << "Bitmap saving was unsuccessful :(";
		}*/

		