#pragma once

//C/C++ libraries
#include <vector>

//other items
#include "Point.h"

class Country
{
public:
	Country();
	~Country();

	//draw the country
	void draw();

	//check if point is inside country


private:
	//points that make the country shape
	std::vector<Point> CountryPoints;

	#pragma region Country Attributes

	//country population
	int population;


	#pragma endregion
};

Country::Country()
{
}


Country::~Country()
{
}

