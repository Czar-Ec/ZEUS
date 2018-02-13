#pragma once

//need to sort out dependency on windows sdk
//C:\Program Files (x86)\Windows Kits\10\Lib\10.0.15063.0\um\x86 for opengl32.lib
//C:\Program Files (x86)\Windows Kits\10\Include\10.0.15063.0\um for include files glu.h and gl.h

//IMGUI
#include "../sharedobjects/imgui.h"
#include "../sharedobjects/imgui_impl_sdl.h"
#include "../sharedobjects/imgui_impl_sdl.h"
#include "../sharedobjects/stb_rect_pack.h"
#include "../sharedobjects/stb_textedit.h"
#include "../sharedobjects/stb_truetype.h"

//SDL libraries
#define SDL_STATIC
#include <SDL\SDL.h>
#include <SDL\SDL_main.h>
#include <SDL\SDL_ttf.h>
#include <SDL\SDL_opengl.h>
#include <SDL\SDL_image.h>

//C/C++ libraries
//basic IO
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <string>
#include <algorithm>

//Visual C++ library
#include "Windows.h"

//other classes
#include "../sharedobjects/Country.h"
#include "../sharedobjects/DataHandler.h"
#include "../sharedobjects/UX.h"

/**
* GUI Class
* the class which handles the imgui actions and will be drawing and handling the actions on the scren
*/
static class SCGUI
{
public:
	//default constructor and destructor
	SCGUI();
	~SCGUI();
	//main constructor
	SCGUI(SDL_Renderer *renderer, int winX, int winY);

	//main menu bar
	void menuBar(SDL_Renderer *renderer, bool &appRun);

	//file handling
	void open(SDL_Renderer *renderer);
	bool loadScenario(std::string filePath, SDL_Renderer *renderer);
	void save();
	void saveAs();
	void saveFile(std::string filepath);
	
	//view country window
	void viewCountries();

	//new scenario window
	void newScenarioWin(SDL_Renderer *renderer);
	void resetNewScenario();

	//add new country window
	void newCountryMenu(int r, int g, int b);
	void resetNewCountry();

	//edit country window
	void editCountryMenu();

	//gui rendering
	void render(SDL_Window *window, SDL_Renderer *renderer);

	//tools
	bool doesCountryExist(std::string id);

	//ease of access
	void eyedropTool();

	//Control functions
	void zoom(int zoomType);	//function to allow zooming
	void pan(SDL_Point *mPos, int motionX, int motionY);	//function to allow panning of the map
	void panLimiting();	//ensures the pan is limited within the relevant zone of the texture

	void mouseOver();	//mouse over helps identify a country of where there could be one
	void leftClick();

	//shortcut controls
	void ctrlS() { save(); };

private:
	//colour of the background
	ImVec4 bkgColour = ImColor(0,0,44);

	bool newScenario = false;
	bool openScenario = false;
	bool addNewCountry = false;
	bool editCountry = false;
	bool viewCountriesWin = false;

	int clickR = -1, clickG = -1, clickB = -1;

	//map to be shown on screen
	SDL_Texture *map = NULL;
	char textureLoc[MAX_PATH];

	//region where the map will be drawn
	int worldX, worldY;
	SDL_Rect vp;
	//rectangle which allows for zooming and panning
	SDL_Rect vpSrc;

	#pragma region SAVING AND LOADING
	//////////////////////////////////////////////////////////////////////////////////
	char curFileName[MAX_PATH] = "";


	//////////////////////////////////////////////////////////////////////////////////
	#pragma endregion

	#pragma region CONTROL VARIABLES
	//////////////////////////////////////////////////////////////////////////////////
	int wMapX, wMapY;
	
	float zoomVal = 1,
		maxZoom = 1,
		minZoom = 0.1,
		zoomInterval = 0.025;

	//mouse over variables
	std::vector<std::string> emptyVec;
	SDL_Color curCol = { 0, 0, 0 };
	Country scrollCountry = Country("None", "None", 0, 0, 0, 0, 0, 0, 0, -1, -1, emptyVec, emptyVec, emptyVec);
	bool newCountryOnClick = false;

	//////////////////////////////////////////////////////////////////////////////////
	#pragma endregion

	#pragma region SCENARIO GLOBAL VARIABLES
	//////////////////////////////////////////////////////////////////////////////////
	//scenario name
	char scenarioName[30] = "";
	//file path for the scenario map
	char scenarioPath[MAX_PATH] = "";
	char imgFilePath[MAX_PATH] = "";
	std::string imgType = "";
	int totalCountries = 0, worldPopulation = 0;

	//loaded scenario
	bool scenarioLoaded = false;
	char curScenario[30];

	/////////////////////
	//TEMPORARY VARIABLES
	/////////////////////
	//temporary variables, will be pushed into global after pressing create simulation
	char tempName[30] = "";
	char tempMapFilePath[MAX_PATH] = "";
	std::string tempImgType = "";

	//booleans for error validation
	bool acceptScenarioName = false;
	bool acceptImgPath = false;
	bool existingImgPath = false;
	bool validType = false;

	//////////////////////////////////////////////////////////////////////////////////
	#pragma endregion

	#pragma region VIEW COUNTRIES
	//////////////////////////////////////////////////////////////////////////////////
	int currentCountry = -1;

	char editID[5] = "";
	char editCName[31] = "";
	int editR = 0,
		editG = 0,
		editB = 0;


	//active eye dropper
	bool editEyeDropperActive = false;

	//country's population
	char editPop[15] = "";
	unsigned long long int editPopInt;

	//country GDP
	char editGDP[15] = "";
	unsigned long long int editGDPInt;

	//country military budget
	char editMilitaryBudget[15] = "";
	unsigned long long int editMBInt;

	//country research spending
	char editResearchSpending[15] = "";
	unsigned long long int editRSInt;

	//climate booleans
	bool
		//temperatures
		ehotTemp = false,
		ecoldTemp = false,
		eneutralTemp = true,

		//humidity
		ewetHum = false,
		edryHum = false,
		eneutralHum = true;

	//country borders
	std::vector<std::string> elandBorders;

	//air and ocean links
	std::vector<std::string> eairLinks;
	std::vector<std::string> eseaLinks;


	//////////////////////////////////////////////////////////////////////////////////
	#pragma endregion

	#pragma region NEW COUNTRY VARIABLES
	//////////////////////////////////////////////////////////////////////////////////
	//temporary variables which hold country information
	char tempID[5] = "";
	char tempCName[31] = "";
	int tempR = 0,
		tempG = 0,
		tempB = 0;


	//active eye dropper
	bool eyedropperActive = false;

	//country's population
	char tempPop[15] = "";
	unsigned long long int tempPopInt;

	//country GDP
	char tempGDP[15] = "";
	unsigned long long int tempGDPInt;

	//country military budget
	char tempMilitaryBudget[15] = "";
	unsigned long long int tempMBInt;

	//country research spending
	char tempResearchSpending[15] = "";
	unsigned long long int tempRSInt;

	//climate booleans
	bool
		//temperatures
		hotTemp = false,
		coldTemp = false,
		neutralTemp = true,

		//humidity
		wetHum = false,
		dryHum = false,
		neutralHum = true;

	//country borders
	std::vector<std::string> tempLandBorders;

	//air and ocean links
	std::vector<std::string> tempAirLinks;
	std::vector<std::string> tempSeaLinks;

	//error checking
	std::string errID, errName;
	bool acceptNewCID, isNewCIDunique, acceptNewCName;

	//////////////////////////////////////////////////////////////////////////////////
	#pragma endregion

	#pragma region COUNTRY VARIABLES
	//////////////////////////////////////////////////////////////////////////////////
	//list of countries
	std::vector<Country> countryList;

	//current chosen country
	Country curCountry = Country();

	SDL_Color scrollCol;
	bool nonExistentCountry = true; //variable to know if the country being scrolled over is unknown therefore can make a new country
	//////////////////////////////////////////////////////////////////////////////////
	#pragma endregion
};

/**
* GUI default constructor
* empty constructor, meant to be used temporarily
*/
SCGUI::SCGUI()
{

}

/**
* GUI destructor
* destructor called when a class is to be destroyed
*/
SCGUI::~SCGUI()
{

}

/**
* GUI constructor
* constructor which properly sets up the simulator GUI
*
* @param SDL_Renderer *renderer
* @param int winX
* @param int winY
*/
SCGUI::SCGUI(SDL_Renderer *renderer, int winX, int winY)
{
	scrollCol.r = 0;
	scrollCol.g = 0;
	scrollCol.b = 0;

	worldX = winX;
	worldY = winY;

	//set draw region
	vp = { 0, 20, winX, winY - 20 };
}

/**
* menuBar
* function that displays and makes the menu bar work
*
* @param SDL_Renderer *renderer
* @param bool &appRun (the boolean that tells the main loop when to end the program)
*/
void SCGUI::menuBar(SDL_Renderer *renderer, bool &appRun)
{
	//menu bar
	ImGui::BeginMainMenuBar();
	//File
	if (ImGui::BeginMenu("File"))
	{
		//Make a new simulation
		if (ImGui::MenuItem("New Scenario", "CTRL+N"))
		{
			newScenario = true;
		}

		//Open existing simulation
		if (ImGui::MenuItem("Open Scenario", "CTRL+O"))
		{
			openScenario = true;
		}

		//Save current simulation
		if (ImGui::MenuItem("Save", "CTRL+S"))
		{
			save();
		}

		//Save current simulation with a different name

		if (ImGui::MenuItem("Save As"))
		{
			saveAs();
		}


		ImGui::Separator();
		if (ImGui::BeginMenu("Recent Files"))
		{
			// iterate items..
			// eg if (ImGui::Item("&1. filename.txt")) {}
			ImGui::EndMenu();
		}
		ImGui::Separator();
		ImGui::EndMenu();
	}

	//View
	if (ImGui::BeginMenu("View"))
	{

		//view existing countries option
		if (ImGui::MenuItem("View all countries"))
		{
			if (scenarioLoaded)
			{
				viewCountriesWin = true;

				//sort the country list alphabetically
				//std::sort(countryList.begin(), countryList.end());
			}
		}

		//add new country option
		if (ImGui::MenuItem("Add new country"))
		{
			if (scenarioLoaded)
			{
				addNewCountry = true;
				clickR = clickG = clickB = -1;
			}
		}




		ImGui::EndMenu();
	}

	//Help
	if (ImGui::BeginMenu("Help"))
	{
		//open the online manual
		if (ImGui::MenuItem("Online Manual"))
		{
			ShellExecute(NULL, NULL, "https://zeusczarec.weebly.com", NULL, NULL, SW_SHOWNORMAL);
		}

		//open the local manual
		if (ImGui::MenuItem("Local Manual"))
		{

		}

		ImGui::EndMenu();
	}

	//allows user to exit the app via the main menu
	if (ImGui::BeginMenu("Quit"))
	{
		ImGui::Separator();
		if (ImGui::MenuItem("Close Application"))
		{
			appRun = false;
		}
		ImGui::Separator();
		ImGui::EndMenu();
	}

	//end of main menu bar
	ImGui::EndMainMenuBar();

	//components of main menu bar
	

	if (newScenario)
	{
		newScenarioWin(renderer);
	}

	if (openScenario)
	{
		open(renderer);
	}

	if (viewCountriesWin)
	{
		viewCountries();
	}

	if (addNewCountry)
	{
		newCountryMenu(clickR, clickG, clickB);
	}

	if (editCountry)
	{
		editCountryMenu();
	}
}

void SCGUI::open(SDL_Renderer *renderer)
{	
	char filename[MAX_PATH];
	OPENFILENAME ofn;
	ZeroMemory(&filename, sizeof(filename));
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;  // If you have a window to center over, put its HANDLE here
	ofn.lpstrFilter = "ZEUS Scenario Files (*.sce)\0"
		"*.sce\0";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = "Open Scenario";
	ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

	if (GetOpenFileName(&ofn))
	{
		strcpy(scenarioPath, filename);
		//std::cout << tempMapFilePath << "\n";
	}
	
	//check if file is valid
	FILE *fp = fopen(scenarioPath, "r");
	if (fp != NULL)
	{
		DataHandler d = DataHandler(scenarioPath);
		d.loadScenario();
			
		//image file path
		strcpy(textureLoc, d.getTexturePath().c_str());

		//load the texture
		if (textureLoc != "")
		{
			SDL_Surface *surf = IMG_Load(d.getTexturePath().c_str());
			map = SDL_CreateTextureFromSurface(renderer, surf);


			if (map != NULL)
			{
				SDL_RenderCopy(renderer, map, NULL, NULL);//get texture size
				SDL_QueryTexture(map, NULL, NULL, &wMapX, &wMapY);
				vpSrc = { 0, 0, wMapX, wMapY };

				//set scenario values
				//scenario name
				strcpy(scenarioName, d.getSceName().c_str());
					
				//countryList
				countryList = d.getCountryList();

				openScenario = false;
				scenarioLoaded = true;
			}
			else
			{
				std::cout << map << " " << IMG_GetError() << "\n";
				std::cout << map << " " << SDL_GetError() << "\n";
			}

			SDL_FreeSurface(surf);
			surf = NULL;
		}
			
	}
	else
	{
		//otherwise the file does not exist
		std::cout << "Error: File not found\n";
	}
}

bool SCGUI::loadScenario(std::string filePath, SDL_Renderer *renderer)
{
	bool loaded = false;

	//load the scenario
	DataHandler d = DataHandler(filePath);
	d.loadScenario();

	//debug
	std::cout << d.getSceName() << " " << d.getTexturePath() << "\n";

	//load the map texture
	//SDL_Surface *worldSurf = IMG_Load(d.getTexturePath().c_str());
	SDL_Surface *worldSurf = IMG_Load(d.getTexturePath().c_str());
	map = SDL_CreateTextureFromSurface(renderer, worldSurf);
	//finished with the surface
	SDL_FreeSurface(worldSurf);

	//check if the texture is loaded
	if (map != NULL)
	{
		//reset world X and Y
		worldX = worldY = 0;

		//get texture size
		SDL_QueryTexture(map, NULL, NULL, &wMapX, &wMapY);
		vpSrc = { 0, 0, wMapX, wMapY };

		//set global scenario values
		strcpy(scenarioName, d.getSceName().c_str());
		countryList = d.getCountryList();
		totalCountries = d.getCountryCount();
		worldPopulation = d.getTotalPop();

		loaded = true;
	}
	else
	{
		//warn about the map not being loaded
		std::cerr << "World Map not found!\n" << IMG_GetError() << std::endl;
	}

	return loaded;
}

/**
* save
* function called when the save option is used. The function checks
* if the scenario was loaded or newly created and either calls save as or
* writes over the existing scenario
*/
void SCGUI::save()
{
	if (scenarioLoaded)
	{
		//check if this file was opened or was newly created
		if (curFileName == "")
		{
			//call the save as function
			saveAs();
		}
		//else save it as the cur file name
		else
		{
			saveFile(curFileName);
		}
	}
	
}

/**
* saveAs
* function called when the saveAs option is used. The function is also called when
* save function determines that the scenario is new and requires a filepath for the scenario
*/
void SCGUI::saveAs()
{
	if (scenarioLoaded)
	{
		char filename[MAX_PATH];
		OPENFILENAME ofn;
		ZeroMemory(&filename, sizeof(filename));
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;  // If you have a window to center over, put its HANDLE here
		ofn.lpstrFilter = "ZEUS Scenario Files (*.sce)\0*.sce\0";
		ofn.lpstrFile = filename;
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrTitle = "Save Scenario";
		ofn.Flags = OFN_DONTADDTORECENT | OFN_NOCHANGEDIR;

		if (GetSaveFileNameA(&ofn))
		{
			saveFile(filename);
		}
	}
	
}

/**
* saveFile
* function that actually writes the file
*
* @param string filepath
*/
void SCGUI::saveFile(std::string filepath)
{
	//check if the .sim extension is already added, if not add it
	if (!(filepath.substr(filepath.find_last_of(".") + 1) == "sce"))
	{
		filepath = filepath + ".sce";
	}

	std::ofstream file(filepath);

	//check if file is valid
	if (!file.is_open())
	{
		std::cout << "Error while saving, file could not be opened\n";
	}
	else
	{
		//first line is always the scenario name
		file << scenarioName << "\n";

		//second line will be the map's image/texture
		file << textureLoc << "\n";

		//the following lines will be the country data
		for (int i = 0; i < countryList.size(); i++)
		{
			//everything is on the same line
			file << countryList[i].getID() << "|" <<
				countryList[i].getCountryName() << "|" <<
				(int)countryList[i].getColour().r << "|" <<
				(int)countryList[i].getColour().g << "|" <<
				(int)countryList[i].getColour().b << "|" <<
				countryList[i].getPopulation() << "|" <<
				countryList[i].getGDP() << "|" <<
				countryList[i].getMilitaryBudget() << "|" <<
				countryList[i].getResearchBudget() << "|" <<
				countryList[i].getTemperature() << "|" <<
				countryList[i].getHumidity() << "|";

			//borders will need to have its own loops as well, each border is separated by commas
			std::vector<std::string> lBorder = countryList[i].getLandBorders();
			std::vector<std::string> sLink = countryList[i].getSeaLinks();
			std::vector<std::string> aLink = countryList[i].getAirLinks();

			//land border
			for (int borderScan = 0; borderScan < lBorder.size(); borderScan++)
			{
				file << lBorder[borderScan];

				//add a comma after each one except for the last one
				if (!borderScan == lBorder.size()-1)
				{
					file << ",";
				}
			}

			//add a separator to indicate the next border
			file << "|";

			//sea links
			for (int seaScan = 0; seaScan < sLink.size(); seaScan++)
			{
				file << sLink[seaScan];

				//add a comma after each one except for the last one
				if (!seaScan == sLink.size()-1)
				{
					file << ",";
				}
			}

			//add a separator to indicate the next border
			file << "|";

			for (int airScan = 0; airScan < aLink.size(); airScan++)
			{
				file << aLink[airScan];

				//add a comma after each one except for the last one
				if (!airScan == aLink.size()-1)
				{
					file << ",";
				}
			}

			//finish the country by adding a new line
			file << "|\n";
		}
	}

	file.close();

	//this file is now this filepath
	strcpy(curFileName, filepath.c_str());
}

/**
* viewCountries
* function that displays a list of all the countries the scenario contains.
* The function is also a way to access the edit menu by editing a specific country
*/
void SCGUI::viewCountries()
{
	//make the window
	ImGui::Begin("View Country", &viewCountriesWin, ImGuiWindowFlags_NoCollapse);
	ImGui::SetWindowSize(ImVec2(750, 500));
	ImGui::BeginColumns("View Countries", 4, NULL);

	//column titles
	ImGui::Text("Country ID");
	ImGui::NextColumn();

	ImGui::Text("Country Name");
	ImGui::NextColumn();

	helpMarker("Press View to edit/view the country data");
	ImGui::NextColumn();

	helpMarker("Press Remove to delete the country from the list. Action cannot be undone");
	ImGui::NextColumn();

	//add all information from the country list
	for (int count = 0; count < countryList.size(); count++)
	{
		//show the ID in the first column
		ImGui::Text(countryList[count].getID().c_str());
		ImGui::NextColumn();

		//show country name
		ImGui::Text(countryList[count].getCountryName().c_str());
		ImGui::NextColumn();

		std::string viewButtonText = "View " + countryList[count].getID();
		//view button
		if (ImGui::Button(viewButtonText.c_str()))
		{
			currentCountry = count;

			//set edit ID
			strcpy(editID, countryList[count].getID().c_str());

			//set edit name
			strcpy(editCName, countryList[count].getCountryName().c_str());

			//set region colours
			SDL_Color colour = countryList[count].getColour();
			editR = colour.r;
			editG = colour.g;
			editB = colour.b;

			//set population
			strcpy(editPop, std::to_string(countryList[count].getPopulation()).c_str());

			//set gdp
			strcpy(editGDP, std::to_string(countryList[count].getGDP()).c_str());

			//set military budget
			strcpy(editMilitaryBudget, std::to_string(countryList[count].getMilitaryBudget()).c_str());

			//set research budget
			strcpy(editResearchSpending, std::to_string(countryList[count].getResearchBudget()).c_str());

			int temp = countryList[count].getTemperature();
			eneutralTemp = ehotTemp = ecoldTemp = false;
			int hum = countryList[count].getHumidity();
			eneutralHum = ewetHum = edryHum = false;

			//setting correct settings for temperature
			switch (temp)
			{
				case 0:
					eneutralTemp = true;
					break;

				case 1:
					ehotTemp = true;
					break;

				case 2:
					ecoldTemp = true;
					break;

				default:
					break;
			}

			//setting correct settings for humidity
			switch (hum)
			{
			case 0:
				eneutralHum = true;
				break;

			case 1:
				ewetHum = true;
				break;

			case 2:
				edryHum = true;
				break;

			default:
				break;
			}

			//set land air and sea borders equal to the temps
			tempLandBorders = countryList[count].getLandBorders();
			tempSeaLinks = countryList[count].getSeaLinks();
			tempAirLinks = countryList[count].getAirLinks();

			//load land, air and sea borders
			for (int scan = 0; scan < countryList.size(); scan++)
			{
				//check for land borders
				for (int landScan = 0; landScan < tempLandBorders.size(); landScan++)
				{
					//if ID's match then set selected for land and then break loop
					if (tempLandBorders[landScan] == countryList[scan].getID())
					{
						countryList[scan].selectedBorder = true;
						break;
					}
				}

				//doing the same for air and sea
				for (int seaScan = 0; seaScan < tempSeaLinks.size(); seaScan++)
				{
					if (tempSeaLinks[seaScan] == countryList[scan].getID())
					{
						countryList[scan].selectedSea = true;
						break;
					}
				}

				for (int airScan = 0; airScan < tempAirLinks.size(); airScan++)
				{
					if (tempAirLinks[airScan] == countryList[scan].getID())
					{
						countryList[scan].selectedAir = true;
						break;
					}
				}
			}

			//opens the edit menu
			editCountry ^= 1;
		}
		ImGui::NextColumn();

		std::string removeButtonText = "Remove " + countryList[count].getID();
		//remove button
		if (ImGui::Button(removeButtonText.c_str()))
		{
			countryList.erase(countryList.begin() + count);
		}
		ImGui::NextColumn();
	}

	ImGui::EndColumns();
	ImGui::End();
}

/**
* newScenarioWin
* function that displays the new scenario menu when called.
* The function also sets the map texture which will be used for the scenario
*
* @param SDL_Renderer *renderer
*/
void SCGUI::newScenarioWin(SDL_Renderer *renderer)
{
	//make the window
	ImGui::Begin("New Scenario", &newScenario, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);

	ImGui::SetWindowSize(ImVec2(400, 250));

	ImGui::Separator();

	//Scenario name label
	ImGui::Text("Scenario Name: ");
	ImGui::SameLine();
	helpMarker("The name of the scenario. Maximum 30 characters and no spaces.");
	//Scenario name input
	ImGui::InputText("##scenarioname", tempName, sizeof(tempName), ImGuiInputTextFlags_CharsNoBlank);

	ImGui::Separator();

	//Scenario map label
	ImGui::Text("Scenario Map: ");
	ImGui::SameLine();
	helpMarker(
		"The file path the program follows to load the image which will be the map used in the simulation\n\n"
		"The map should be in a 16:9 aspect ratio to prevent stretching during the simulation and should preferably be "
		"2700 x 1500 to prevent pixelation during the zoom (unless the zoom controls are disabled)\n\n"
		"The simulation also determines differing countries by their RGB colour values and each country / region "
		"should have its own unique colour.");
	//Scenario Map input
	ImGui::InputText("##mapfilepath", tempMapFilePath, sizeof(tempMapFilePath));
	ImGui::SameLine();
	if (ImGui::Button("Browse"))
	{
		char filename[MAX_PATH];
		OPENFILENAME ofn;
		ZeroMemory(&filename, sizeof(filename));
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;  // If you have a window to center over, put its HANDLE here
		//only able to use image type files
		ofn.lpstrFilter = "Image Files (*.jpg;*.png;.*gif;*.bmp)\0"
						"*.jpg;*.png;*.gif;*.bmp\0";
		ofn.lpstrFile = filename;
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrTitle = "Select map image";
		ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

		if (GetOpenFileName(&ofn))
		{
			strcpy(tempMapFilePath, filename);
			//std::cout << tempMapFilePath << "\n";
		}
	}

	ImGui::Separator();

	//create scenario button
	ImGui::Separator();
	ImGui::Separator();
	if (ImGui::Button("Create simulation", ImVec2(ImGui::GetWindowWidth(), 20)))
	{
		//validation checks
		if (strcmp(tempName, "") != 0)
		{
			acceptScenarioName = true;
		}
		if (strcmp(tempMapFilePath, "") != 0)
		{
			acceptImgPath = true;
		}
		
		//check if the file exists
		FILE *fp = fopen(tempMapFilePath, "r");
		if (fp != NULL)
		{
			existingImgPath = true;
			validType = true;

			//get image file type
			std::string processString = tempMapFilePath;
			if (processString.substr(processString.find_last_of(".") + 1) == "jpg" ||
				processString.substr(processString.find_last_of(".") + 1) == "JPG" ||
				processString.substr(processString.find_last_of(".") + 1) == "jpeg" ||
				processString.substr(processString.find_last_of(".") + 1) == "JPEG")
			{
				tempImgType = "jpg";
			}
			if (processString.substr(processString.find_last_of(".") + 1) == "png" ||
				processString.substr(processString.find_last_of(".") + 1) == "PNG")
			{
				tempImgType = "png";
			}
			if (processString.substr(processString.find_last_of(".") + 1) == "gif" ||
				processString.substr(processString.find_last_of(".") + 1) == "GIF")
			{
				tempImgType = "gif";
			}
			if (processString.substr(processString.find_last_of(".") + 1) == "bmp" ||
				processString.substr(processString.find_last_of(".") + 1) == "BMP")
			{
				tempImgType = "bmp";
			}

			//check if valid
			if (tempImgType != "png" && tempImgType != "gif" &&
				tempImgType != "bmp" && tempImgType != "jpg")
			{
				validType = false;
			}
		}
		else
		{			
			existingImgPath = false;
		}

		//if valid, commit to global
		if (acceptScenarioName && acceptImgPath && existingImgPath)
		{
			//copy temp name to global name
			strcpy(scenarioName, tempName);

			//copy img path to global img path
			strcpy(imgFilePath, tempMapFilePath);

			//file type of image
			imgType = tempImgType;

			//load the texture
			if (tempMapFilePath != "")
			{
				//SDL_Surface* tempSurf = IMG_Load(imgFilePath);
				SDL_Surface* tempSurf = IMG_Load(tempMapFilePath);

				map = SDL_CreateTextureFromSurface(renderer, tempSurf);
				SDL_FreeSurface(tempSurf);
				SDL_RenderCopy(renderer, map, NULL, NULL);//get texture size
				SDL_QueryTexture(map, NULL, NULL, &wMapX, &wMapY);
				vpSrc = { 0, 0, wMapX, wMapY };

				//resets map file path
				strcpy(textureLoc, tempMapFilePath);
				strcpy(tempMapFilePath, "");
			}

			strcpy(curScenario, tempName);

			resetNewScenario();
			scenarioLoaded = true;

			//tells the program that this is a new scenario, not a loaded scenario
			strcpy(curFileName, "");

			//also clear all the countries
			countryList.clear();
		}
		else
		{
			ImGui::OpenPopup("Cannot Create Scenario");
		}

	}
	ImGui::Separator();
	ImGui::Separator();

	bool error = true;
	if (ImGui::BeginPopupModal("Cannot Create Scenario", &error, ImGuiWindowFlags_NoResize))
	{
		ImGui::SetWindowSize(ImVec2(400, 150));

		if (!acceptScenarioName)
		{
			ImGui::Text("Name of the scenario cannot be empty.\n");
		}

		if (!acceptImgPath)
		{
			ImGui::Text("Map file path cannot be empty.\n");
		}
		
		if (!existingImgPath && acceptImgPath)
		{
			ImGui::Text("Map file does not exist\n");
		}

		if (existingImgPath && !validType)
		{
			ImGui::Text("Invalid image file\n");
		}

		//close popup
		ImGui::Separator();
		if (ImGui::Button("Close", ImVec2(ImGui::GetWindowWidth(), 20)))
		{
			ImGui::CloseCurrentPopup();
		}
		ImGui::Separator();
		ImGui::EndPopup();
	}
	ImGui::End();
	
}

/**
* resetNewScenario
* function that resets all the variables used for the new scenario menu
*/
void SCGUI::resetNewScenario()
{
	/*std::cout << "Name: " << name << std::endl
		<< "filepath: " << imgFilePath << std::endl
		<< "img type: " << imgType << std::endl
		<< "zombies: " << simulateZombies << std::endl;*/
	
	//reset the values relevant to new scenario
	strcpy(tempName, "");
	strcpy(tempMapFilePath, "");
	tempImgType = "";
	
	//reset validations
	acceptScenarioName = false;
	acceptImgPath = false;
	existingImgPath = false;

	newScenario = false;
}

/**
* newCountryMenu
* function that displays the new country menu when called. The function
* is also able to instantiate and add a country to the country list
*
* @param int r
* @param int g
* @param int b
*/
void SCGUI::newCountryMenu(int r, int g, int b) 
{
	if (r != -1 &&
		g != -1 &&
		b != -1)
	{
		tempR = r,
		tempB = b,
		tempG = g;
	}

	//make the window
	ImGui::Begin("New Country", &addNewCountry, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
	ImGui::SetWindowSize(ImVec2(700, 500), NULL);

	ImGui::Separator();
	#pragma region INPUT: CID AND CNAME

	//unique country ID
	ImGui::Text("Country ID: ");
	ImGui::SameLine();
	helpMarker(
		"A unique identifier for each country\n"
		"Maximum 4 characters"
	);
	ImGui::SameLine();
	ImGui::InputText("##uniquecountryID", tempID, sizeof(tempID), ImGuiInputTextFlags_CharsUppercase | ImGuiInputTextFlags_CharsNoBlank);

	ImGui::Separator();


	//country name label
	ImGui::Text("Country Name: ");
	//input box
	ImGui::SameLine();
	//help marker
	helpMarker("Country Name. Maximum 30 characters and use '-' as spaces");
	//country input
	ImGui::SameLine();
	ImGui::InputText("##countryname", tempCName, sizeof(tempCName), ImGuiInputTextFlags_CharsNoBlank);
	
	#pragma endregion INPUT: CID AND CNAME

	ImGui::Separator();
	#pragma region INPUT: REGION COLOUR
	//separate inputs into 3 columns
	ImGui::BeginColumns("##countrycolourinputs", 3, ImGuiColumnsFlags_NoBorder);

	//region identifier
	ImGui::Text("Country Region: ");
	ImGui::SameLine();
	helpMarker(
		"The colour that identifies as the country.\n" 
		"You can either input the colour manually or use the\n"
		"eye dropper tool to display the colour values from the image");
	ImGui::NextColumn();

	//eye dropper tool that will help identify region colours
	ImGui::Text("Eyedrop tool: ");
	ImGui::SameLine();
	ImGui::Checkbox("##eyeDropCheckbox", &eyedropperActive);
	ImGui::NextColumn();
	ImGui::NextColumn();

	//red colour input
	ImGui::TextColored(ImVec4(255, 0, 0, 255), "R: ");
	ImGui::SameLine();
	ImGui::InputInt("##redcolourinput", &tempR, NULL, NULL, NULL);
	//limiting input
	if (tempR > 255) tempR = 255;
	if (tempR < 0) tempR = 0;
	ImGui::SameLine();

	//green colour input
	ImGui::NextColumn();
	ImGui::TextColored(ImVec4(0, 255, 0, 255), "G: ");
	ImGui::SameLine();
	ImGui::InputInt("##greencolourinput", &tempG, NULL, NULL, NULL);
	//limiting input
	if (tempG > 255) tempG = 255;
	if (tempG < 0) tempG = 0;
	ImGui::SameLine();

	//blue colour input
	ImGui::NextColumn();
	ImGui::TextColored(ImVec4(0, 0, 255, 255), "B: ");
	ImGui::SameLine();
	ImGui::InputInt("##bluecolourinput", &tempB, NULL, NULL, NULL);
	//limiting input
	if (tempB > 255) tempB = 255;
	if (tempB < 0) tempB = 0;

	ImGui::EndColumns();

	#pragma endregion INPUT: REGION COLOUR

	ImGui::Separator();
	#pragma region INPUT: C ATTRIBUTES
	ImGui::BeginColumns("##newcountryattributescolumn", 2, ImGuiColumnsFlags_NoBorder);

	//country population
	ImGui::Text("Country Population: "); 
	ImGui::SameLine();
	helpMarker(
		"Maximum characters are set at 14 i.e. maximum value\n"
		"is set at 9.99 x 10 ^ 14. Value cannot be negative."
	);
	ImGui::SameLine();
	ImGui::NextColumn();
	ImGui::InputText("##countrypopinput", tempPop, sizeof(tempPop), ImGuiInputTextFlags_CharsDecimal);
	tempPopInt = strtoull(tempPop, (char **) NULL, 10);	//this converts to unsigned long long
	if (tempPopInt < 0) strcpy(tempPop, "0");
	if (tempPopInt > 99999999999999) strcpy(tempPop, "99999999999999");

	ImGui::Separator();

	//country GDP
	ImGui::NextColumn();
	ImGui::Text("Country GDP (Million US Dollars): ");
	ImGui::SameLine();
	helpMarker(
		"Maximum characters are set at 14 i.e. maximum value\n"
		"is set at 9.99 x 10 ^ 14. Value cannot be negative.\n"
		"Note that the value is in millions of USD"
	);
	ImGui::SameLine();
	ImGui::NextColumn();
	ImGui::InputText("##countryGDPinput", tempGDP, sizeof(tempGDP), ImGuiInputTextFlags_CharsDecimal);
	//limiting GDP
	tempGDPInt = strtoull(tempGDP, (char**)NULL, 10);
	if (tempGDPInt < 0) strcpy(tempGDP, "0");
	if (tempGDPInt > 99999999999999) strcpy(tempGDP, "99999999999999");

	ImGui::Separator();

	ImGui::NextColumn();
	ImGui::Text("Military Budget (Million US Dollars): ");
	ImGui::SameLine();
	helpMarker(
		"The military budget will be used to determine how\n"
		"well the country will fare in a zombie scenario.\n"
		"Maximum 14 characters (9.99x10^20 million USD)"
	);
	ImGui::SameLine();
	ImGui::NextColumn();
	ImGui::InputText("##countryMBinput", tempMilitaryBudget, sizeof(tempMilitaryBudget), ImGuiInputTextFlags_CharsDecimal);
	//limiting Military budget
	tempMBInt = strtoull(tempMilitaryBudget, (char**)NULL, 10);
	if (tempMBInt > 99999999999999) strcpy(tempMilitaryBudget, "99999999999999");
	//cannot be negative
	if (tempMBInt < 0) strcpy(tempMilitaryBudget, "0");

	ImGui::Separator();

	ImGui::NextColumn();
	ImGui::Text("Research Budget (Million US Dollars): ");
	ImGui::SameLine();
	helpMarker(
		"This is the country's contribution to the global research pool.\n"
		"The more money the world puts into the research pool, the \n"
		"faster a cure can be researched. Zombies cannot be cured, but\n"
		"once a cure is found, no more zombies can be made."
	);
	ImGui::SameLine();
	ImGui::NextColumn();
	ImGui::InputText("##countryRBinput", tempResearchSpending, sizeof(tempResearchSpending), ImGuiInputTextFlags_CharsDecimal);
	//limiting Military budget
	tempRSInt = strtoull(tempResearchSpending, (char**)NULL, 10);
	if (tempRSInt > 99999999999999) strcpy(tempResearchSpending, "99999999999999");
	//cannot be negative
	if (tempRSInt < 0) strcpy(tempResearchSpending, "0");
		
	ImGui::EndColumns();

	#pragma endregion INPUT: C ATTRIBUTES

	ImGui::Separator();
	#pragma region INPUT: C CLIMATE
	//country climates
	ImGui::Text("Country Climates: ");

	//temperature
	ImGui::Text("Temperature");

	ImGui::BeginColumns("##countrytempcolumn", 4, ImGuiColumnsFlags_NoBorder);
	
	//hot temperature
	ImGui::Text("Hot");
	ImGui::SameLine();
	ImGui::Checkbox("##hottempcheckbox", &hotTemp);
	ImGui::NextColumn();

	//cold temperature
	ImGui::Text("Cold");
	ImGui::SameLine();
	ImGui::Checkbox("##coldtempcheckbox", &coldTemp);
	ImGui::NextColumn();

	//neutral temperature
	ImGui::Text("Neutral");
	ImGui::SameLine();
	ImGui::Checkbox("##neutraltempcheckbox", &neutralTemp);

	//error checking
	//can EITHER be hot or cold but can't be in at the same time.
	//default to neutral if both hot and cold (and other combinations) are used at the same time
	if (hotTemp && coldTemp ||
		hotTemp && neutralTemp ||
		coldTemp && neutralTemp
		) neutralTemp = true, hotTemp = false, coldTemp = false;
	
	ImGui::NextColumn();

	//tooltip for user friendliness
	helpMarker(
		"The country's (average) temperature.\n"
		"Assume that any average temperature below 10 degrees Celsius is \n"
		"cold; Any temperature between 10 and 20 degrees Celsius is \n"
		"neutral and any temperature above 20 degrees Celsius is a hot \n"
		"climate\n\nThe menu will automatcally set to neutral if invalid \n"
		"options are made."
	);
	
	ImGui::EndColumns();

	//humidity
	ImGui::Text("Humidity");

	ImGui::BeginColumns("##countryhumiditycolumn", 4, ImGuiColumnsFlags_NoBorder);

	ImGui::Text("Wet");
	ImGui::SameLine();
	ImGui::Checkbox("##wethumcheckbox", &wetHum);
	ImGui::NextColumn();

	ImGui::Text("Dry ");
	ImGui::SameLine();
	ImGui::Checkbox("##dryhumcheckbox", &dryHum);
	ImGui::NextColumn();

	ImGui::Text("Neutral");
	ImGui::SameLine();
	ImGui::Checkbox("##neutralhumcheckbox", &neutralHum);
	ImGui::NextColumn();

	//tooltip
	helpMarker(
		"The country's (average) humidity.\n"
		"Wet refers to countries with high humidity such as\n"
		"rainforests / tropical monsoon areas.\n"
		"Dry refers to countries with low humidity such as\n"
		"deserts / arid areas\n\n"
		"The option will be set to neutral if invalid options\n"
		"are made."
	);

	//error checking
	//can EITHER be dry OR wet but cannot be both at the same time
	//default to neutral if invalid combinations are made
	if (dryHum && wetHum ||
		dryHum && neutralHum ||
		wetHum && neutralHum
		) neutralHum = true, wetHum = false, dryHum = false;

	ImGui::EndColumns();

	#pragma endregion INPUT: C CLIMATE

	ImGui::Separator();
	#pragma region INPUT: C CONNECTIONS
	ImGui::Text("Country Connections");

	//countries this country shares borders with
	if (ImGui::TreeNode("Border Countries"))
	{
		if (ImGui::ListBoxHeader("##bordercountries", ImVec2(400, 150)))
		{
			//make a selectable item for each country
			for (int countryNum = 0; countryNum < countryList.size(); countryNum++)
			{
				//add the country's unique ID to ensure no countries have similar selectable names
				//prevents imgui from having a hard time distinguishing selectables
				std::string countryString = countryList[countryNum].getID() + " - " + countryList[countryNum].getCountryName();
				//this is where the user can select which country is connected to another by land
				ImGui::Selectable(countryString.c_str(), &countryList[countryNum].selectedBorder);				
			}

			ImGui::ListBoxFooter();
		}

		ImGui::TreePop();
	}
	
	//countries this country has ocean routes to
	if (ImGui::TreeNode("Ocean Links"))
	{
		if (ImGui::ListBoxHeader("##oceanlinks", ImVec2(400, 150)))
		{
			//make a selectable item for each country
			for (int countryNum = 0; countryNum < countryList.size(); countryNum++)
			{
				//add the country's unique ID to ensure no countries have similar selectable names
				//prevents imgui from having a hard time distinguishing selectables
				std::string countryString = countryList[countryNum].getID() + " - " + countryList[countryNum].getCountryName();
				//this is where the user can select which country is connected to another by land
				ImGui::Selectable(countryString.c_str(), &countryList[countryNum].selectedSea);
			}

			ImGui::ListBoxFooter();
		}

		ImGui::TreePop();
	}

	//countries this country has air routes to
	if (ImGui::TreeNode("Air Links"))
	{
		if (ImGui::ListBoxHeader("##airlinks", ImVec2(400, 150)))
		{
			//make a selectable item for each country
			for (int countryNum = 0; countryNum < countryList.size(); countryNum++)
			{
				//add the country's unique ID to ensure no countries have similar selectable names
				//prevents imgui from having a hard time distinguishing selectables
				std::string countryString = countryList[countryNum].getID() + " - " + countryList[countryNum].getCountryName();
				//this is where the user can select which country is connected to another by land
				ImGui::Selectable(countryString.c_str(), &countryList[countryNum].selectedAir);
			}

			ImGui::ListBoxFooter();
		}

		ImGui::TreePop();
	}
	#pragma endregion INPUT: C CONNECTIONS
	ImGui::Separator();

	//input validation
	

	//create new country button
	if (ImGui::Button("Create Country", ImVec2(ImGui::GetWindowWidth(), 20)))
	{
		#pragma region NEW COUNTRY VALIDATION CHECK
		
		acceptNewCID = false;
		isNewCIDunique = false;
		acceptNewCName = false;

		//check if the id is not empty
		if (!strlen(tempID) == 0)
		{
			acceptNewCID = true;

			//check if the id is unique
			//the ID is a unique identifier, since some countries may have similar names
			if (doesCountryExist(tempID))
			{
				//find the offending country
				for (int i = 0; i < countryList.size(); i++)
				{
					if (tempID == countryList[i].getID())
					{
						errID = tempID;
						errName = countryList[i].getCountryName();
					}
				}
			}
			else
			{
				isNewCIDunique = true;
			}
		}

		//check if the country name is empty
		if (!strlen(tempCName) == 0)
		{
			acceptNewCName = true;
		}

		#pragma endregion NEW COUNTRY VALIDATION CHECK

		if (acceptNewCID && acceptNewCName && isNewCIDunique)
		{
			//find the correct value for climates
			int climTemp, climHum;

			if (neutralTemp) climTemp = 0;
			if (hotTemp) climTemp = 1;
			if (coldTemp) climTemp = 2;

			if (neutralHum) climHum = 0;
			if (wetHum) climHum = 1;
			if (dryHum) climHum = 2;

			//find the country(ies) selected as this country's land neighbours
			std::vector<std::string> landBorders;
			for (int borderScan = 0; borderScan < countryList.size(); borderScan++)
			{
				//if selected
				if (countryList[borderScan].selectedBorder)
				{
					landBorders.push_back(countryList[borderScan].getID());

					//adds this country to the other country's border list too
					countryList[borderScan].linkLand(tempID);
				}
			}

			//find the sea links
			std::vector<std::string> seaLinks;
			for (int seaScan = 0; seaScan < countryList.size(); seaScan++)
			{
				//if selected
				if (countryList[seaScan].selectedSea)
				{
					seaLinks.push_back(countryList[seaScan].getID());

					//add this country to the other country's border list too
					countryList[seaScan].linkSea(tempID);
				}
			}

			//find air links
			std::vector<std::string> airLinks;
			for (int airScan = 0; airScan < countryList.size(); airScan++)
			{
				//if selected
				if (countryList[airScan].selectedAir)
				{
					airLinks.push_back(countryList[airScan].getID());

					//add this country to thr other country's border list too
					countryList[airScan].linkAir(tempID);
				}
			}

			//create the country
			Country newCountry = Country(
				tempID,
				tempCName,
				tempR, tempG, tempB,
				tempPopInt,
				tempGDPInt,
				tempMBInt,
				tempRSInt,
				climTemp,
				climHum,
				landBorders,
				seaLinks,
				airLinks
			);

			//debug country stats
			/*std::cout <<
				"ID: " << newCountry.getID() << std::endl <<
				"Name: " << newCountry.getCountryName() << std::endl <<
				"Pop: "  << newCountry.getPopulation() << std::endl <<
				"GDP: " << newCountry.getGDP() << std::endl <<
				"MB: " << newCountry.getMilitaryBudget() << std::endl <<
				"RB: " << newCountry.getResearchBudget() << std::endl;*/

			//add to country list
			countryList.push_back(newCountry);
			resetNewCountry();
		}
		else
		{
			ImGui::OpenPopup("Cannot Create Country");
		}
		
	}

	if (ImGui::Button("Reset", ImVec2(ImGui::GetWindowWidth(), 20)))
	{
		resetNewCountry();
	}
	
	//Error popup if country cannot be created
	bool error = true;
	if (ImGui::BeginPopupModal("Cannot Create Country", &error, ImGuiWindowFlags_NoResize))
	{
		ImGui::SetWindowSize(ImVec2(400, 200));

		//printing the error messages
		if (!acceptNewCID)
		{
			ImGui::Text("The Unique ID must not be empty\n");
			ImGui::NewLine();
		}
		if (!isNewCIDunique && acceptNewCID)
		{
			std::string errText =
				"The ID must be unique\nCountry: " + errID + "-" + errName + " already exists with ID\n";
			
			ImGui::Text(errText.c_str());
			ImGui::NewLine();
		}
		if (!acceptNewCName)
		{
			ImGui::Text("The country must have a name");
		}

		ImGui::Separator();
		//close the popup
		if (ImGui::Button("Close", ImVec2(ImGui::GetWindowWidth(), 20)))
		{
			ImGui::CloseCurrentPopup();
		}
		ImGui::Separator();

		ImGui::EndPopup();
	}

	ImGui::End();

	

	//only work if the mouse is not over any imgui items
	if (eyedropperActive && !ImGui::IsAnyItemHovered() && !ImGui::IsAnyWindowHovered())
	{
		eyedropTool();
	}
}

/**
* resetNewCountry
* function that resets all the variables used for the new country menu
*/
void SCGUI::resetNewCountry()
{
	//reset all variables
	strcpy(tempID, "");

	strcpy(tempCName, "");

	tempR = 0,
		tempG = 0,
		tempB = 0;

	clickR = -1,
		clickG = -1,
		clickB = -1;

	//active eye dropper
	eyedropperActive = false;

	//country's population
	strcpy(tempPop, "");

	//country GDP
	strcpy(tempGDP, "");

	//country military budget
	strcpy(tempMilitaryBudget, "");

	//country research spending
	strcpy(tempResearchSpending, "");

	//climate booleans
	//temperatures
	hotTemp = false,
		coldTemp = false,
		neutralTemp = true,

		//humidity
		wetHum = false,
		dryHum = false,
		neutralHum = true;

	//country borders
	tempLandBorders.clear();

	//air and ocean links
	tempAirLinks.clear();
	tempSeaLinks.clear();

	//remove the selected option from countries
	for (int i = 0; i < countryList.size(); i++)
	{
		countryList[i].selectedBorder = false;
		countryList[i].selectedSea = false;
		countryList[i].selectedAir = false;
	}

	acceptNewCID = acceptNewCName = isNewCIDunique = false;
}

/**
* editCountryMenu
* function that when called to be displayed will show the menu for editing countries.
* function is very similar to new country menu but acts differently and contains extra things
*/
void SCGUI::editCountryMenu()
{
	//make the window
	ImGui::Begin("Edit Country", &editCountry, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
	ImGui::SetWindowSize(ImVec2(700, 500), NULL);

	ImGui::Separator();

	//unique country ID
	ImGui::Text("Country ID: ");
	ImGui::SameLine();
	helpMarker(
		"A unique identifier for each country\n"
		"Maximum 4 characters"
	);
	ImGui::SameLine();
	ImGui::InputText("##euniquecountryID", editID, sizeof(editID), ImGuiInputTextFlags_CharsUppercase | ImGuiInputTextFlags_CharsNoBlank);

	ImGui::Separator();


	//country name label
	ImGui::Text("Country Name: ");
	//input box
	ImGui::SameLine();
	//help marker
	helpMarker("Country Name. Maximum 30 characters and use '-' as spaces");
	//country input
	ImGui::SameLine();
	ImGui::InputText("##ecountryname", editCName, sizeof(editCName), ImGuiInputTextFlags_CharsNoBlank);
	ImGui::Separator();



	//separate inputs into 3 columns
	ImGui::BeginColumns("##ecountrycolourinputs", 3, ImGuiColumnsFlags_NoBorder);

	//region identifier
	ImGui::Text("Country Region: ");
	ImGui::SameLine();
	helpMarker(
		"The colour that identifies as the country.\n"
		"You can either input the colour manually or use the\n"
		"eye dropper tool to display the colour values from the image");
	ImGui::NextColumn();

	//eye dropper tool that will help identify region colours
	ImGui::Text("Eyedrop tool: ");
	ImGui::SameLine();
	ImGui::Checkbox("##editeyeDropCheckbox", &editEyeDropperActive);
	ImGui::NextColumn();
	ImGui::NextColumn();

	//red colour input
	ImGui::TextColored(ImVec4(255, 0, 0, 255), "R: ");
	ImGui::SameLine();
	ImGui::InputInt("##eredcolourinput", &editR, NULL, NULL, NULL);
	//limiting input
	if (editR > 255) editR = 255;
	if (editR < 0) editR = 0;
	ImGui::SameLine();

	//green colour input
	ImGui::NextColumn();
	ImGui::TextColored(ImVec4(0, 255, 0, 255), "G: ");
	ImGui::SameLine();
	ImGui::InputInt("##egreencolourinput", &editG, NULL, NULL, NULL);
	//limiting input
	if (editG > 255) editG = 255;
	if (editG < 0) editG = 0;
	ImGui::SameLine();

	//blue colour input
	ImGui::NextColumn();
	ImGui::TextColored(ImVec4(0, 0, 255, 255), "B: ");
	ImGui::SameLine();
	ImGui::InputInt("##ebluecolourinput", &editB, NULL, NULL, NULL);
	//limiting input
	if (editB > 255) editB = 255;
	if (editB < 0) editB = 0;

	ImGui::EndColumns();

	ImGui::Separator();
	ImGui::BeginColumns("##enewcountryattributescolumn", 2, ImGuiColumnsFlags_NoBorder);

	//country population
	ImGui::Text("Country Population: ");
	ImGui::SameLine();
	helpMarker(
		"Maximum characters are set at 14 i.e. maximum value\n"
		"is set at 9.99 x 10 ^ 14. Value cannot be negative."
	);
	ImGui::SameLine();
	ImGui::NextColumn();
	ImGui::InputText("##ecountrypopinput", editPop, sizeof(editPop), ImGuiInputTextFlags_CharsDecimal);
	editPopInt = strtoull(editPop, (char**)NULL, 10);
	if (editPopInt < 0) strcpy(editPop, "0");
	if (editPopInt > 99999999999999) strcpy(editPop, "99999999999999");

	ImGui::Separator();

	//country GDP
	ImGui::NextColumn();
	ImGui::Text("Country GDP (Million US Dollars): ");
	ImGui::SameLine();
	helpMarker(
		"Maximum characters are set at 14 i.e. maximum value\n"
		"is set at 9.99 x 10 ^ 14. Value cannot be negative.\n"
		"Note that the value is in millions of USD"
	);
	ImGui::SameLine();
	ImGui::NextColumn();
	ImGui::InputText("##ecountryGDPinput", editGDP, sizeof(editGDP), ImGuiInputTextFlags_CharsDecimal);
	//limiting GDP	
	editGDPInt = strtoull(editGDP, (char**)NULL, 10);
	if (editGDPInt > 99999999999999) strcpy(editGDP, "99999999999999");
	//<insert joke about removing government debt here>
	if (editGDPInt < 0) strcpy(editGDP, "0");

	ImGui::Separator();

	ImGui::NextColumn();
	ImGui::Text("Military Budget (Million US Dollars): ");
	ImGui::SameLine();
	helpMarker(
		"The military budget will be used to determine how\n"
		"well the country will fare in a zombie scenario.\n"
		"Maximum 12 characters (9.99x10^20 million USD)"
	);
	ImGui::SameLine();
	ImGui::NextColumn();
	ImGui::InputText("##ecountryMBinput", editMilitaryBudget, sizeof(editMilitaryBudget), ImGuiInputTextFlags_CharsDecimal);
	//limiting Military budget
	editMBInt = strtoull(editMilitaryBudget, (char**)NULL, 10);
	if (editMBInt > 99999999999999) strcpy(editMilitaryBudget, "99999999999999");
	//cannot be negative
	if (editMBInt < 0) strcpy(editMilitaryBudget, "0");

	ImGui::Separator();

	ImGui::NextColumn();
	ImGui::Text("Research Budget (Million US Dollars): ");
	ImGui::SameLine();
	helpMarker(
		"This is the country's contribution to the global research pool.\n"
		"The more money the world puts into the research pool, the \n"
		"faster a cure can be researched. Zombies cannot be cured, but\n"
		"once a cure is found, no more zombies can be made."
	);
	ImGui::SameLine();
	ImGui::NextColumn();
	ImGui::InputText("##ecountryRBinput", editResearchSpending, sizeof(editResearchSpending), ImGuiInputTextFlags_CharsDecimal);
	//limiting Military budget
	editRSInt = strtoull(editResearchSpending, (char**)NULL, 10);
	if (editRSInt > 99999999999999) strcpy(editResearchSpending, "99999999999999");
	//cannot be negative
	if (editRSInt < 0) strcpy(editResearchSpending, "0");

	ImGui::Separator();

	ImGui::EndColumns();

	//country climates
	ImGui::Text("Country Climates: ");

	//temperature
	ImGui::Text("Temperature");

	ImGui::BeginColumns("##ecountrytempcolumn", 4, ImGuiColumnsFlags_NoBorder);

	//hot temperature
	ImGui::Text("Hot");
	ImGui::SameLine();
	ImGui::Checkbox("##ehottempcheckbox", &ehotTemp);
	ImGui::NextColumn();

	//cold temperature
	ImGui::Text("Cold");
	ImGui::SameLine();
	ImGui::Checkbox("##ecoldtempcheckbox", &ecoldTemp);
	ImGui::NextColumn();

	//neutral temperature
	ImGui::Text("Neutral");
	ImGui::SameLine();
	ImGui::Checkbox("##eneutraltempcheckbox", &eneutralTemp);

	//error checking
	//can EITHER be hot or cold but can't be in at the same time.
	//default to neutral if both hot and cold (and other combinations) are used at the same time
	if (ehotTemp && ecoldTemp ||
		ehotTemp && eneutralTemp ||
		ecoldTemp && eneutralTemp
		) eneutralTemp = true, ehotTemp = false, ecoldTemp = false;

	ImGui::NextColumn();

	//tooltip for user friendliness
	helpMarker(
		"The country's (average) temperature.\n"
		"Assume that any average temperature below 10 degrees Celsius is \n"
		"cold; Any temperature between 10 and 20 degrees Celsius is \n"
		"neutral and any temperature above 20 degrees Celsius is a hot \n"
		"climate\n\nThe menu will automatcally set to neutral if invalid \n"
		"options are made."
	);

	ImGui::EndColumns();

	//humidity
	ImGui::Text("Humidity");

	ImGui::BeginColumns("##ecountryhumiditycolumn", 4, ImGuiColumnsFlags_NoBorder);

	ImGui::Text("Wet");
	ImGui::SameLine();
	ImGui::Checkbox("##ewethumcheckbox", &ewetHum);
	ImGui::NextColumn();

	ImGui::Text("Dry ");
	ImGui::SameLine();
	ImGui::Checkbox("##edryhumcheckbox", &edryHum);
	ImGui::NextColumn();

	ImGui::Text("Neutral");
	ImGui::SameLine();
	ImGui::Checkbox("##eneutralhumcheckbox", &eneutralHum);
	ImGui::NextColumn();

	//tooltip
	helpMarker(
		"The country's (average) humidity.\n"
		"Wet refers to countries with high humidity such as\n"
		"rainforests / tropical monsoon areas.\n"
		"Dry refers to countries with low humidity such as\n"
		"deserts / arid areas\n\n"
		"The option will be set to neutral if invalid options\n"
		"are made."
	);

	//error checking
	//can EITHER be dry OR wet but cannot be both at the same time
	//default to neutral if invalid combinations are made
	if (edryHum && ewetHum ||
		edryHum && eneutralHum ||
		ewetHum && eneutralHum
		) eneutralHum = true, ewetHum = false, edryHum = false;

	ImGui::EndColumns();

	ImGui::Separator();

	ImGui::Text("Country Connections");

	//countries this country shares borders with
	if (ImGui::TreeNode("Border Countries"))
	{
		if (ImGui::ListBoxHeader("##ebordercountries", ImVec2(400, 150)))
		{
			//make a selectable item for each country
			for (int countryNum = 0; countryNum < countryList.size(); countryNum++)
			{
				//country cannot border itself
				if (countryList[countryNum].getID() != editID)
				{
					//add the country's unique ID to ensure no countries have similar selectable names
					//prevents imgui from having a hard time distinguishing selectables
					std::string countryString = countryList[countryNum].getID() + " - " + countryList[countryNum].getCountryName();
					//this is where the user can select which country is connected to another by land
					ImGui::Selectable(countryString.c_str(), &countryList[countryNum].selectedBorder);
				}
			}

			ImGui::ListBoxFooter();
		}

		ImGui::TreePop();
	}

	//countries this country has ocean routes to
	if (ImGui::TreeNode("Ocean Links"))
	{
		if (ImGui::ListBoxHeader("##oceanlinks", ImVec2(400, 150)))
		{
			//make a selectable item for each country
			for (int countryNum = 0; countryNum < countryList.size(); countryNum++)
			{
				//country should not have seal links to itself
				if (countryList[countryNum].getID() != editID)
				{
					//add the country's unique ID to ensure no countries have similar selectable names
					//prevents imgui from having a hard time distinguishing selectables
					std::string countryString = countryList[countryNum].getID() + " - " + countryList[countryNum].getCountryName();
					//this is where the user can select which country is connected to another by land
					ImGui::Selectable(countryString.c_str(), &countryList[countryNum].selectedSea);
				}
			}

			ImGui::ListBoxFooter();
		}

		ImGui::TreePop();
	}

	//countries this country has air routes to
	if (ImGui::TreeNode("Air Links"))
	{
		if (ImGui::ListBoxHeader("##airlinks", ImVec2(400, 150)))
		{
			

			//make a selectable item for each country
			for (int countryNum = 0; countryNum < countryList.size(); countryNum++)
			{
				//country should not have air links to itself
				if (countryList[countryNum].getID() != editID)
				{
					//add the country's unique ID to ensure no countries have similar selectable names
					//prevents imgui from having a hard time distinguishing selectables
					std::string countryString = countryList[countryNum].getID() + " - " + countryList[countryNum].getCountryName();
					//this is where the user can select which country is connected to another by land
					ImGui::Selectable(countryString.c_str(), &countryList[countryNum].selectedAir);
				}
			}
			ImGui::ListBoxFooter();
		}

		ImGui::TreePop();
	}



	ImGui::Separator();

	//create new country button
	if (ImGui::Button("Edit Country", ImVec2(ImGui::GetWindowWidth(), 20)))
	{
		//prevents crashing
		if (countryList.size() > currentCountry)
		{
			countryList.erase(countryList.begin() + currentCountry);
		}
		
		//find the correct value for climates
		int climTemp, climHum;

		if (eneutralTemp) climTemp = 0;
		if (ehotTemp) climTemp = 1;
		if (ecoldTemp) climTemp = 2;

		if (eneutralHum) climHum = 0;
		if (ewetHum) climHum = 1;
		if (edryHum) climHum = 2;
		
		//find the country(ies) selected as this country's land neighbours
		std::vector<std::string> landBorders;
		for (int borderScan = 0; borderScan < countryList.size(); borderScan++)
		{
			//if selected
			if (countryList[borderScan].selectedBorder)
			{
				landBorders.push_back(countryList[borderScan].getID());

				//add this country to the other country's border list too
				countryList[borderScan].linkLand(editID);
			}
			else
			{
				//if not selected, remove from the country's list, just in case
				countryList[borderScan].removeLinkLand(editID);
			}
		}

		//find the sea links
		std::vector<std::string> seaLinks;
		for (int seaScan = 0; seaScan < countryList.size(); seaScan++)
		{
			//if selected
			if (countryList[seaScan].selectedSea)
			{
				seaLinks.push_back(countryList[seaScan].getID());

				//add this country to the other country's border list too
				countryList[seaScan].linkSea(editID);
			}
			else
			{
				//if not selected, remove from the country's list, just in case
				countryList[seaScan].removeLinkSea(editID);
			}
		}

		//find air links
		std::vector<std::string> airLinks;
		for (int airScan = 0; airScan < countryList.size(); airScan++)
		{
			//if selected
			if (countryList[airScan].selectedAir)
			{
				airLinks.push_back(countryList[airScan].getID());

				//add this country to the other country's border list too
				countryList[airScan].linkAir(editID);
			}
			else
			{
				//if not selected, remove from the country's list, just in case
				countryList[airScan].removeLinkAir(editID);
			}
		}

		//create the country
		Country newCountry = Country(
			editID,
			editCName,
			editR, editG, editB,
			editPopInt,
			editGDPInt,
			editMBInt,
			editRSInt,
			climTemp,
			climHum,
			landBorders,
			seaLinks,
			airLinks
		);

		//add to country list
		countryList.insert(countryList.begin() + currentCountry, newCountry);
	}

	ImGui::End();

	//only work if the mouse is not over any imgui items
	if (eyedropperActive && !ImGui::IsAnyItemHovered() && !ImGui::IsAnyWindowHovered())
	{
		eyedropTool();
	}
}

/**
* render
* function that renders everything; the ImGui elements as well as the map
*
* @param SDL_Window *window
* @param SDL_Renderer *renderer
*/
void SCGUI::render(SDL_Window * window, SDL_Renderer * renderer)
{
	//update vp size
	vp.y = 20;
	vp.w = ((int)ImGui::GetIO().DisplaySize.x);
	vp.h = ((int)ImGui::GetIO().DisplaySize.y) - 20;

	//gets the world size
	SDL_GetWindowSize(window, &worldX, &worldY);
	//link viewports to the renderer
	SDL_RenderSetViewport(renderer, &vp);

	//clear the screen
	SDL_SetRenderDrawColor(renderer,
		bkgColour.x * 255.0f,
		bkgColour.y * 255.0f,
		bkgColour.z * 255.0f,
		bkgColour.w * 255.0f);
	SDL_RenderClear(renderer);

	//render the world map
	if (map != NULL)
	{
		SDL_RenderCopy(renderer, map, &vpSrc, NULL);
		//std::cout << "test\n";
	}

	//not to show tooltip if either eyedroppers are active 
	//and the mouse is not over any ImGui components
	if (!ImGui::IsAnyItemHovered() && !ImGui::IsAnyWindowHovered())
	{
		mouseOver();
	}

	//render the IMGUI elements
	glUseProgram(0);
	ImGui::Render();


	//update the screen
	SDL_RenderPresent(renderer);
}

/**
* doesCountryExist
* function used to check if a country exists by checking if unique ID's match
*
* @param string id
*/
bool SCGUI::doesCountryExist(std::string id)
{
	bool exist = false;

	for (int scan = 0; scan < countryList.size(); scan++)
	{
		//check if ID's match
		if (id == countryList[scan].getID())
		{
			exist = true;
		}
	}

	return exist;
}

/**
* eyedropTool
* function that shows to the user the red, green and blue colour values underneath the user pointer
*/
void SCGUI::eyedropTool()
{
	//source of this function: 
	//https://stackoverflow.com/questions/3078919/how-do-i-get-the-pixel-color-under-the-cursor
	POINT p;
	BOOL b;

	// Get the current cursor position
	b = GetCursorPos(&p);
	COLORREF colour;
	HDC hDC;

	// Get the device context for the screen
	hDC = GetDC(NULL);
	if (hDC == NULL)
		std::cout << 3;

	if (!b)
		std::cout << 2;

	// Retrieve the color at that position
	colour = GetPixel(hDC, p.x, p.y);
	if (colour == CLR_INVALID)
		std::cout << 1;

	// Release the device context again
	ReleaseDC(GetDesktopWindow(), hDC);

	//printf("%i %i %i\n", GetRValue(colour), GetGValue(colour), GetBValue(colour));

	//find the country which matches the colour
	SDL_Color comparison = { GetRValue(colour), GetGValue(colour), GetBValue(colour) };

	//loop through the country list to find a matching colour
	for (int i = 0; i < countryList.size(); i++)
	{
		//get country colour
		SDL_Color countryColour = countryList[i].getColour();

		//debugging
		/*std::cout << countryList[i].getCountryName() << ": " << (int)countryColour.r << "|" << (int)countryColour.g << "|" << (int)countryColour.b << std::endl;
		printf("%i %i %i\n", GetRValue(colour), GetGValue(colour), GetBValue(colour));*/

		if (comparison.r == countryColour.r		//compare red values
			&& comparison.g == countryColour.g	//compare green values
			&& comparison.b == countryColour.b	//compare blue values
			)
		{
			//set the current country to this country (countryList[i])
			curCountry = countryList[i];

			//break the loop
			break;
		}
	}

	//if the country was identified
	if ((int)comparison.r != (int)bkgColour.w &&
		(int)comparison.g != (int)bkgColour.x &&
		(int)comparison.b != (int)bkgColour.y)
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(450.0f);

		//text to show
		std::string rTxt = std::to_string((int)comparison.r);
		std::string gTxt = std::to_string((int)comparison.g);
		std::string bTxt = std::to_string((int)comparison.b);
		std::string col = "R: " + rTxt + ", G: " + gTxt + ", B: " + bTxt;

		ImGui::TextUnformatted(col.c_str());

		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

/**
* zoom
* function that manipulates the zoom of the map to be displayed
*
* @param int zoomType (0 = zoom in, 1 = zoom out)
*/
void SCGUI::zoom(int zoomType)
{
	//prevents the control if the user is over any ImGui components
	if (!ImGui::IsAnyItemHovered() && !ImGui::IsAnyWindowHovered())
	{
		//store the old zoom
		float oldZoom = zoomVal;

		//determine the zoom type and alter the zoom val
		switch (zoomType)
		{
		case -1:
			//place holder input
			break;

			//zoom in
		case 0:
			if (zoomVal - zoomInterval > minZoom)
			{
				zoomVal -= zoomInterval;
				//std::cout << "zoomed in" << std::endl;
			}
			break;

			//zoom out
		case 1:
			if (zoomVal + zoomInterval <= maxZoom)
			{
				zoomVal += zoomInterval;
				//std::cout << "zoomed out" << std::endl;
			}
			break;

		default:
			std::cout << "Unknown zoom type" << std::endl;
			break;
		}

		//adjust vpSrc
		if (oldZoom - zoomVal != 0)
		{
			vpSrc.w = wMapX * zoomVal;
			vpSrc.h = wMapY * zoomVal;
			vpSrc.x = wMapX / 2 - vpSrc.w / 2;
			vpSrc.y = wMapY / 2 - vpSrc.h / 2;
		}

		//std::cout << zoomVal << std::endl;

		//limit the x and y of the source
		panLimiting();
	}
}

/**
* pan
* function that allows the user to pan the map around, so they are able to
* see around the map, especially when zoomed in
*
* @param SDL_Point *mPos
* @param int motionX
* @param int motionY
*/
void SCGUI::pan(SDL_Point * mPos, int motionX, int motionY)
{
	//prevents control if the user is over any ImGui components
	if (!ImGui::IsAnyItemHovered() && !ImGui::IsAnyWindowHovered())
	{
		//check if the mouse is within the viewport
		if (SDL_PointInRect(mPos, &vp))
		{
			vpSrc.x += motionX * 2;
			vpSrc.y += motionY * 2;
			//std::cout << "X: " << vpSrc.x << std::endl << "Y: " << vpSrc.y << std::endl;

			//limit the panning so there is no texture streching
			panLimiting();
		}
	}
	
}

/**
* panLimiting
* function that ensures that the user remains within the bounds of the image i.e.
* prevents user from being lost while panning
*/
void SCGUI::panLimiting()
{
	//limit for the left scrolling
	if (vpSrc.x < 0)
	{
		vpSrc.x = 0;
	}
	//limit for up scrolling
	if (vpSrc.y < 0)
	{
		vpSrc.y = 0;
	}
	//limit for scrolling to the right
	if (vpSrc.x > wMapX - vpSrc.w)
	{
		vpSrc.x = wMapX - vpSrc.w;
	}
	//limit for scrolling to the bottom
	if (vpSrc.y > wMapY - vpSrc.h)
	{
		vpSrc.y = wMapY - vpSrc.h;
	}
}

/**
* mouseOver
* function that displays what country the user is moused over
*/
void SCGUI::mouseOver()
{
	//variables to get mouse position and screen context
	POINT p;
	BOOL b;

	// Get the current cursor position
	b = GetCursorPos(&p);
	COLORREF colour;
	HDC hDC;

	// Get the device context for the screen
	hDC = GetDC(NULL);
	if (hDC == NULL)
		std::cout << "Unable to get screen context\n";

	if (!b)
		std::cout << "Unable to get cursor position\n";

	// Retrieve the color at that position
	colour = GetPixel(hDC, p.x, p.y);
	if (colour == CLR_INVALID)
		std::cout << "Obtained colour invalid\n";

	// Release the device context again
	ReleaseDC(GetDesktopWindow(), hDC);

	//find the country which matches the colour
	SDL_Color comparison = { GetRValue(colour), GetGValue(colour), GetBValue(colour) };

	bool countryFound = false;
	//check if current mouse over colour is the same, if not find out which country
	//this prevents having to go through the loop everytime, uses less computing processes
	//also ensures that the current colour is not the background colour
	if (
		comparison.r != bkgColour.x &&
		comparison.g != bkgColour.y &&
		comparison.b != bkgColour.z)
	{
		for (int i = 0; i < countryList.size(); i++)
		{
			//get country colour
			SDL_Color countryColour = countryList[i].getColour();

			//debugging
			/*std::cout << countryList[i].getCountryName() << ": " << (int)countryColour.r << "|" << (int)countryColour.g << "|" << (int)countryColour.b << std::endl;
			printf("%i %i %i\n", GetRValue(colour), GetGValue(colour), GetBValue(colour));*/

			if (comparison.r == countryColour.r		//compare red values
				&& comparison.g == countryColour.g	//compare green values
				&& comparison.b == countryColour.b	//compare blue values
				)
			{
				//set this as the scroll country
				scrollCountry = countryList[i];

				//set scroll colour equal to this
				curCol.r = countryColour.r;
				curCol.g = countryColour.g;
				curCol.b = countryColour.b;

				//country found
				countryFound = true;

				//break the loop
				break;
			}
		}

		//if country was not found, set scroll colour equal to current colour
		if (!countryFound)
		{
			curCol.r = comparison.r;
			curCol.g = comparison.g;
			curCol.b = comparison.b;
		}
	}
	
	//if the country was identified
	if (countryFound && scenarioLoaded)
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(450.0f);
		//get country name
		ImGui::TextUnformatted(scrollCountry.getCountryName().c_str());
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
		newCountryOnClick = false;
	}
	//if not the background colour
	else if(
		comparison.r != bkgColour.x &&
		comparison.g != bkgColour.y &&
		comparison.b != bkgColour.z &&
		scenarioLoaded
		)
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(450.0f);
		ImGui::TextUnformatted("Add New Country?");
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
		newCountryOnClick = true;
	}
	else
	{
		newCountryOnClick = false;
	}
}

/**
* leftClick
* function called when a left click is detected by the Main class's inputs.
* The function determines how to respond when a left click is detected
*/
void SCGUI::leftClick()
{
	//source of this function: 
	//https://stackoverflow.com/questions/3078919/how-do-i-get-the-pixel-color-under-the-cursor
	POINT p;
	BOOL b;

	// Get the current cursor position
	b = GetCursorPos(&p);
	COLORREF colour;
	HDC hDC;

	// Get the device context for the screen
	hDC = GetDC(NULL);
	if (hDC == NULL)
		std::cout << 3;

	if (!b)
		std::cout << 2;

	// Retrieve the color at that position
	colour = GetPixel(hDC, p.x, p.y);
	if (colour == CLR_INVALID)
		std::cout << 1;

	// Release the device context again
	ReleaseDC(GetDesktopWindow(), hDC);

	//printf("%i %i %i\n", GetRValue(colour), GetGValue(colour), GetBValue(colour));

	//find the country which matches the colour
	SDL_Color comparison = { GetRValue(colour), GetGValue(colour), GetBValue(colour) };

	bool countryFound = false;

	//loop through the country list to find a matching colour
	for (int count = 0; count < countryList.size(); count++)
	{
		//get country colour
		SDL_Color countryColour = countryList[count].getColour();

		//debugging
		/*std::cout << countryList[i].getCountryName() << ": " << (int)countryColour.r << "|" << (int)countryColour.g << "|" << (int)countryColour.b << std::endl;
		printf("%i %i %i\n", GetRValue(colour), GetGValue(colour), GetBValue(colour));*/

		if (comparison.r == countryColour.r		//compare red values
			&& comparison.g == countryColour.g	//compare green values
			&& comparison.b == countryColour.b	//compare blue values
			)
		{
			//country is found
			countryFound = true;

			//set the current country to this country (countryList[i])
			curCountry = countryList[count];
			currentCountry = count;

			//set edit ID
			strcpy(editID, countryList[count].getID().c_str());

			//set edit name
			strcpy(editCName, countryList[count].getCountryName().c_str());

			//set region colours
			SDL_Color colour = countryList[count].getColour();
			editR = colour.r;
			editG = colour.g;
			editB = colour.b;

			//set population
			strcpy(editPop, std::to_string(countryList[count].getPopulation()).c_str());

			//set gdp
			strcpy(editGDP, std::to_string(countryList[count].getGDP()).c_str());

			//set military budget
			strcpy(editMilitaryBudget, std::to_string(countryList[count].getMilitaryBudget()).c_str());

			//set research budget
			strcpy(editResearchSpending, std::to_string(countryList[count].getResearchBudget()).c_str());

			int temp = countryList[count].getTemperature();
			eneutralTemp = ehotTemp = ecoldTemp = false;
			int hum = countryList[count].getHumidity();
			eneutralHum = ewetHum = edryHum = false;

			//setting correct settings for temperature
			switch (temp)
			{
			case 0:
				eneutralTemp = true;
				break;

			case 1:
				ehotTemp = true;
				break;

			case 2:
				ecoldTemp = true;
				break;

			default:
				break;
			}

			//setting correct settings for humidity
			switch (hum)
			{
			case 0:
				eneutralHum = true;
				break;

			case 1:
				ewetHum = true;
				break;

			case 2:
				edryHum = true;
				break;

			default:
				break;
			}

			//set land air and sea borders equal to the temps
			tempLandBorders = countryList[count].getLandBorders();
			tempSeaLinks = countryList[count].getSeaLinks();
			tempAirLinks = countryList[count].getAirLinks();

			//load land, air and sea borders
			for (int scan = 0; scan < countryList.size(); scan++)
			{
				//check for land borders
				for (int landScan = 0; landScan < tempLandBorders.size(); landScan++)
				{
					//if ID's match then set selected for land and then break loop
					if (tempLandBorders[landScan] == countryList[scan].getID())
					{
						countryList[scan].selectedBorder = true;
						break;
					}
				}

				//doing the same for air and sea
				for (int seaScan = 0; seaScan < tempSeaLinks.size(); seaScan++)
				{
					if (tempSeaLinks[seaScan] == countryList[scan].getID())
					{
						countryList[scan].selectedSea = true;
						break;
					}
				}

				for (int airScan = 0; airScan < tempAirLinks.size(); airScan++)
				{
					if (tempAirLinks[airScan] == countryList[scan].getID())
					{
						countryList[scan].selectedAir = true;
						break;
					}
				}
			}

			//opens the edit menu
			editCountry ^= 1;

			//break the loop
			break;
		}


	}

	if (!countryFound && !ImGui::IsAnyItemHovered() && !ImGui::IsAnyWindowHovered() &&
		comparison.r != bkgColour.x &&
		comparison.g != bkgColour.y &&
		comparison.b != bkgColour.z &&
		scenarioLoaded)
	{
		addNewCountry = true;
		clickR = comparison.r;
		clickG = comparison.g;
		clickB = comparison.b;
	}
}
