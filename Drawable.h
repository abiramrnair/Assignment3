#pragma once
#include <vector>
#include "Drawing.h"

class DrawObject {
private:
	COLOUR member;	
public:
	DrawObject(COLOUR arg) { // Single constructor that takes a COLOUR obj
		member = arg;
	}
	COLOUR getColour() { // Getter method to return the COLOUR obj
		return member;
	}
	virtual void draw(Drawing &obj) = 0; // Pure virtual method that accepts a reference to a Drawing obj
	virtual ~DrawObject(){} // Virtual destructor for accurate shapecount
protected: 
	std::vector<COORD> coordinateList; // Protected vector storing coord objects	
}; // class done coding

class Point :public DrawObject {
public:
	Point(COLOUR arg1, COORD arg2) :DrawObject(arg1) { // Single Point constructor
		coordinateList.push_back(arg2);
	}

	void draw(Drawing &obj) { // virtual draw implemented for point
		COLOUR setColour = getColour();
		obj.setPixel(coordinateList[0], setColour); // first coordinate is set to colour
	}
	// no destructor included
}; // class done coding

class Line :public DrawObject { 
public:
	Line(COLOUR arg1,COORD startCoord,COORD endCoord):DrawObject(arg1) { // Single Line Constructor
		coordinateList.push_back(startCoord);
		coordinateList.push_back(endCoord);
	}
	void draw(Drawing &obj) { // virtual draw implemented for line
		COLOUR lineColour = getColour();
		obj.drawLine(coordinateList[0], coordinateList[1], lineColour);
	}
   // no destructor included
}; // class done coding

class Shape :public DrawObject {
private:
	static int shapeCounter; // Static variable for shape count
public:	
	Shape(COLOUR arg1) :DrawObject(arg1) { // Single constructor accepting shape colour
		shapeCounter++; // iterator that increases +1 every time a shape is constructed
	}
	void getShapeCoord(COORD object) { // Takes coord objects and adds it to the public COORD vec
		coordinateList.push_back(object);
	}
	static int getShapeCount() { // public method to get number of shapes in existence
		return shapeCounter;
	}
	void draw(Drawing &obj) {
		COLOUR shapeColour = getColour();
		// basically for this part you just copy the line method but modify it slightly
		// one line from coord to coord and make sure it gets all tied together by linking last to first
		for (int i = 0; i < ((coordinateList.size())-1); i++) {
			obj.drawLine(coordinateList[i], coordinateList[i + 1], shapeColour); // [1,2,3,4...] where i = 1 = [0] = 1 means coord 1 and i = i + 2 
		}                                                                        // means [1] which = coord 2 so you can draw a line between the 2 points
		// Now access the first and last elements of the coordinate vector and draw a line
		obj.drawLine(coordinateList.back(), coordinateList.front(), shapeColour);
	}
	~Shape() {
		shapeCounter--; // this class has a destructor that makes sure the shape counter
	}					// reflects number of shapes in existence, (shape destroyed = one less shape).
}; // class done coding

int Shape::shapeCounter = 0; // initializing constant variable after class declaration, starts off at 0
							 // referenced from slide 29 (Unit 4-Classes-Objects.pdf)

