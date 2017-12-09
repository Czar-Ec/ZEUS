#pragma once

//SDL Library
#include <SDL\SDL.h>

//C/C++ libraries
#include <vector>
#include <string>

class Country
{
public:
	//default constructor
	Country();
	//main constructor
	Country(std::string ID, std::string cName, int red, int green, int blue, int pop);
	~Country();

	//getters for the country data
	std::string getID() { return id; };
	std::string getCountryName() { return cname; };
	SDL_Color getColour() { return cColour; };
	int getPopulation() { return population; };


private:
	#pragma region Country Attributes
	//country unique ID
	std::string id;

	//country name
	std::string cname;

	//country colour identifier
	SDL_Color cColour;

	//country population
	int population;

	#pragma endregion
};

Country::Country()
{
}


Country::Country(std::string ID, std::string cName, int red, int green, int blue, int pop)
{
	//initiating the country with the loaded values
	id = ID;
	cname = cName;
	population = pop;

	//country colour identifier
	cColour.r = red;
	cColour.g = green;
	cColour.b = blue;
}

Country::~Country()
{
}

