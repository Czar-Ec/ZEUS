#pragma once
//IMGUI
#include "../sharedobjects/imgui.h"
#include "../sharedobjects/imgui_internal.h"
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
#include <stdio.h>

//opening external programs
#include <shellapi.h>

//data storing
#include <vector>

//data handling (loading and saving)
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>
#include <algorithm>

//threading
#include <thread>

//other items
#include "../sharedobjects/Country.h"
#include "../sharedobjects/DataHandler.h"
#include "../sharedobjects/UX.h"
#include "../sharedobjects/IconsFontAwesome4.h"

/**
* GUI Class
* the class which handles the imgui actions and will be drawing and handling the actions on the scren
*/
static class GUI
{
	public:
		GUI();
		GUI(SDL_Renderer *renderer, int winX, int winY);
		~GUI();

		//load country data
		bool loadScenario(SDL_Renderer *renderer, std::string filePath);

		//draw menu bar
		void menuBar(bool &appRun, SDL_Renderer *renderer);

		//info box
		void infoBox();

		//tool bar
		void toolBar();

		//menu bar functions
		void newSim(SDL_Renderer *renderer);
		void resetNewSim();

		void openSim();

		void save();
		void saveAs();

		void editSimVals();

		//run simulations
		void simulate();
		void countrySim(int countryNum);
		void resetSim();

		//render items
		void render(SDL_Window *window, SDL_Renderer *renderer);

		//CONTROLS AND SHORTCUTS
		void ctrlN();	//new simulation shortcut
		void ctrlO();	//open simulation shortcut
		void spaceBar();

		void mouseOver();	//mouseover countries, so user can see the country where the mouse is over

		void leftClick();	//left click control

		void zoom(int zoomType);	//function to allow zooming
		void pan(SDL_Point *mPos, int motionX, int motionY);	//function to allow panning of the map
		void panLimiting();	//ensures the pan is limited within the relevant zone of the texture

	private:

		//world size
		int worldX, worldY;

		//viewport rect
		SDL_Rect vp; //display area
		SDL_Rect vpSrc; //allows panning and zooming

		//information box rect
		SDL_Rect infoBoxRect;

		//toolbar rect
		SDL_Rect toolbarRect;
		bool showToolBar;

		//bool for menubar windows
		bool newSimWindow, openSimWindow;

		#pragma region SIMULATION SETUP
		////////////////////////////////////////////////////////////////////////////////
		//simulation name
		char tempName[30] = "";
		char tempFilePath[MAX_PATH] = "";

		std::string simPath = "";

		float infectionRateSlider = 99.5f, 
			naturalDeathRateSlider = 0.5f,
			recoveryRateSlider = 0.5f, 
			infDeathRateSlider = 40.0f,
			zconversionRate = 0.3f, 
			zdeathRate = 1.0f, 
			zremoveRate = 1.0f,
			corpseDecayRate = 0.5f,
			reanimationRate = 10.0f;

		//is a zombie sim
		bool simulateZombies = true;

		//allowing different infection vectors
		bool allowLandInfect = true, allowSeaInfect = true, allowAirInfect = true;

		int simFrame = 0;

		////////////////////////////////////////////////////////////////////////////////
		#pragma endregion

		#pragma region APPEARANCE PREFERENCES
		////////////////////////////////////////////////////////////////////////////////
		//Appearance Preferences
		//bool if window should be open or not
		bool aPrefWin = false;

		//colour of the background
		ImVec4 bkgColour;
		////////////////////////////////////////////////////////////////////////////////
		#pragma endregion

		//the texture which will be drawn to the screen
		SDL_Texture *worldMap;
		
		//READING THE PIXEL COLOURS
		//texture sizes
		int wMapX, wMapY;
		
		#pragma region INFOBOX VARIABLES
		////////////////////////////////////////////////////////////////////////////////
		//collapse bools
		bool worldStatCollapse = true;
		bool countryStatCollapse = true;

		////////////////////////////////////////////////////////////////////////////////
		#pragma endregion
		
		#pragma region CONTROL VARIABLES
		////////////////////////////////////////////////////////////////////////////////
		//zoom values
		float zoomVal = 1, 
			maxZoom = 1, 
			minZoom = 0.1,
			zoomInterval = 0.025;

		bool run = false;


		////////////////////////////////////////////////////////////////////////////////
		#pragma endregion

		#pragma region GLOBAL DATA VARIABLES
		////////////////////////////////////////////////////////////////////////////////
		//current simulation name
		std::string simName = "";
		
		//current scenario name
		std::string scenarioName = "";
		
		//total number of countries in the world
		int totalCountries = 0;

		//total number of people in the world
		unsigned long long int worldPopulation = 0;

		//list of countries
		std::vector<Country> countryList;

		////////////////////////////////////////////////////////////////////////////////
		#pragma endregion


		#pragma region EVENT VARIABLES
		//////////////////////////////////////////////////////////////////////////////////////
		//current country being chosen
		std::vector<std::string> emptyVec;
		Country curCountry = Country("None", "None", 0, 0, 0, 0, 0, 0, 0, -1, -1, emptyVec, emptyVec, emptyVec);

		SDL_Color curCol = { 0, 0, 0 };
		Country scrollCountry = Country("None", "None", 0, 0, 0, 0, 0, 0, 0, -1, -1, emptyVec, emptyVec, emptyVec);

		bool sceDetails = false, simDetails = false, viewCountries = false, detailedCountry = false,
			editSim = false;
		//////////////////////////////////////////////////////////////////////////////////////
		#pragma endregion

		#pragma region VIEW COUNTRY DETAILS
		//////////////////////////////////////////////////////////////////////////////////////
		int currentCountry = -1;

		char editID[5] = "";
		char editCName[31] = "";
		int editR = 0,
			editG = 0,
			editB = 0;

		//country's population
		unsigned long long int editPopInt = 0, editGDPInt = 0, editMBInt = 0, editRSInt = 0;

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


		//borders
		std::vector<std::string> tempLandBorders, tempSeaLinks, tempAirLinks;


		//////////////////////////////////////////////////////////////////////////////////////
		#pragma endregion
};

/**
* GUI default contructor
* empty constructor which is temporary i.e. for when GUI is set up in main
*/
GUI::GUI()
{
	//temporarily empty but will then have values later on
}

/**
* GUI constructor
* the constructor used to give the GUI class parameters and be able to run
* 
* @param SDL_Renderer renderer
* @param int winX
* @param int winY
*/
GUI::GUI(SDL_Renderer *renderer, int winX, int winY)
{	
	//viewport location
	vp = { 0, 0, winX, winY };

	worldX = winX;
	worldY = winY;

	//info box setup
	infoBoxRect = { vp.w - vp.w / 4,
				0,
				vp.w / 4,
				vp.h };

	toolbarRect = { 0, 0, winX, 50 };

	//set zoom to 1
	//zoomVal = 1;

	//not initially open
	newSimWindow = false;
	openSimWindow= false;
	editSim = false;
	sceDetails = false;
	simDetails = false;
	viewCountries = false;
	detailedCountry = false;

	//pref window not open unless chosen
	aPrefWin = false;

	//toolbar
	showToolBar = true;

	//background colour
	bkgColour = ImColor(0, 0, 44);

	//default opening scenario
	if (!loadScenario(renderer, "..\\res\\scenarios\\world.sce"))
	{
		std::cout << "Error: Scenario cannot be loaded\n";
	}
	
	//default simulation setup
	simName = "world";
}

/**
* GUI destructor
*/
GUI::~GUI()
{
	
}

bool GUI::loadScenario(SDL_Renderer *renderer, std::string filePath)
{
	bool success = false;

	//reset values
	scenarioName = "";
	countryList.clear();
	totalCountries = 0;
	worldPopulation = 0;

	//DataHandler class to start the parsing
	DataHandler d = DataHandler(filePath);
	//tell the class what kind of file to load
	d.loadScenario();

	//load the worldmap textures
	SDL_Surface *worldSurf = IMG_Load(d.getTexturePath().c_str());
	worldMap = SDL_CreateTextureFromSurface(renderer, worldSurf);
	//remove the surface, no longer needed
	SDL_FreeSurface(worldSurf);

	//check if texture is loaded
	if (worldMap != NULL)
	{
		//reset world X and Y
		worldX = worldY = 0;

		//get texture size
		SDL_QueryTexture(worldMap, NULL, NULL, &wMapX, &wMapY);
		vpSrc = { 0, 0, wMapX, wMapY };

		//set the global scenario values
		scenarioName = d.getSceName();
		countryList = d.getCountryList();
		totalCountries = d.getCountryCount();
		worldPopulation = d.getTotalPop();

		success = true;
	}
	else
	{
		//warn about the map not being loaded
		std::cerr << "World Map not found!\n" << IMG_GetError() << std::endl;
	}

	

	return success;
}



/**
* menuBar
* function which heavily uses imgui to create the program's main menu bar as well as its options.
* The function also deals with the sub windows that the menu options generate as well as calls the info box function
*
* @param bool &appRun (uses the pointer to the bool value so that the quit option of the menu can shut down the program)
*/
void GUI::menuBar(bool &appRun, SDL_Renderer *renderer)
{
	//menu bar
	ImGui::BeginMainMenuBar();

	//File
	if (ImGui::BeginMenu("File"))
	{
		//Make a new simulation
		if (ImGui::MenuItem("New Simulation", "CTRL+N"))
		{
			newSimWindow = true;
		}

		//Open existing simulation
		if (ImGui::MenuItem("Open Simulation", "CTRL+O"))
		{
			openSim();
		}

		//Save current simulation
		if (ImGui::MenuItem("Save", "CTRL+S"))
		{
			//check if the file was already saved, if not then call save as
			if (simPath == "")
			{
				saveAs();
			}
			else
			{
				save();
			}
		}

		//Save current simulation with a different name

		if (ImGui::MenuItem("Save As"))
		{

		}

		ImGui::EndMenu();
	}

	//Edit
	if (ImGui::BeginMenu("Edit"))
	{
		if (ImGui::MenuItem("Edit Simulation"))
		{
			editSim = true;
		}

		if (ImGui::MenuItem("Change Scenario"))
		{
			char filename[MAX_PATH];
			OPENFILENAME ofn;
			ZeroMemory(&filename, sizeof(filename));
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = NULL;  // If you have a window to center over, put its HANDLE here
								   //only able to use image type files
			ofn.lpstrFilter = "ZEUS Scenario Files (*.sce)\0"
				"*.sce\0";
			ofn.lpstrFile = filename;
			ofn.nMaxFile = MAX_PATH;
			ofn.lpstrTitle = "Select simulation scenario";
			ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

			if (GetOpenFileName(&ofn))
			{
				strcpy(tempFilePath, filename);
				//std::cout << tempMapFilePath << "\n";

				loadScenario(renderer, tempFilePath);
			}
		}
		ImGui::EndMenu();
	}

	//View
	if (ImGui::BeginMenu("View"))
	{
		if (ImGui::MenuItem("Scenario details"))
		{
			sceDetails = true;
		}

		if (ImGui::MenuItem("Simulation details"))
		{
			simDetails = true;
		}

		if (ImGui::MenuItem("View all countries"))
		{
			viewCountries = true;
		}

		//toolbar has a tick if displayed
		if (showToolBar)
		{
			if (ImGui::MenuItem("Toolbar ", "", showToolBar))
			{
				showToolBar ^= 1;
			}
		}
		else
		{
			if (ImGui::MenuItem("Toolbar"))
			{
				showToolBar ^= 1;
			}
		}
		

		ImGui::EndMenu();
	}

	//Simulation
	if (ImGui::BeginMenu("Simulation"))
	{
		if (ImGui::MenuItem("Run"))
		{
			run = true;			
		}

		if (ImGui::MenuItem("Pause"))
		{
			run = false;
		}

		if (ImGui::MenuItem("Reset"))
		{
			resetSim();
		}

		ImGui::EndMenu();
	}

	//Preferences
	if (ImGui::BeginMenu("Preferences"))
	{
		//allows user to change simulation appearance
		if (ImGui::MenuItem("Appearance Preferences"))
		{
			aPrefWin = true;
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

	//editing the simulation
	if (editSim)
	{
		editSimVals();
	}

	//components of main menu bar
	//Appearance Preferences window
	if (aPrefWin)
	{
		//open appearance preferences window
		ImGui::Begin("Appearance Preferences", &aPrefWin, ImGuiWindowFlags_NoCollapse);
		ImGui::Separator();
		ImGui::Text("Background colour");
		ImGui::ColorEdit3("background colour", (float*)&bkgColour);
		ImGui::Separator();
		ImGui::End();
	}

	//simulation details
	if (simDetails)
	{
		ImGui::Begin("Simulation Details", &simDetails, ImGuiWindowFlags_NoCollapse);
		ImGui::Separator();

		//Simulation name
		ImGui::Text("Simulation Name: ");
		ImGui::SameLine();
		ImGui::Text("%s", simName.c_str());

		ImGui::End();
	}

	if (sceDetails)
	{
		ImGui::Begin("Scenario Details", &sceDetails, ImGuiWindowFlags_NoCollapse);
		ImGui::Separator();

		//Simulation name
		ImGui::Text("Scenario Name: ");
		ImGui::SameLine();
		ImGui::Text("%s", scenarioName.c_str());

		ImGui::Separator();

		//number of countries
		ImGui::Text("Number of countries: ");
		ImGui::SameLine();
		ImGui::Text("%d", totalCountries);

		//total population in scenario
		ImGui::Text("Total Scenario Population: ");
		ImGui::SameLine();
		ImGui::Text("%llu", worldPopulation);

		ImGui::End();
	}

	if (viewCountries)
	{
		//make the window
		ImGui::Begin("View Country", &viewCountries, ImGuiWindowFlags_NoCollapse);
		ImGui::SetWindowSize(ImVec2(750, 500));
		ImGui::BeginColumns("View Countries", 4, NULL);

		//column titles
		ImGui::Text("Country ID");
		ImGui::NextColumn();

		ImGui::Text("Country Name");
		ImGui::NextColumn();

		ImGui::Text("View Country");
		ImGui::SameLine();
		helpMarker("Press View to view the country data");
		ImGui::NewLine();
		ImGui::NextColumn();

		ImGui::Text("Initially Infected");
		ImGui::SameLine();
		helpMarker("Click to set the country as an initial infector");
		ImGui::NewLine();
		if (ImGui::Button("Reset All"))
		{
			for (int i = 0; i < countryList.size(); i++)
			{
				countryList[i].infected = false;
			}
		}
		ImGui::SameLine();
		helpMarker("Reset All removes the infected status for all countries");
		ImGui::NewLine();
		ImGui::NextColumn();

		//add all information from the country list
		for (int count = 0; count < countryList.size(); count++)
		{
			//show the ID in the first column
			ImGui::Text(countryList[count].getID().c_str());
			ImGui::NextColumn();

			//show country name
			std::string cNameStr = countryList[count].getCountryName();
			std::replace(cNameStr.begin(), cNameStr.end(), '-', ' ');
			ImGui::Text(cNameStr.c_str());
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
				editPopInt = countryList[count].getPopulation();

				//set gdp
				editGDPInt = countryList[count].getGDP();

				//set military budget
				editMBInt = countryList[count].getMilitaryBudget();

				//set research budget
				editRSInt = countryList[count].getResearchBudget();

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

				//opens the detailed menu
				detailedCountry ^= 1;
			}
			ImGui::NextColumn();

			//checkbox to set the infected country
			std::string checkboxLabel = "##checkbox" + countryList[count].getID();
			ImGui::Checkbox(checkboxLabel.c_str(), &countryList[count].infected);
			

			ImGui::NextColumn();
		}

		ImGui::EndColumns();

		ImGui::End();
	}

	//opens a window that shows all country details
	if (detailedCountry)
	{
		//new window to view details of the country
		ImGui::Begin("View Country Detail", &detailedCountry, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
		ImGui::SetWindowSize(ImVec2(500, 600), NULL);

		ImGui::Separator();

		//country ID
		ImGui::BeginColumns("##countrydetails", 2);
		ImGui::Text("Country ID:");
		ImGui::NextColumn();
		ImGui::Text("%s", editID);

		//country name
		ImGui::NextColumn();
		ImGui::Text("Country Name:");
		ImGui::NextColumn();
		std::string nameStr = editCName;
		std::replace(nameStr.begin(), nameStr.end(), '-', ' ');
		ImGui::Text("%s", nameStr.c_str());
		ImGui::NewLine();
		ImGui::NextColumn();

		//RGB colours
		ImGui::Separator();
		ImGui::Text("Country Colour Identifier");
		ImGui::NextColumn();
		helpMarker("The unique colour for each country territory, in RGB format.");
		ImGui::NewLine();
		ImGui::NextColumn();

		ImGui::Text("Red:");
		ImGui::NextColumn();
		ImGui::Text("%d", editR);
		ImGui::NextColumn();

		ImGui::Text("Green:");
		ImGui::NextColumn();
		ImGui::Text("%d", editG);
		ImGui::NextColumn();


		ImGui::Text("Blue:");
		ImGui::NextColumn();
		ImGui::Text("%d", editB);
		ImGui::NextColumn();
		ImGui::NewLine();
		ImGui::Separator();

		//attributes
		ImGui::Text("Country Attributes");
		ImGui::NextColumn();
		helpMarker("The country's different attribute values. These values are used in the simulation to determine how the disease spreads.");
		ImGui::NewLine();
		ImGui::NextColumn();

		//population
		ImGui::Text("Population:");
		ImGui::NextColumn();
		ImGui::Text("%llu", editPopInt);
		ImGui::NextColumn();

		//GDP
		ImGui::Text("GDP:");
		ImGui::SameLine();
		helpMarker("In million USD (US Dollars)");
		ImGui::NextColumn();
		ImGui::Text("%llu", editGDPInt);
		ImGui::NextColumn();

		//military budget
		ImGui::Text("Military Budget:");
		ImGui::SameLine();
		helpMarker("In million USD (US Dollars)");
		ImGui::NextColumn();
		ImGui::Text("%llu", editMBInt);
		ImGui::NextColumn();

		//research budget
		ImGui::Text("Research Budget:");
		ImGui::SameLine();
		helpMarker("In million USD (US Dollars)");
		ImGui::NextColumn();
		ImGui::Text("%llu", editRSInt);
		ImGui::NewLine();
		ImGui::NextColumn();
		ImGui::Separator();

		//climate
		ImGui::Text("Country Climate");
		ImGui::NextColumn();
		helpMarker("The country's climate. The climate affects  diseases differently according to the climate.");
		ImGui::NewLine();
		ImGui::NextColumn();

		//temperature
		ImGui::Text("Temperature:");
		ImGui::NextColumn();
		if (ehotTemp)
			ImGui::Text("Hot");
		if (ecoldTemp)
			ImGui::Text("Cold");
		if (eneutralTemp)
			ImGui::Text("Neutral");


		ImGui::NextColumn();

		//humidity
		ImGui::Text("Humidity:");
		ImGui::NextColumn();
		if (edryHum)
			ImGui::Text("Dry");
		if (ewetHum)
			ImGui::Text("Wet");
		if (eneutralHum)
			ImGui::Text("Neutral");

		ImGui::NewLine();
		ImGui::NextColumn();
		ImGui::EndColumns();
		ImGui::Separator();
		ImGui::NewLine();

		//print out the neighbours
		if (tempLandBorders.size() > 0)
		{
			if (ImGui::TreeNode("Land Borders"))
			{
				for (int i = 0; i < tempLandBorders.size(); i++)
				{
					for (int j = 0; j < countryList.size(); j++)
					{
						if (countryList[j].getID() == tempLandBorders[i])
						{
							std::string printout = "[" + tempLandBorders[i] + "] - " + countryList[j].getCountryName();
							ImGui::Text(printout.c_str());
						}
					}
				}

				ImGui::TreePop();
			}
		}

		ImGui::NewLine();

		if (tempSeaLinks.size() > 0)
		{
			if (ImGui::TreeNode("Sea Links"))
			{
				for (int i = 0; i < tempSeaLinks.size(); i++)
				{
					for (int j = 0; j < countryList.size(); j++)
					{
						if (countryList[j].getID() == tempSeaLinks[i])
						{
							std::string printout = "[" + tempSeaLinks[i] + "] - " + countryList[j].getCountryName();
							ImGui::Text(printout.c_str());
						}
					}
				}

				ImGui::TreePop();
			}
		}

		ImGui::NewLine();

		if (tempAirLinks.size() > 0)
		{
			if (ImGui::TreeNode("Air Links"))
			{
				for (int i = 0; i < tempAirLinks.size(); i++)
				{
					for (int j = 0; j < countryList.size(); j++)
					{
						if (countryList[j].getID() == tempAirLinks[i])
						{
							std::string printout = "[" + tempAirLinks[i] + "] - " + countryList[j].getCountryName();
							ImGui::Text(printout.c_str());
						}
					}
				}

				ImGui::TreePop();
			}
		}

		ImGui::End();
	}

	if (showToolBar)
	{
		toolBar();
	}

	//if the user wants to create a new simulation
	newSim(renderer);

	if (run)
	{
		simulate();
	}
}

/**
* infoBox
* function which uses imgui to display the options that the user has done i.e. the chosen country's information
*/
void GUI::infoBox()
{	
	//update currentCountry
	for (int i = 0; i < countryList.size(); i++)
	{
		if (curCountry.getID() == countryList[i].getID())
		{
			curCountry = countryList[i];
		}
	}

	//make the side bar
	ImGui::Begin("infobox", NULL, 
		ImGuiWindowFlags_NoCollapse
		| ImGuiWindowFlags_NoTitleBar
		| ImGuiWindowFlags_NoMove
		| ImGuiWindowFlags_NoResize);
	//set the side bar position, which is on the infobox rect
	ImGui::SetWindowPos("infobox", ImVec2(infoBoxRect.x, infoBoxRect.y));
	//set the side bar size
	ImGui::SetWindowSize("infobox", ImVec2(infoBoxRect.w, infoBoxRect.h));

	//running sim
	ImGui::Separator();
	ImGui::Separator();
	ImGui::NewLine();
	ImGui::Text("Simulation status: ");
	ImGui::SameLine();
	ImGui::Text(run ? "Running" : "Paused");

	if (ImGui::Button(ICON_FA_PLAY, ImVec2(infoBoxRect.w / 3 - 10, 32)))
	{
		run = true;
	}
	tooltip("Run Simulation");
	ImGui::SameLine(); 
	
	if (ImGui::Button(ICON_FA_PAUSE, ImVec2(infoBoxRect.w / 3 - 10, 32)))
	{
		run = false;
	}
	tooltip("Pause Simulation");
	ImGui::SameLine(); 
	
	if (ImGui::Button(ICON_FA_REFRESH, ImVec2(infoBoxRect.w / 3 - 10, 32)))
	{
		resetSim();
	}
	tooltip("Reset Simulation");

	ImGui::NewLine();
	ImGui::Separator();
	ImGui::Separator();

	#pragma region WORLD STATISTICS
	///////////////////////////////////////////////////////////////////////////////////////////////
	//display the map statistics
	if (ImGui::CollapsingHeader("World Statistics"))
	{
		//total countries
		ImGui::Text("Number of Countries: %d", totalCountries);
		//total world population
		ImGui::TextWrapped("Total World Population: %llu", worldPopulation);
	}
	
	///////////////////////////////////////////////////////////////////////////////////////////////
	#pragma endregion

	#pragma region SELECTED COUNTRY
	///////////////////////////////////////////////////////////////////////////////////////////////
	//display the data of the selected country
	if (ImGui::CollapsingHeader("Selected Country"))
	{
		ImGui::Separator();
		ImGui::Separator();
		//country ID
		ImGui::Text("ID: %s", curCountry.getID().c_str());
		//country Name
		ImGui::TextWrapped("Name: %s", curCountry.getCountryName().c_str());
		ImGui::Separator();
		ImGui::Separator();

		//header for country statistics
		if (ImGui::CollapsingHeader("Country Statistics"))
		{
			//country Population
			ImGui::NewLine();
			ImGui::TextWrapped("Population: %d", curCountry.getPopulation());
			ImGui::NewLine();

			if (ImGui::CollapsingHeader("Simulation Statistics"))
			{
				ImGui::TextWrapped("Healthy: %d", curCountry.getHealthyPop());
				ImGui::NewLine();

				ImGui::TextWrapped("Infected: %d", curCountry.getInfectedPop());
				ImGui::NewLine();

				ImGui::TextWrapped("Dead: %d", curCountry.getDeadPop());
				ImGui::NewLine();

				if (simulateZombies)
				{
					ImGui::TextWrapped("Zombie: %d", curCountry.getZombiePop());
					ImGui::NewLine();

					ImGui::Text("Removed");
					ImGui::SameLine();
					helpMarker("The individuals that can no longer be animated therefore removed from the simulation");
					ImGui::SameLine();
					ImGui::TextWrapped(": %d", curCountry.getRemovedPop());
					ImGui::NewLine();
				}
			}			

			//country economy
			if (ImGui::CollapsingHeader("Country Economy"))
			{
				ImGui::TextWrapped("All values in Million US Dollars ($)");
				ImGui::Separator();
				ImGui::Separator();
				ImGui::NewLine();

				//country GDP
				ImGui::TextWrapped("Gross Domestic Product: %d", curCountry.getGDP());

				//country military spending
				ImGui::TextWrapped("Military Spending: %d", curCountry.getMilitaryBudget());

				//country research budget
				ImGui::TextWrapped("Research Budget: %d", curCountry.getResearchBudget());
			}

			//country climate
			if (ImGui::CollapsingHeader("Country Climate"))
			{
				//different output depending on climate type
				//switch case is more effective than nested if-elses

				helpMarker("The Climate conditions of the country");
				ImGui::NewLine();

				//country temprature
				std::string temperature = "Not Set";
				switch (curCountry.getTemperature())
				{
					//neutral
					case 0: { temperature = "Neutral"; }
					break;

					//warm
					case 1: { temperature = "Warm"; }
					break;

					//cold
					case 2: { temperature = "Cold"; }
					break;

					default: { temperature = "Temperature not set"; }
					break;
				}
				//show to sidebar
				ImGui::Text("Temperature: %s", temperature.c_str());

				ImGui::NewLine();

				//country humidity
				std::string humidity = "Not Set";
				switch (curCountry.getHumidity())
				{
					case 0: { humidity = "Neutral"; }
					break;
				
					case 1: { humidity = "Wet"; }
					break;
				
					case 2: { humidity = "Dry"; }
					break;

					default: { humidity = "Humidity not set"; }
					break;
				}
				//show to sidebar
				ImGui::Text("Humidity: %s", humidity.c_str());
				ImGui::NewLine();
			}

			//country links
			if (ImGui::CollapsingHeader("Country External Links"))
			{
				helpMarker("Shows whether or not a country is linked via land, sea or air to other countries");

				//get all links now
				//so that the check is only run once

				//get the land borders
				std::vector<std::string> tempLand = curCountry.getLandBorders();

				//get sea links
				std::vector<std::string> tempSea = curCountry.getSeaLinks();

				//get air links
				std::vector<std::string> tempAir = curCountry.getAirLinks();

				//display that the country has land borders
				bool hasLandBorder = false, hasSeaLink = false, hasAirLink = false;

				if (tempLand.size() > 0) { hasLandBorder = true; }
				if (tempSea.size() > 0) { hasSeaLink = true; }
				if (tempAir.size() > 0) { hasAirLink = true; }

				ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);

				ImGui::Text("Land Borders:\t ");
				ImGui::SameLine();
				ImGui::Checkbox("##landDisplay", &hasLandBorder);

				ImGui::Text("Sea Links:\t\t");
				ImGui::SameLine();
				ImGui::Checkbox("##seaDisplay", &hasSeaLink);

				ImGui::Text("Air Links:\t\t");
				ImGui::SameLine();
				ImGui::Checkbox("##airDisplay", &hasAirLink);

				ImGui::PopItemFlag();
			}
		}






	}

	///////////////////////////////////////////////////////////////////////////////////////////////
#pragma endregion

//std::cout << curCountry.getID() << ", " << curCountry.getCountryName() << ", " << curCountry.getPopulation() << std::endl;

	ImGui::End();

}

/**
* toolBar
* function which displays the toolbar for easier controls
*/
void GUI::toolBar()
{
	ImGui::Begin("toolbar", NULL,
		ImGuiWindowFlags_NoCollapse
		| ImGuiWindowFlags_NoTitleBar
		| ImGuiWindowFlags_NoMove
		| ImGuiWindowFlags_NoResize
		| ImGuiWindowFlags_NoScrollbar);
	//set the side bar position, which is on the infobox rect
	ImGui::SetWindowPos("toolbar", ImVec2(toolbarRect.x, toolbarRect.y));
	//set the side bar size
	ImGui::SetWindowSize("toolbar", ImVec2(toolbarRect.w, toolbarRect.h));

	//New Simulation Button
	if (ImGui::Button(ICON_FA_FILE, ImVec2(30, 30)))
	{
		newSimWindow = true;
	}
	tooltip("New Simulation");
	ImGui::SameLine();

	//Open Simulation Button
	if (ImGui::Button(ICON_FA_FOLDER_OPEN, ImVec2(30, 30)))
	{
		openSim();
	}
	tooltip("Open Simulation");
	ImGui::SameLine();

	//Save Simulation Button
	if (ImGui::Button(ICON_FA_FLOPPY_O, ImVec2(30, 30)))
	{

		std::cout << simPath << std::endl;

		//check if the file was already saved, if not then call save as
		if (simPath == "")
		{
			saveAs();
		}
		else
		{
			save();
		}
	}
	tooltip("Save Simulation");
	ImGui::SameLine();

	ImGui::Text("Map View: ");

	ImGui::SameLine();

	//combo box information
	const char *options[] =
	{"Country Information", "Infection Spread", "Zombie Spread", "Sandwich Spread"};
	static int mapViewCombo = 0;
	ImGui::PushItemWidth(200);
	ImGui::Combo("##mapviewcombo", &mapViewCombo, options, IM_ARRAYSIZE(options));
	


	ImGui::End();
}

/**
* newSim
* function that uses an imgui window to allow the user to create a new simulation
*/
void GUI::newSim(SDL_Renderer *renderer)
{
	//open new simulation window
	if (newSimWindow)
	{
		ImGui::Begin("New Simulation", &newSimWindow, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
		ImGui::SetWindowSize("NewSimWin", ImVec2(600, 500));

		ImGui::Separator();

		//Sim name label
		ImGui::Text("Simulation Name: ");
		ImGui::SameLine();
		helpMarker("The name of the simulation. Maximum 30 characters and no spaces.");
		//Sim name input
		ImGui::InputText("##simname", tempName, sizeof(tempName), ImGuiInputTextFlags_CharsNoBlank);

		//Simulation scenario
		ImGui::Text("Simulation Scenario: ");
		ImGui::SameLine();
		helpMarker("The scenario the simulation is to be applied to. Not required\n"
			"to set up the simulation, however is required to run the simulation");

		ImGui::InputText("##scenariopath", tempFilePath, sizeof(tempFilePath));
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
			ofn.lpstrFilter = "ZEUS Scenario Files (*.sce)\0"
				"*.sce\0";
			ofn.lpstrFile = filename;
			ofn.nMaxFile = MAX_PATH;
			ofn.lpstrTitle = "Select simulation scenario";
			ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

			if (GetOpenFileName(&ofn))
			{
				strcpy(tempFilePath, filename);
				//std::cout << tempMapFilePath << "\n";
			}
		}


		ImGui::Separator();

		if (ImGui::Button("Create Simulation", ImVec2(ImGui::GetWindowWidth(), 20)))
		{
			bool acceptName = false, acceptScenario = false;

			//check the simulation name
			if (strcmp(tempName, "") != 0)
			{
				acceptName = true;
			}

			//check if the scenario is valid
			if (strcmp(tempFilePath, "") == 0)
			{
				//valid if empty
				acceptScenario = true;
			}
			else
			{
				//check if the file exists
				std::ifstream infile(tempFilePath);
				if (infile.good())
				{
					//std::cout << "File exists\n";
					acceptScenario = true;
				}
			}

			//check if valid
			if (acceptName && acceptScenario)
			{
				//simulation name
				simName = tempName;

				//load the scenario, should be empty if no scenario input
				loadScenario(renderer, tempFilePath);

				
				//reset the new simulator creator
				resetNewSim();
			}
		}

		ImGui::End();
	}
}

void GUI::resetNewSim()
{
	strcpy(tempName, "");
	strcpy(tempFilePath, "");

	newSimWindow = false;
}

/**
* openSim
* function that uses an imgui window to allow the user to open an existing simulation
*/
void GUI::openSim()
{
	char filename[MAX_PATH];
	OPENFILENAME ofn;
	ZeroMemory(&filename, sizeof(filename));
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;  // If you have a window to center over, put its HANDLE here
	ofn.lpstrFilter = "ZEUS Simulation Files (*.zsim)\0"
		"*.zsim\0";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = "Open Simulation";
	ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

	if (GetOpenFileName(&ofn))
	{
		simPath = filename;
		//std::cout << tempMapFilePath << "\n";
	}
}

void GUI::save()
{

}

void GUI::saveAs()
{

}

void GUI::editSimVals()
{
	ImGui::Begin("Edit Simulation", &editSim, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
	ImGui::SetWindowSize(ImVec2(400, 500));
	
	ImGui::Separator();
	ImGui::BeginColumns("##checkboxSeparator", 2, ImGuiColumnsFlags_NoBorder | ImGuiColumnsFlags_NoResize);

	ImGui::Text("Zombies");
	ImGui::SameLine();
	helpMarker("Uncheck to disable the simulation of zombies, making the simulation purely for spread of disease.");
	ImGui::NextColumn();
	ImGui::Checkbox("##zombieOption", &simulateZombies);
	
	ImGui::EndColumns();
	ImGui::Separator();

	//options for simulated disease
	if (ImGui::TreeNode("Disease Settings"))
	{
		//infection rate of disease
		ImGui::Text("Infection rate");
		ImGui::SameLine();
		helpMarker("Determines how fast the infection spreads across the simulation");
		ImGui::SliderFloat("##infectionrateslider", &infectionRateSlider, 0.0f, 100.0f, "%.2f%%");
		ImGui::NewLine();

		naturalDeathRateSlider = 100 - infectionRateSlider;
		//limit values
		if (infectionRateSlider > 100) { infectionRateSlider = 100; }
		if (infectionRateSlider < 0) { infectionRateSlider = 0; }

		//death rate from infection
		ImGui::Text("Natural death rate");
		ImGui::SameLine();
		helpMarker("Rate at which individuals die from natural causes.\n"
		"Maximum value is 5%");
		ImGui::SliderFloat("##naturaldeathslider", &naturalDeathRateSlider, 0.0f, 100.0f, "%.2f%%");
		ImGui::NewLine();

		if (naturalDeathRateSlider > 5) { naturalDeathRateSlider = 2; }
		if (naturalDeathRateSlider < 0) { naturalDeathRateSlider = 0; }
		infectionRateSlider = 100 - naturalDeathRateSlider;
		

		//recovery rate
		ImGui::Text("Recovery rate");
		ImGui::SameLine();
		helpMarker("Rate at which individuals recover from the disease.\n"
			"Maximum value is 5% if zombies are to be simulated");
		ImGui::SliderFloat("##recovrateslider", &recoveryRateSlider, 0.0f, 5.0f, "%.2f%%");
		ImGui::NewLine();

		if (!simulateZombies) { infDeathRateSlider = 100 - recoveryRateSlider; }
		if (recoveryRateSlider > 5.0f) { recoveryRateSlider = 5.0f; }
		if (recoveryRateSlider < 0) { recoveryRateSlider = 0.0f; }

		//infection death rate
		ImGui::Text("Infection death rate");
		ImGui::SameLine();
		helpMarker("Rate at which individuals die of the disease");
		ImGui::SliderFloat("##infdeathrateslider", &infDeathRateSlider, 0.0f, 100.0f - recoveryRateSlider, "%.2f%%");

		if (!simulateZombies) { recoveryRateSlider = 100 - infDeathRateSlider; }
		if (infDeathRateSlider > 100.0f - recoveryRateSlider) { infDeathRateSlider = 100.0f - recoveryRateSlider; }
		if (infDeathRateSlider < 0.0f) { infDeathRateSlider = 0.0f; }

		if (simulateZombies)
		{
			if (ImGui::TreeNode("Zombie Settings"))
			{
				//rate of infected turning into zombies
				ImGui::Text("Zombie conversion rate");
				ImGui::SameLine();
				helpMarker("Rate at which infected become zombies. This also affects death rate.");
				ImGui::SliderFloat("##zconversionrateslider", &zconversionRate, 0.0f, 100.0f, "%.2f%%");
				ImGui::NewLine();

				zconversionRate = 100 - (recoveryRateSlider + infDeathRateSlider);

				//death rate of zombies
				ImGui::Text("Zombie elimination rate");
				ImGui::SameLine();
				helpMarker("Rate at which zombies are TEMPORARILY removed");
				ImGui::SliderFloat("##zdeathrateslider", &zdeathRate, 0.0f, 10.0f, "%.2f%%");
				ImGui::NewLine();

				if (zdeathRate > 10.0f) { zdeathRate = 10.0f; }
				if (zdeathRate < 0.0f) { zdeathRate = 0.0f; }

				//removal rate of zombies
				ImGui::Text("Zombie removal rate");
				ImGui::SameLine();
				helpMarker("Rate at which zombies are PERMANENTLY removed");
				ImGui::SliderFloat("##zremoverateslider", &zremoveRate, 0.0f, 10.0f, "%.2f%%");

				if (zremoveRate > 10.0f) { zremoveRate = 10.0f; }
				if (zremoveRate < 0.0f) { zremoveRate = 0.0f; }

				ImGui::Text("Decay rate");
				ImGui::SameLine();
				helpMarker("Rate at which dead entities decay.\n"
					"Used to determine how fast zombies die out in a simulation");
				ImGui::SliderFloat("##decayrateslider", &corpseDecayRate, 0.0f, 2.5f, "%.2f%%");

				if (corpseDecayRate > 2.5f) { corpseDecayRate = 2.5f; }
				if (corpseDecayRate < 0.0f) { corpseDecayRate = 0.0f; }

				ImGui::Text("Reanimation rate");
				ImGui::SameLine();
				helpMarker("Rate at which dead infected are reanimated into zombies");
				ImGui::SliderFloat("##reanimatuinslider", &reanimationRate, 0.0f, 100.0f, "%.2f%%");

				if (reanimationRate > 100.0f) { reanimationRate = 100.0f; }
				if (reanimationRate < 0.0f) { reanimationRate = 0.0f; }

				//rate of infected dying
				ImGui::TreePop();
			}
		}		

		ImGui::TreePop();
	}

	//allowing infection of other countries via specific connections
	if (ImGui::TreeNode("Country Border Settings"))
	{
		ImGui::Text("Uncheck any of the settings to stop the simulation spreading via these country connections.");
		helpMarker(
			" Note that removing the ability to spread via certain connections may make it impossible to infect countries "
			" more speifically, islands (if the sea links option is disabled)");
		ImGui::NewLine();

		ImGui::BeginColumns("##checkboxSeparator", 2, ImGuiColumnsFlags_NoBorder | ImGuiColumnsFlags_NoResize);

		ImGui::Text("Land Borders");
		ImGui::NextColumn();
		ImGui::Checkbox("##landborderUse", &allowLandInfect);
		ImGui::NextColumn();

		ImGui::Text("Sea Links");
		ImGui::NextColumn();
		ImGui::Checkbox("##seaLinkUse", &allowSeaInfect);
		ImGui::NextColumn();

		ImGui::Text("Air Links");
		ImGui::NextColumn();
		ImGui::Checkbox("##airLinkUse", &allowAirInfect);
		ImGui::NextColumn();


		ImGui::EndColumns();


		ImGui::TreePop();
	}

	ImGui::End();
}

void GUI::simulate()
{
	bool noInfectedError = true;

	//check if any country(ies) have any infected population
	for (int i = 0; i < countryList.size(); i++)
	{
		if (countryList[i].infected > 0)
		{
			noInfectedError = false;
			break;
		}
	}

	//show an error that no infected country is set
	if (noInfectedError)
	{
		ImGui::OpenPopup("Cannot run simulation");
	}
	else
	{
		for (int i = 0; i < countryList.size(); i++)
		{
			countrySim(i);
		}

		//increment simulation frame
		simFrame++;
	}

	//show error
	bool error = true;
	if (ImGui::BeginPopupModal("Cannot run simulation", &error, ImGuiWindowFlags_NoResize))
	{
		ImGui::SetWindowSize(ImVec2(400, 150));

		if (noInfectedError)
		{
			ImGui::Text("No country is infected\n");
		}

		//close popup
		ImGui::Separator();
		if (ImGui::Button("Close", ImVec2(ImGui::GetWindowWidth(), 20)))
		{
			ImGui::CloseCurrentPopup();
			run = false;
		}
		ImGui::Separator();
		ImGui::EndPopup();
	}
}

void GUI::countrySim(int countryNum)
{
	countryList[countryNum].simulate(
		simulateZombies,
		simFrame,
		infectionRateSlider,
		naturalDeathRateSlider,
		recoveryRateSlider,
		infDeathRateSlider,
		zconversionRate,
		zdeathRate,
		zremoveRate,
		corpseDecayRate,
		reanimationRate,
		allowLandInfect,
		allowSeaInfect,
		allowAirInfect,
		countryList);
}

void GUI::resetSim()
{
	//reset all country values
	for (int i = 0; i < countryList.size(); i++)
	{
		countryList[i].resetSimVal();
	}

	//reset simulation frame
	simFrame = 0;

	run = false;
}

/**
* render
* function that draws all the items to the screen
*
* @param SDL_Window window
* @param SDL_Renderer renderer
*/
void GUI::render(SDL_Window *window, SDL_Renderer *renderer)
{	
	//update vp size
	vp.y = ((int)ImGui::GetIO().DisplaySize.y) * 0.125;
	vp.w = ((int)ImGui::GetIO().DisplaySize.x) * 0.75;
	vp.h = ((int)ImGui::GetIO().DisplaySize.y) * 0.75;
	
	//update toolbar size
	toolbarRect.x = 0;
	toolbarRect.y = 20;
	toolbarRect.w = ((int)ImGui::GetIO().DisplaySize.x);
	toolbarRect.h = 50;

	//update info box rect
	infoBoxRect.x = vp.w;
	infoBoxRect.y = 15 + toolbarRect.h;
	infoBoxRect.w = ((int)ImGui::GetIO().DisplaySize.x) / 4;
	infoBoxRect.h = ((int)ImGui::GetIO().DisplaySize.y) - (toolbarRect.h + 15);

	//gets the world size
	SDL_GetWindowSize(window, &worldX, &worldY);
	//std::cout << worldX << ", " << worldY << std::endl;
	//std::cout << vp.x << ", " << vp.y << std::endl;

	//clear the screen
	SDL_SetRenderDrawColor(renderer,
		bkgColour.x * 255.0f,
		bkgColour.y * 255.0f,
		bkgColour.z * 255.0f,
		bkgColour.w * 255.0f);
	SDL_RenderClear(renderer);

	//get the user mouse over
	mouseOver();

	//link viewports to the renderer
	SDL_RenderSetViewport(renderer, &vp);

	//render the world map
	SDL_RenderCopy(renderer, worldMap, &vpSrc, NULL);

	//render the IMGUI elements
	glUseProgram(0);
	ImGui::Render();

	//update the screen
	SDL_RenderPresent(renderer);
}

/**
* ctrlN
* function called when the control + N shortcut is used.
* shortcut is to make a new simulation
*/
void GUI::ctrlN()
{
	newSimWindow = true;
}

/**
* ctrlO
* function called when the control + O shortcut is used.
* shortcut is used to open an existing simulation
*/
void GUI::ctrlO()
{
	openSimWindow = true;
}

void GUI::spaceBar()
{
	run ^= 1;
}

/**
* mouseOver
* function that shows to the user the current country that is being moused over
*/
void GUI::mouseOver()
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
	{
		//std::cout << "Unable to get screen context\n";
	}
		

	if (!b)
	{
		//std::cout << "Unable to get cursor position\n";
	}
	
	// Retrieve the color at that position
	colour = GetPixel(hDC, p.x, p.y);
	if (colour == CLR_INVALID)
	{
		//std::cout << "Obtained colour invalid\n";
	}
		

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
	if (countryFound)
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(450.0f);

		if (countryFound)
		{
			//get country name
			ImGui::Text("[%s] - %s", scrollCountry.getID().c_str(), scrollCountry.getCountryName().c_str());
		}

		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

/**
leftClick
When called, the function reads the screen and uses the pixel under the mouse cursor to determine if the user has selected a country
*/
void GUI::leftClick()
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
}

/**
* zoom
* function that determines the type of zoom that is done and then changes the vpSrc rect to change what is to be shown on the screen.
*
* @param int zoomType
*/
void GUI::zoom(int zoomType)
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
void GUI::pan(SDL_Point *mPos, int motionX, int motionY)
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

/**
* panLimiting
* function that ensures that the user remains within the bounds of the image i.e.
* prevents user from being lost while panning
*/
void GUI::panLimiting()
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

