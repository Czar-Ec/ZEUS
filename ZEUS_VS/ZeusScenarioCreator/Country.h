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
	Country(std::string ID, std::string cName, int red, int green, int blue, long int pop, 
		int gdp, int militarybudget, int researchbudget, int temp, int hum, std::vector<std::string> landBorder,
		std::vector<std::string> sea, std::vector<std::string> air);
	~Country();

	//getters and setters for the country data
	/**
	* getID
	* returns a country's ID
	*
	* @return id
	*/
	std::string getID() { return id; };

	/**
	* setID
	* edits the country ID
	*
	* @param string id
	*/
	void setID(std::string newID) { id = newID; };

	/**
	* getCountryName
	* returns a country's Name
	*
	* @return cname
	*/
	std::string getCountryName() { return cname; };

	/**
	* setCountryName
	* allows the modification of the country name
	*
	* @param string newCName
	*/
	void setCountryName(std::string newCName) { cname = newCName; };

	/**
	* getColour
	* returns a country's colour
	*
	* @return cColour (return type is SDL_Color)
	*/
	SDL_Color getColour() { return cColour; };

	/**
	* setColour
	* allows the modification of country region
	*
	* @param int r
	* @param int g
	* @param int b
	*/
	void setColour(int newR, int newG, int newB) { cColour.r = newR, cColour.g = newG, cColour.b = newB; };

	/**
	* getPopulation
	* returns a country's population
	*
	* @return population
	*/
	long int getPopulation() { return population; };

	/**
	* setGDP
	* allows for the country's GDP to be modified
	*
	* @param int gdp
	*/
	void setGDP(long int gdp) { countryGDP = gdp; };

	/**
	* getGDP
	* returns the country's GDP
	*
	* @return countryGDP
	*/
	long int getGDP() { return countryGDP; };

	/**
	* setMilitaryBudget
	* allows for the military budget to be modified
	* 
	* @param int mb
	*/
	void setMilitaryBudget(long int mb) { militarySpending = mb; };

	/**
	* getMilitaryBudget
	* returns the country military budget
	*
	* @return militarySpending
	*/
	long int getMilitaryBudget() { return militarySpending; };

	/**
	* setResearchBudget
	* allows for the research budget to be modified
	*
	* @param int rb
	*/
	void setResearchBudget(long int rb) { researchSpending = rb; };

	/**
	* getResearchBudget
	* returns the country research budget
	*
	* @return researchBudget
	*/
	long int getResearchBudget() { return researchSpending; };

	/**
	* getTemperature
	* returns the country's temperature type
	*
	* @return temperature
	*/
	int getTemperature() { return temperature; };

	/**
	* getHumidity
	* returns the country's humidity type
	*
	* @return humidity
	*/
	int getHumidity() { return humidity; };

	bool selectedBorder, selectedSea, selectedAir;

private:
	#pragma region Country Attributes
	//country unique ID
	std::string id;

	//country name
	std::string cname;

	//country colour identifier
	SDL_Color cColour;

	//country population
	long int population;

	//country economy variables
	long int countryGDP;
	long int militarySpending;
	long int researchSpending;

	//country environment
	long int temperature;
	long int humidity;

	//country borders and links
	std::vector<std::string> landBorders;
	std::vector<std::string> seaLinks;
	std::vector<std::string> airLinks;


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
* used to instantiate a country with values passed from the file / scenario creator
* 
* @param string ID
* @param string cName (country name)
* @param int red (red colour value)
* @param int green (green colour value)
* @param int blue (blue colour value)
* @param int pop (country population)
* @param int gdp (overall earning of country)
* @param int militarybudget
* @param int researchbudget
* @param int temp (0 - neutral, 1 - hot, 2 - cold)
* @param int hum (0 - neutral, 1 - wet, 2 - dry)
* @param vector<string> landBorder (country's neighbours)
* @param vector<string> sea (sea connections)
* @param vector<string> air (air connections)
*/
Country::Country(std::string ID, std::string cName, int red, int green, int blue, long int pop,
	int gdp, int militarybudget, int researchbudget, int temp, int hum, std::vector<std::string> landBorder,
	std::vector<std::string> sea, std::vector<std::string> air)
{
	//initiating the country with the loaded values
	id = ID;
	cname = cName;
	population = pop;

	//country colour identifier
	cColour.r = red;
	cColour.g = green;
	cColour.b = blue;

	//economic attributes
	countryGDP = gdp;
	militarySpending = militarybudget;
	researchSpending = researchbudget;

	//country climate
	temperature = temp;
	humidity = hum;

	//country borders and links
	landBorders = landBorder;
	seaLinks = sea;
	airLinks = air;

	selectedBorder = selectedSea = selectedAir = false;
}

/**
* Country destructor
* For when a country needs to be made great again
*/
Country::~Country()
{
}

