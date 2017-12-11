#pragma once
//IMGUI
#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_sdl.h"
#include "stb_rect_pack.h"
#include "stb_textedit.h"
#include "stb_truetype.h"

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

//data handling (loadin and saving)
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>
#include <algorithm>

//other items
#include "Country.h"

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
		int loadCountryData(std::string filePath);

		//draw menu bar
		void menuBar(bool &appRun);

		//info box
		void infoBox();

		//menu bar functions
		void newSim();
		void openSim();

		//render items
		void render(SDL_Window *window, SDL_Renderer *renderer);

		//CONTROLS AND SHORTCUTS
		void ctrlN();
		void ctrlO();

		void leftClick();


	private:

		//world size
		int worldX, worldY;

		//viewport rect
		SDL_Rect vp;

		//information box rect
		SDL_Rect infoBoxRect;

		//viewport zoom
		//float zoomVal; //current zoom
		float zoomAmount = 0.1; //increment zoom by this amount
		float panSpeed = 20;
		float maxZoomIn = 4, maxZoomOut = 0.9;

		//bool for menubar windows
		bool newSimWindow, openSimWindow;

		#pragma region APPEARANCE PREFERENCES
		////////////////////////////////////////////////////////////////////////////////
		//Appearance Preferences
		//bool if window should be open or not
		bool aPrefWin;

		//bool to show colour map or not
		bool showColourMap;

		//colour of the background
		ImVec4 bkgColour;
		////////////////////////////////////////////////////////////////////////////////
		#pragma endregion

		//the texture which will be drawn to the screen
		SDL_Texture *worldMap;
		
		//READING THE PIXEL COLOURS
		//texture sizes
		int wMapX, wMapY;
		

		//list of countries
		std::vector<Country> countryList;

		//current country being chosen
		Country curCountry = Country("None", "None", 0, 0, 0, 0);
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

	//set zoom to 1
	//zoomVal = 1;

	//not initially open
	newSimWindow = false;
	openSimWindow= false;

	//pref window not open unless chosen
	aPrefWin = false;

	//colour map default to not displayed
	showColourMap = false;

	//background colour
	bkgColour = ImColor(0, 0, 44);

	//load the worldmap textures
	SDL_Surface *worldSurf = IMG_Load("res\\img\\worldHigh.png");
	worldMap = SDL_CreateTextureFromSurface(renderer, worldSurf);
	//remove the surface, no longer needed
	SDL_FreeSurface(worldSurf);
	//check if texture is loaded
	if (worldMap == NULL)
	{
		std::cerr << "World Map not found!\n" << IMG_GetError() << std::endl;
		worldX = worldY = 0;
	}

	//get texture size
	SDL_QueryTexture(worldMap, NULL, NULL, &wMapX, &wMapY);

	//load the country data
	if (loadCountryData("res\\dat\\countrydata.dat") < 0)
	{
		std::cout << "Country File not loaded\n";
	}
}

/**
* GUI destructor
*/
GUI::~GUI()
{
	
}

/**
* loadCountryData
* function which loads the file path given to it.
* the countries loaded are then instantiated and added to the country list
*
* @param string filePath
* @return loaded (0 = success, -1 = failed)
*/
int GUI::loadCountryData(std::string filePath)
{
	//if the file was successfully loaded or not
	int loaded = 0;

	//vectors that store strings for data
	std::vector<std::string> cID;
	std::vector<std::string> cName;
	std::vector<std::string> cRed;
	std::vector<std::string> cGreen;
	std::vector<std::string> cBlue;
	std::vector<std::string> cPopulation;
	
	//line buffer
	std::string lineBuffer;

	//get the country data file
	std::ifstream cData;
	cData.open(filePath);

	//error checking
	if (cData.is_open())
	{
		//counts the number of loaded countries
		int countries = 0;

		//loop until end of file
		while (!cData.eof())
		{
			//send the retrieved line to the line buffer
			cData >> lineBuffer;

			//string stream to process the line
			std::stringstream ss;
			ss.str(lineBuffer);

			//store processed line
			std::string processedData;

			//actual country data
			std::string countryData[6];

			//separator for each line
			char delimiter = ',';

			//counts the number of items in the line
			int count = 0;

			//loop to read the entire line
			while (std::getline(ss, processedData, delimiter))
			{
				//store the processed data in the appropriate array location
				//std::replace(processedData.begin(), processedData.end(), '_', ' ');
				countryData[count] = processedData;

				if (count == 5)
				{
					//for debugging if the data was input correctly
					/*std::cout <<
					"ID: " << countryData[0] << std::endl <<
					"Name: " << countryData[1] << std::endl <<
					"Red: " << countryData[2] << std::endl <<
					"Green: " << countryData[3] << std::endl <<
					"Blue: " << countryData[4] << std::endl <<
					"Population: " << countryData[5] << std::endl;*/

					//process the data i.e. turn string to int
					//as well as just making clear which variable is which
					std::string id = countryData[0];
					std::string name = countryData[1];
					//std::cout << name << std::endl;
					int red = atoi(countryData[2].c_str());
					int green = atoi(countryData[3].c_str());
					int blue = atoi(countryData[4].c_str());
					int pop = atoi(countryData[5].c_str());

					//create new instance of a country
					Country c = Country(id, name, red, green, blue, pop);

					//add the country to the country list
					countryList.push_back(c);
				}
				
				//increment
				count++;
			}

			//next line therefore increment
			countries++;
		}

		//close file after reading
		cData.close();
	}
	else
	{
		loaded = -1;
	}

	//debugging
	/*for (int i = 0; i < countryList.size(); i++)
	{
		std::cout << "ID: " << countryList[i].getID() << std::endl;
		std::cout << "Name: " << countryList[i].getCountryName() << std::endl;
		std::cout << "Population: " << countryList[i].getPopulation() << std::endl << std::endl;
	}*/

	return loaded;
}

/**
* menuBar
* function which heavily uses imgui to create the program's main menu bar as well as its options.
* The function also deals with the sub windows that the menu options generate as well as calls the info box function
*
* @param bool &appRun (uses the pointer to the bool value so that the quit option of the menu can shut down the program)
*/
void GUI::menuBar(bool &appRun)
{
	//display the side info box
	infoBox();

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
			openSimWindow = true;
		}

		//Save current simulation
		if (ImGui::MenuItem("Save", "CTRL+S"))
		{

		}

		//Save current simulation with a different name

		if (ImGui::MenuItem("Save As"))
		{

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

	//Edit
	if (ImGui::BeginMenu("Edit"))
	{
		if (ImGui::MenuItem("Edit Simulation"))
		{

		}


		ImGui::EndMenu();
	}

	//View
	if (ImGui::BeginMenu("View"))
	{

		ImGui::EndMenu();
	}

	//Preferences
	if (ImGui::BeginMenu("Preferences"))
	{
		//allows user to change simulation appearance
		if (ImGui::MenuItem("Appearance Preferences"))
		{
			aPrefWin ^= 1;
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

	//if the user wants to create a new simulation
	newSim();
	//if the user wants to open a previous simulation
	openSim();
}

/**
* infoBox
* function which uses imgui to display the options that the user has done i.e. the chosen country's information
*/
void GUI::infoBox()
{
	//make the side bar
	ImGui::Begin("", NULL, 
		ImGuiWindowFlags_NoCollapse
		| ImGuiWindowFlags_NoTitleBar
		| ImGuiWindowFlags_NoMove
		| ImGuiWindowFlags_NoResize);
	//set the side bar position, which is on the infobox rect
	ImGui::SetWindowPos("", ImVec2(infoBoxRect.x, infoBoxRect.y));
	//set the side bar size
	ImGui::SetWindowSize("", ImVec2(infoBoxRect.w, infoBoxRect.h));

	//display the data of the selected country
	ImGui::CollapsingHeader("Selected Country");
	//country ID
	ImGui::TextWrapped("ID: \n%s", curCountry.getID().c_str());
	//country Name
	ImGui::TextWrapped("Name: \n%s", curCountry.getCountryName().c_str());
	//country Population
	ImGui::TextWrapped("Population: \n%d", curCountry.getPopulation());

	//std::cout << curCountry.getID() << ", " << curCountry.getCountryName() << ", " << curCountry.getPopulation() << std::endl;

	ImGui::End();

}

/**
* newSim
* function that uses an imgui window to allow the user to create a new simulation 
*/
void GUI::newSim()
{
	//open new simulation window
	if (newSimWindow)
	{
		ImGui::Begin("New Simulation", &newSimWindow, ImGuiWindowFlags_NoCollapse);
		ImGui::Text("New Sim");
		ImGui::End();
	}
}

/**
* openSim
* function that uses an imgui window to allow the user to open an existing simulation
*/
void GUI::openSim()
{
	//open the existing simulation window
	if (openSimWindow)
	{
		ImGui::Begin("Opem Simulation", &openSimWindow, ImGuiWindowFlags_NoCollapse);
		ImGui::Text("Open Sim");
		ImGui::End();
	}
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
	//update info box rect
	infoBoxRect.x = vp.w;
	infoBoxRect.y = 20;
	infoBoxRect.w = ((int)ImGui::GetIO().DisplaySize.x) / 4;
	infoBoxRect.h = ((int)ImGui::GetIO().DisplaySize.y);

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

	//link viewports to the renderer
	SDL_RenderSetViewport(renderer, &vp);

	//render the world map
	SDL_RenderCopy(renderer, worldMap, NULL, NULL);

	//render the IMGUI elements
	glUseProgram(0);
	ImGui::Render();


	//update the screen
	SDL_RenderPresent(renderer);
	SDL_GL_SwapWindow(window);
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

