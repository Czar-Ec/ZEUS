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
	#pragma region SETTERS AND GETTERS
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

#pragma endregion

	//get simulation variables
	unsigned long long int getHealthyPop() { return healthyPop; }
	unsigned long long int getInfectedPop() { return infectedPop; }
	unsigned long long int getDeadPop() { return deadPop; }
	unsigned long long int getZombiePop() { return zombiePop; }
	unsigned long long int getRemovedPop() { return removedPop; }

	//reset simulation variables
	void resetSimVal();

	//initial infection
	bool infected = false;

	//simulate spread
	void simulate(bool simulateZombies, int simFrame, 
		float infRate, float naturalDeathRate,
		float recoveryRate, float infDeathRate,
		float zconversionRate, float zdeathRate,
		float zremoveRate, float corpseDecayRate,
		float reanimationRate, bool allowLandInfect, bool allowSeaInfect, bool allowAirInfect,
		std::vector<Country> &countryList);

	void receiveInfection(int infectedPassengers);

	bool selectedBorder, selectedSea, selectedAir;

private:

	float getRand(float range1, float range2);


	//natural deaths
	void naturalDeaths(bool simulateZombies, float naturalDeathRate);

	//spread infection
	void spreadInfection(bool simulateZombies, float infRate, 
		float recoveryRate);

	//deaths from infection
	void deathRates(bool simulateZombies, float infDeathRate);

	//spread to other countries
	void infectCountries(bool allowLandInfect, bool allowSeaInfect, bool allowAirInfect, std::vector<Country> &countrylist);

	//zombie functions
	void zombieSpread(float zconversionRate);
	void zombieInfect();
	void zombieDecay(float zdeathRate);
	void zombieReanimation(float reanimationRate);

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

	#pragma region SIMULATOR VARIABLES

	//variables only used in the simulator
	int simulationFrame = 0;
	unsigned long long int healthyPop, infectedPop, deadPop, zombiePop, removedPop;

	std::vector<std::string> tempLandBorder, tempSeaLink, tempAirLink;

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

	resetSimVal();
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
std::vector<std::string> Country::getAirLinks() { return airLinks; }

/**
* resetSimVal
* resets the simulation values
*/
void Country::resetSimVal()
{
	healthyPop = population;
	infectedPop = 0;
	zombiePop = 0;
	deadPop = 0;
	removedPop = 0;

	tempLandBorder = landBorders;
	tempSeaLink = seaLinks;
	tempAirLink = airLinks;

	infected = false;
}

void Country::simulate(bool simulateZombies, int simFrame, float infRate, float naturalDeathRate, float recoveryRate, float infDeathRate, float zconversionRate, float zdeathRate, float zremoveRate, float corpseDecayRate, float reanimationRate, bool allowLandInfect, bool allowSeaInfect, bool allowAirInfect, std::vector<Country>& countryList)
{
	//debug
	//std::cout << id << std::endl;

	//check if it is the first frame
	if (simFrame == 0)
	{
		//if the country is set to be initially infected, set up the country to
		//have one infected individual
		if (infected)
		{
			healthyPop--;
			infectedPop = 1;
		}
		
	}

	//else proceed as normal
	else
	{
		//natural deaths occur regardless of country's infection status
		naturalDeaths(simulateZombies, naturalDeathRate);

		//infection spreads within the country
		if (infectedPop > 0)
		{
			spreadInfection(simulateZombies, infRate,
				recoveryRate);

			deathRates(simulateZombies, infDeathRate);

			//if over 5% of the population is infected, spread to other countries
			if (((float)population / (float)infectedPop) > 0.05)
			{
				infectCountries(allowLandInfect, allowSeaInfect, allowAirInfect, countryList);
			}

			//if zombies are being simulated
			if (simulateZombies && ((float)population / (float)infectedPop) > 0.3)
			{
				zombieSpread(zconversionRate);

				//if zombiePop is more than 0
				if (zombiePop > 0)
				{
					zombieDecay(zdeathRate);
					zombieReanimation(reanimationRate);
				}
			}
		}
	}
}

void Country::receiveInfection(int infectedPassengers)
{
	//country is now infected
	infected = true;

	//add the infected passengets tot he population pool
	population += infectedPassengers;

	//add the infected passengers to the infected pool
	infectedPop += infectedPassengers;
}


float Country::getRand(float range1, float range2)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = range2 - range1;
	float r = random * diff;
	return range1 + r;
}

void Country::naturalDeaths(bool simulateZombies, float naturalDeathRate)
{
	//small random chance for a random people between 0 and natural
	//death rate to die
	float deathChance = rand() % 1000000;

	if (deathChance <= 1)
	{
		//random number between 0 and the natural death rate
		float randDeathPerc = ((float) rand() / (float) naturalDeathRate) * naturalDeathRate ;

		
		//check if the healthy pop if the death will not give negative values
		int populationToRemove = healthyPop * getRand(0, naturalDeathRate / 100);

		//prevents small populations from not dying out
		if (populationToRemove == 0)
		{
			populationToRemove = 1;
		}
		if (populationToRemove > 10000)
		{
			populationToRemove /= 100;
		}
		if (populationToRemove > 100000)
		{
			populationToRemove /= 1000;
		}
		if (populationToRemove > 1000000)
		{
			populationToRemove /= 10000;
		}

		//if simulating zombies, the individuals are removed
		//otherwise they are just dead
		if (simulateZombies)
		{
			//check if the population to remove does not exceed the healthy pop
			if (populationToRemove >= healthyPop)
			{
				removedPop += healthyPop;
				healthyPop = 0;
			}
			else
			{
				healthyPop -= populationToRemove;
				removedPop += populationToRemove;
			}
		}
		else
		{
			//converts removed and zombies to dead should the user change
			//the option mid simulation
			if (zombiePop > 0)
			{
				deadPop += zombiePop;
				zombiePop = 0;
			}
			if (removedPop > 0)
			{
				deadPop += removedPop;
				removedPop = 0;
			}

			if (populationToRemove >= healthyPop)
			{
				deadPop += healthyPop;
				healthyPop = 0;
			}
			else
			{
				healthyPop -= populationToRemove;
				deadPop += populationToRemove;
			}
		}
	}


}

void Country::spreadInfection(bool simulateZombies, float infRate, float recoveryRate)
{
	/*random value between 0 and the infRate, spread is calculated by 
	new infected num = 
	((rand[0 - infRate] * current infected num) + current infected num)
	
	recovery rate only kicks in after 0.01% of the total pop is infected and
	is subtracted from the above calculation

	death rate also subtracts from the new infected and will be added to the dead group
	regardless of whether or not this is a zombie sim
	*/

	float randChance = rand() % 200;

	//random chances of spreading
	if (randChance <= 1)
	{
		//new infections
		float randInfRate = getRand(0, infRate / 100);

		int newInfectedCount = 0;

		newInfectedCount = infectedPop * randInfRate;
		//std::cout << "test\n";
		//limiting infected count
		if (newInfectedCount == 0) { newInfectedCount = 1; }
		/*if (newInfectedCount > 10000) { newInfectedCount /= 10; }
		if (newInfectedCount > 100000) { newInfectedCount /= 100; }
		if (newInfectedCount > 1000000) { newInfectedCount /= 1000; }*/

		//std::cout << (float)infectedPop / (float)population << std::endl;

		//recoveries and deaths after 1% of population is infected
		if (((float)infectedPop / (float)population) > 0.0001)
		{
			float randRecoveryRate = getRand(0, recoveryRate / 100);
			newInfectedCount -= (infectedPop * randRecoveryRate);
		}

		//ensures that the infected does not exceed the healthyPop
		if (newInfectedCount >= healthyPop)
		{
			infectedPop += healthyPop;
			healthyPop = 0;
		}
		else if (newInfectedCount < 0)
		{
			healthyPop += newInfectedCount;
			infectedPop -= newInfectedCount;
		}
		else
		{
			infectedPop += newInfectedCount;
			healthyPop -= newInfectedCount;
		}		
	}

	
	
}

void Country::deathRates(bool simulateZombies, float infDeathRate)
{
	float randChance = rand() % 200;

	if (randChance <= 1)
	{
		float randDeathRate = getRand(0, infDeathRate / 100);

		int deathRate = 0;
		deathRate = deadPop * randDeathRate;

		if (deathRate == 0) { deathRate = 1; }

		if (((float)infectedPop / (float)population) > 0.005)
		{
			if (deathRate >= infectedPop)
			{
				deadPop += infectedPop;
				infectedPop = 0;
			}
			else
			{
				deadPop += deathRate;
				infectedPop -= deathRate;
			}
		}
	}
}

void Country::infectCountries(bool allowLandInfect, bool allowSeaInfect, bool allowAirInfect, std::vector<Country> &countryList)
{
	//small chance to infect another country
	float randChance = rand() % 500;

	if (randChance <= 1 && ((float)population / (float)infectedPop) > 0.2)
	{
		//booleans to see if another country was infected
		bool infectionHasSpread = false;

		//check if spreading by land is possible
		//additional randomisation
		float randLand = rand() % 100;
		if (allowLandInfect && !infectionHasSpread && randLand <= 10)
		{
			//only loop if there are land borders
			while (tempLandBorder.size() > 0 && !infectionHasSpread)
			{
				//shuffle the land border
				std::random_shuffle(tempLandBorder.begin(), tempLandBorder.end());

				//check if the country is already infected
				//if not, infect it and remove from the list
				for (int i = 0; i < countryList.size(); i++)
				{
					//compare IDs
					if (tempLandBorder.back() == countryList[i].getID())
					{
						//infect the country
						int randAmountPeople = 1;
						population -= randAmountPeople;
						infectedPop -= randAmountPeople;
						countryList[i].receiveInfection(randAmountPeople);
						infectionHasSpread = true;
					}
				}
			}
		}

		//check if spreading via sea is possible
		//additional randomisation
		float randSea = rand() % 100;
		if (allowSeaInfect && !infectionHasSpread && randSea <= 1)
		{
			//only loop if there are sea links
			while (tempSeaLink.size() > 0 && !infectionHasSpread)
			{
				//shuffle sea links
				std::random_shuffle(tempSeaLink.begin(), tempSeaLink.end());

				for (int i = 0; i < countryList.size(); i++)
				{
					//compare ID
					if (tempSeaLink.back() == countryList[i].getID())
					{
						//infect the country
						int randAmountPeople = 1;
						population -= randAmountPeople;
						infectedPop -= randAmountPeople;
						countryList[i].receiveInfection(randAmountPeople);
						infectionHasSpread = true;
					}
				}
			}
		}

		//check if spreading via air is possible
		//no additional spread

		if (allowAirInfect && !infectionHasSpread)
		{
			//only loop if there are air links
			while (tempAirLink.size() > 0 && !infectionHasSpread)
			{
				//shuffle air links
				std::random_shuffle(tempAirLink.begin(), tempAirLink.end());

				for (int i = 0; i < countryList.size(); i++)
				{
					//compare ID
					if (tempAirLink.back() == countryList[i].getID())
					{
						//infect the country
						int randAmountPeople = 1;
						population -= randAmountPeople;
						infectedPop -= randAmountPeople;
						countryList[i].receiveInfection(randAmountPeople);
						infectionHasSpread = true;
					}
				}
			}
		}
	}
}

void Country::zombieSpread(float zconversionRate)
{
	//random chances for infected to turn into zombies
	float randChance = rand() % 250;

	if (randChance <= 1 && infectedPop >= 250)
	{
		//random conversion rate
		float randConvRate = getRand(0, zconversionRate / 100);

		int zombieCount = 0;
		zombieCount = infectedPop * randConvRate;

		if (zombieCount == 0) { zombieCount = 1; }

		//ensures that the zombies does not exceed the infectedPop
		if (zombieCount >= infectedPop)
		{
			zombiePop += infectedPop;
			infectedPop = 0;
		}
		else if (zombieCount < 0)
		{
			zombiePop += zombieCount;
			infectedPop -= zombieCount;
		}
		else
		{
			zombiePop += zombieCount;
			infectedPop -= zombieCount;
		}
	}
}

void Country::zombieInfect()
{
	float randChance = rand() % 200;

	if (randChance <= 1)
	{
		float randInfect = getRand(0, 100);
		float zombieCount = 0;
		zombieCount = randInfect * healthyPop;

		if (zombieCount == 0) { zombieCount = 1; }

		//ensures that the infected does not exceed the healthyPop
		if (zombieCount >= healthyPop)
		{
			infectedPop += healthyPop;
			healthyPop = 0;
		}
		else if (zombieCount < 0)
		{
			healthyPop += zombieCount;
			infectedPop -= zombieCount;
		}
		else
		{
			infectedPop += zombieCount;
			healthyPop -= zombieCount;
		}
	}
}

inline void Country::zombieDecay(float zdeathRate)
{
	//random chance
	float randChance = rand() % 400;
	if (randChance <= 1)
	{
		//random amount of zombies
		int randAmount = rand() % 1000;

		randAmount *= zdeathRate;

		if (randAmount >= zombiePop)
		{
			removedPop += zombiePop;
			zombiePop = 0;
		}
		else
		{
			removedPop += randAmount;
			zombiePop -= randAmount;
		}
	}
}

void Country::zombieReanimation(float reanimationRate)
{
	//random chance
	float randChance = rand() % 400;
	if (randChance <= 1)
	{
		//random amount of zombies
		int randAmount = rand() % 1000;

		randAmount *= reanimationRate;

		if (randAmount >= deadPop)
		{
			zombiePop += deadPop;
			deadPop = 0;
		}
		else
		{
			zombiePop += randAmount;
			deadPop -= randAmount;
		}
	}
}

