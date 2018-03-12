#pragma once

//SDL Library
#include <SDL\SDL.h>

//C/C++ libraries
#include <vector>
#include <string>
#include <algorithm>

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
	Country(std::string ID, std::string cName, int red, int green, int blue, unsigned long long int pop,
		unsigned long long int gdp, unsigned long long int militarybudget, unsigned long long int researchbudget, int temp, int hum, std::vector<std::string> landBorder,
		std::vector<std::string> sea, std::vector<std::string> air);
	~Country();

	//getters and setters for the country data
	std::string getID();
	void setID(std::string newID);

	std::string Country::getCountryName();
	void setCountryName(std::string newCName);

	SDL_Color getColour();
	void setColour(int newR, int newG, int newB);

	unsigned long long int getPopulation();

	void setGDP(unsigned long long int gdp);
	unsigned long long int getGDP();

	void setMilitaryBudget(unsigned long long int mb);
	unsigned long long int getMilitaryBudget();

	void setResearchBudget(unsigned long long int rb);
	unsigned long long int getResearchBudget();

	int getTemperature();

	int getHumidity();

	void linkLand(std::string id);
	void removeLinkLand(std::string id);
	std::vector<std::string> getLandBorders();

	void linkSea(std::string id);
	void removeLinkSea(std::string id);
	std::vector<std::string> getSeaLinks();

	void linkAir(std::string id);
	void removeLinkAir(std::string id);
	std::vector<std::string> getAirLinks();



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
	unsigned long long int population;

	//country economy variables
	unsigned long long int countryGDP;
	unsigned long long int militarySpending;
	unsigned long long int researchSpending;

	//country environment
	/**
	* Temperature values:
	* NEUTRAL TEMP = 0
	* HOT TEMP = 1
	* COLD TEMP = 2
	*/
	int temperature;

	/**
	* Humidity values:
	* NEUTRAL HUM = 0
	* WET HUM = 1
	* DRY HUM = 2
	*/
	int humidity;

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
Country::Country(std::string ID, std::string cName, int red, int green, int blue, unsigned long long int pop,
	unsigned long long int gdp, unsigned long long int militarybudget, unsigned long long int researchbudget, int temp, int hum, std::vector<std::string> landBorder,
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

/**
* getID
* returns a country's ID
*
* @return id
*/
std::string Country::getID() { return id; };

/**
* setID
* edits the country ID
*
* @param string id
*/
void Country::setID(std::string newID) { id = newID; };

/**
* getCountryName
* returns a country's Name
*
* @return cname
*/
std::string Country::getCountryName() { return cname; };

/**
* setCountryName
* allows the modification of the country name
*
* @param string newCName
*/
void Country::setCountryName(std::string newCName) { cname = newCName; };

/**
* getColour
* returns a country's colour
*
* @return cColour (return type is SDL_Color)
*/
SDL_Color Country::getColour() { return cColour; };

/**
* setColour
* allows the modification of country region
*
* @param int r
* @param int g
* @param int b
*/
void Country::setColour(int newR, int newG, int newB) { cColour.r = newR, cColour.g = newG, cColour.b = newB; };

/**
* getPopulation
* returns a country's population
*
* @return population
*/
unsigned long long int Country::getPopulation() { return population; };

/**
* setGDP
* allows for the country's GDP to be modified
*
* @param int gdp
*/
void Country::setGDP(unsigned long long int gdp) { countryGDP = gdp; };

/**
* getGDP
* returns the country's GDP
*
* @return countryGDP
*/
unsigned long long int Country::getGDP() { return countryGDP; };

/**
* setMilitaryBudget
* allows for the military budget to be modified
*
* @param int mb
*/
void Country::setMilitaryBudget(unsigned long long int mb) { militarySpending = mb; };

/**
* getMilitaryBudget
* returns the country military budget
*
* @return militarySpending
*/
unsigned long long int Country::getMilitaryBudget() { return militarySpending; };

/**
* setResearchBudget
* allows for the research budget to be modified
*
* @param int rb
*/
void Country::setResearchBudget(unsigned long long int rb) { researchSpending = rb; };

/**
* getResearchBudget
* returns the country research budget
*
* @return researchBudget
*/
unsigned long long int Country::getResearchBudget() { return researchSpending; };

/**
* getTemperature
* returns the country's temperature type
*
* @return temperature
*/
int Country::getTemperature() { return temperature; };

/**
* getHumidity
* returns the country's humidity type
*
* @return humidity
*/
int Country::getHumidity() { return humidity; };

/**
* linkLand
* function that adds a country to this country's land border list
*
* @param string id
*/
void Country::linkLand(std::string id) 
{ 
	//check if ID already in the list
	if (!(std::find(landBorders.begin(), landBorders.end(), id) != landBorders.end()))
	{
		landBorders.push_back(id); 
	}
};

/**
* removeLinkLand
* function that removes a country from this country's land border list
*
* @param string id
*/
void Country::removeLinkLand(std::string id)
{
	//loop through the land border list
	for (int i = 0; i < landBorders.size(); i++)
	{
		//remove from list if id is found
		if (id == landBorders[i])
		{
			landBorders.erase(landBorders.begin() + i);
			break;
		}
	}
}

/**
* getLandBorders
* returns a vector containing the ID's of the country's neighbours
*
* @return landBorders
*/
std::vector<std::string> Country::getLandBorders() { return landBorders; };

/**
* linkSea
* function that adds a country to this country's sea link list
*
* @param string id
*/
void Country::linkSea(std::string id) 
{ 
	//check if the ID is already in the list
	if (!(std::find(seaLinks.begin(), seaLinks.end(), id) != seaLinks.end()))
	{
		seaLinks.push_back(id);
	}
};

/**
* removeLinkSea
* function that removes a country from this country's sea link list
*
* @param string id
*/
void Country::removeLinkSea(std::string id)
{
	//loop through the land border list
	for (int i = 0; i < seaLinks.size(); i++)
	{
		//remove from list if id is found
		if (id == seaLinks[i])
		{
			seaLinks.erase(seaLinks.begin() + i);
			break;
		}
	}
}

/**
* getSeaLinks
* returns a vector containing the ID's of the country's sea links
*
* @return sealLinks
*/
std::vector<std::string> Country::getSeaLinks() { return seaLinks; };

/**
* linkAir
* function that adds a country to this country's air links
*
* @param string id
*/
void Country::linkAir(std::string id) 
{ 
	//check if ID is already in the list
	if (!(std::find(seaLinks.begin(), seaLinks.end(), id) != airLinks.end()))
	{
		airLinks.push_back(id);
	}
	
};

/**
* removeLinkAir
* function that removes a country from this country's air link list
*
* @param string id
*/
void Country::removeLinkAir(std::string id)
{
	//loop through the land border list
	for (int i = 0; i < airLinks.size(); i++)
	{
		//remove from list if id is found
		if (id == airLinks[i])
		{
			airLinks.erase(airLinks.begin() + i);
			break;
		}
	}
}

/**
* getAirLinks
* returns a vector containing the ID's of the country's air links
*
* @return airLinks
*/
std::vector<std::string> Country::getAirLinks() { return airLinks; };