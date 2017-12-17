#pragma once

//SDL Library
#include <SDL\SDL.h>

//C/C++ libraries
#include <vector>
#include <string>

/**
* Country Class
* class which is used to store the values of one country which is loaded from a file
*/
class Country
{
public:
	//default constructor
	Country();
	//main constructor
	Country(std::string ID, std::string cName, int red, int green, int blue, int pop);
	~Country();

	//getters for the country data
	/**
	* getID
	* returns a country's ID
	*
	* @return id
	*/
	std::string getID() { return id; };

	/**
	* getCountryName
	* returns a country's Name
	*
	* @return cname
	*/
	std::string getCountryName() { return cname; };

	/**
	* getColour
	* returns a country's colour
	*
	* @return cColour (return type is SDL_Color)
	*/
	SDL_Color getColour() { return cColour; };

	/**
	* getPopulation
	* returns a country's population
	*
	* @return population
	*/
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

/**
* Country default constructor
* empty constructor
*/
Country::Country()
{
}

/**
* Country constructor
* used to instantiate a country with values passed from the file
* 
* @param string ID
* @param string cName (country name)
* @param int red (red colour value)
* @param int green (green colour value)
* @param int blue (blue colour value)
* @param int pop (country population)
*/
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

/**
* Country destructor
* For when a country needs to be made great again
*/
Country::~Country()
{
}

