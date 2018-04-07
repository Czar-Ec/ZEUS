#pragma once

#include "Country.h"

//for regex checking
#include <regex>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

/**
* Data Handler
* class that holds the saving and loading functions which are used 
* between both the scenario creator and the main simulator
*/
class DataHandler
{
	public:
		DataHandler();
		DataHandler(std::string filepath);

		////////////////////////////////////////////////////////////////////////////////////
		/**
		* SCENARIO
		*/
		////////////////////////////////////////////////////////////////////////////////////
		void loadScenario();
		void resetAll();

		//getters
		std::string getSceName();
		std::string getTexturePath();
		std::vector<Country> getCountryList();
		int getCountryCount();
		unsigned long long int getTotalPop();


	private:

		char filepath[MAX_PATH];

		//typecheck values
		const int
			CHECK_COUNTRY_CODE = 0;


		//regex checker to validate values
		bool regexCheck(std::string toCheck, int typeCheck);


		//scenario variables
		std::string loadSceName, scenarioTexturePath;
		std::vector<Country> countryList;
		int countryCount;
		unsigned long long int totalPop;

};

/**
* DataHandler default constructor
*/
DataHandler::DataHandler() {}

/**
* DataHandler constructor
* constructor for when the data handler should load a file
*/
DataHandler::DataHandler(std::string _filepath)
{
	strcpy(filepath, _filepath.c_str());
}

void DataHandler::loadScenario()
{
	resetAll();

	//open the file
	std::ifstream file;
	file.open(filepath);

	//line buffer
	std::string lineBuf;

	//check if the file can be opened
	if (file.is_open())
	{
		//clear the country list
		countryList.clear();

		//stringstream to parse the line
		std::stringstream ss;
		ss.str(lineBuf);

		//processed line
		std::string proc;

		//comment prefix
		std::string prefix("//");

		//keep count of which line is being read
		int count = 0;

		//count the number of countries loaded
		countryCount = 0;
		//count the total population
		totalPop = 0;

		//read the file line by line
		while (file >> lineBuf)
		{
			//debug
			//std::cout << lineBuf << "\n";

			//country links
			std::vector<std::string> cLandLinks, cSeaLinks, cAirLinks;

			//only handle non empty lines and non commented lines
			if (lineBuf != "" && lineBuf.compare(0, prefix.size(), prefix))
			{
				//first line should be the scenario name
				if (count == 0) { loadSceName = lineBuf; }

				//second should be the texture path
				if (count == 1) { scenarioTexturePath = lineBuf; }

				//everything else should be a country
				else
				{
					//keep track of which variable is being scanned
					int scanPos = 0;

					//temporarily hold data
					std::string cData[14];

					//stringstream to parse the line
					std::stringstream ls;
					ls.str(lineBuf);

					//go through the line
					while (std::getline(ls, proc, '|'))
					{
						//debug
						//std::cout << scanPos << " " << proc << "\n";

						//add data to relevant position
						cData[scanPos] = proc;

						//handle land borders
						if (scanPos == 11)
						{
							//parse land borders
							std::stringstream land;
							land.str(cData[11]);

							//string buffer
							std::string lBuf;

							//go through the land borders
							while (std::getline(land, lBuf, ','))
							{
								//debug
								//std::cout << "buffer: " << lBuf << "\n";
								cLandLinks.push_back(lBuf);
							}
						}

						//handle sea links
						if (scanPos == 12)
						{
							//parse sea links
							std::stringstream sea;
							sea.str(cData[12]);

							//string buffer
							std::string sBuf;

							while (std::getline(sea, sBuf, ','))
							{
								//std::cout << "buffer: " << sea << std::endl;
								cSeaLinks.push_back(sBuf);
							}
						}
							
						//handle air links then make the country
						if (scanPos == 13)
						{
							//apsring land borders
							std::stringstream air;
							air.str(cData[13]);

							//string buffer
							std::string aBuf;

							//loop through air links
							while(std::getline(air, aBuf, ','))
							{
								//std::cout << "buffer: " << air << std::endl;
								cAirLinks.push_back(aBuf);
							}

							//empty vector
							std::vector<std::string> emptyVec;

							//country colours
							int rCol = atoi(cData[2].c_str());
							int gCol = atoi(cData[3].c_str());
							int bCol = atoi(cData[4].c_str());

							//convert population to unsigned long long
							unsigned long long int cPop = strtoull(cData[5].c_str(), (char**)NULL, 10);
							//country gdp
							unsigned long long int gdp = strtoull(cData[6].c_str(), (char**)NULL, 10);
							//military budget
							unsigned long long int mb = strtoull(cData[7].c_str(), (char**)NULL, 10);
							//research budget
							unsigned long long int rb = strtoull(cData[8].c_str(), (char**)NULL, 10);

							//climate types
							int climTemp = atoi(cData[9].c_str());
							int climHum = atoi(cData[10].c_str());

							//applying empty vectors to countries without borders
							if (cLandLinks.size() == 0)
							{
								cLandLinks = emptyVec;
							}
							if (cSeaLinks.size() == 0)
							{
								cSeaLinks = emptyVec;
							}
							if (cAirLinks.size() == 0)
							{
								cAirLinks = emptyVec;
							}

							//make the country
							Country c = Country(
								cData[0], //id
								cData[1], //country name
								rCol, //red
								gCol, //green
								bCol, //blue
								cPop, //country population
								gdp, //country gdp
								mb, //military budget
								rb, //research budget
								climTemp, //temperature
								climHum, //humidity
								cLandLinks, //land borders
								cSeaLinks, //sea links
								cAirLinks //air links
							);

							/*std::cout <<
							c.getID() << std::endl <<
							c.getCountryName() << std::endl <<
							(int)c.getColour().r << std::endl <<
							(int)c.getColour().g << std::endl <<
							(int)c.getColour().b << std::endl <<
							c.getPopulation() << std::endl <<
							c.getGDP() << std::endl <<
							c.getMilitaryBudget() << std::endl <<
							c.getResearchBudget() << std::endl <<
							c.getTemperature() << std::endl << std::endl;*/

							for (int i = 0; i < cLandLinks.size(); i++)
							{
								//std::cout << cLandLinks[i] << std::endl;
							}

							countryList.push_back(c);

							countryCount++;
							totalPop += cPop;

							//clear the vectors
							cLandLinks.clear();
							cSeaLinks.clear();
							cAirLinks.clear();

							//std::cout << "\n\n\n\n" << std::endl;

							scanPos = 0;
						}

						//update scan position
						scanPos++;
					}
				}

				//increase country count
				count++;
			}
			
				
		}
	}
	else
	{
		//error printing
		std::cout << "Error: File could not be opened\n";
	}

	file.close();
}

inline void DataHandler::resetAll()
{
	loadSceName = "";
	scenarioTexturePath = "";
	countryList.clear();
	countryCount = 0;
	totalPop = 0;
}

inline std::string DataHandler::getSceName()
{
	return loadSceName;
}

inline std::string DataHandler::getTexturePath()
{
	return scenarioTexturePath;
}

inline std::vector<Country> DataHandler::getCountryList()
{
	return countryList;
}

inline int DataHandler::getCountryCount()
{
	return countryCount;
}

inline unsigned long long int DataHandler::getTotalPop()
{
	return totalPop;
}

inline bool DataHandler::regexCheck(std::string toCheck, int typeCheck)
{
	bool valid = false;

	switch (typeCheck)
	{
		case 0:	
		{
			//country code should be maximum of 4 capital characters
			std::regex countryRegex("[A-Z0-9]{4}");
			if (std::regex_match(toCheck, countryRegex))
			{
				valid = true;
			}
			break;
		}

		default:
			std::cout << "Invalid type check\n";
			return false;
			break;
	}


	return valid;
}
