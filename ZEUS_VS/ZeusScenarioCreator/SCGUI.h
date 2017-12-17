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
<<<<<<< HEAD

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

//other items
#include "Country.h"
=======
>>>>>>> parent of 82d0947... 6:00am 14/12/17

/**
* GUI Class
* the class which handles the imgui actions and will be drawing and handling the actions on the scren
*/
static class SCGUI
{
public:
	SCGUI();
	SCGUI(SDL_Renderer *renderer, int winX, int winY);
	~SCGUI();

<<<<<<< HEAD
	//draw menu bar
	void menuBar(bool &appRun);

	//info box
	void infoBox();
=======
	//main menu bar
	void menuBar(bool &appRun);
>>>>>>> parent of 82d0947... 6:00am 14/12/17

	//menu bar functions
	void newSim();
	void openSim();

	//render items
	void render(SDL_Window *window, SDL_Renderer *renderer);

<<<<<<< HEAD
	//CONTROLS AND SHORTCUTS
	void ctrlN();
	void ctrlO();

	void leftClick(SDL_Window *window);

	void zoom(int zoomType);	//function to allow zooming
	void pan(SDL_Point *mPos, int motionX, int motionY);	//function to allow panning of the map
	void panLimiting();	//ensures the pan is limited within the relevant zone of the texture

=======
>>>>>>> parent of 82d0947... 6:00am 14/12/17
private:

	//world size
	int worldX, worldY;

	//viewport rect
	SDL_Rect vp; //display area
	SDL_Rect vpSrc; //allows panning and zooming

					//information box rect
	SDL_Rect infoBoxRect;

	//bool for menubar windows
	bool newSimWindow, openSimWindow;

#pragma region APPEARANCE PREFERENCES
	////////////////////////////////////////////////////////////////////////////////
	//Appearance Preferences
	//bool if window should be open or not
	bool aPrefWin;

	//colour of the background
<<<<<<< HEAD
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

	SDL_Point oldMousePos;

	////////////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma region GLOBAL DATA VARIABLES
	////////////////////////////////////////////////////////////////////////////////
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
	Country curCountry = Country("None", "None", 0, 0, 0, 0);


	//////////////////////////////////////////////////////////////////////////////////////
#pragma endregion
=======
	ImVec4 bkgColour = ImColor(255,255,255);


>>>>>>> parent of 82d0947... 6:00am 14/12/17
};

/**
* GUI default contructor
* empty constructor which is temporary i.e. for when GUI is set up in main
*/
SCGUI::SCGUI()
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
SCGUI::SCGUI(SDL_Renderer *renderer, int winX, int winY)
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
	openSimWindow = false;

	//pref window not open unless chosen
	aPrefWin = false;


	//background colour
	bkgColour = ImColor(0, 0, 44);

	//load the worldmap textures
	SDL_Surface *worldSurf = IMG_Load("..\\res\\img\\worldHigh.png");
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

	vpSrc = { 0, 0, wMapX, wMapY };
}

/**
* GUI destructor
*/
SCGUI::~SCGUI()
{

}

<<<<<<< HEAD
/**
* menuBar
* function which heavily uses imgui to create the program's main menu bar as well as its options.
* The function also deals with the sub windows that the menu options generate as well as calls the info box function
*
* @param bool &appRun (uses the pointer to the bool value so that the quit option of the menu can shut down the program)
*/
=======

>>>>>>> parent of 82d0947... 6:00am 14/12/17
void SCGUI::menuBar(bool &appRun)
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
<<<<<<< HEAD
			newSimWindow = true;
=======

>>>>>>> parent of 82d0947... 6:00am 14/12/17
		}

		//Open existing simulation
		if (ImGui::MenuItem("Open Simulation", "CTRL+O"))
		{
<<<<<<< HEAD
			openSimWindow = true;
=======

>>>>>>> parent of 82d0947... 6:00am 14/12/17
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
<<<<<<< HEAD
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
void SCGUI::infoBox()
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

#pragma region WORLD STATISTICS
	///////////////////////////////////////////////////////////////////////////////////////////////
	//display the map statistics
	if (ImGui::CollapsingHeader("World Statistics"))
	{
		//total countries
		ImGui::TextWrapped("Number of Countries: %d", totalCountries);
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
		//country ID
		ImGui::TextWrapped("ID: %s", curCountry.getID().c_str());
		//country Name
		ImGui::TextWrapped("Name: %s", curCountry.getCountryName().c_str());
		//country Population
		ImGui::TextWrapped("Population: %d", curCountry.getPopulation());

	}

	///////////////////////////////////////////////////////////////////////////////////////////////
#pragma endregion

	//std::cout << curCountry.getID() << ", " << curCountry.getCountryName() << ", " << curCountry.getPopulation() << std::endl;

	ImGui::End();

}

/**
* newSim
* function that uses an imgui window to allow the user to create a new simulation
*/
void SCGUI::newSim()
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
void SCGUI::openSim()
{
	//open the existing simulation window
	if (openSimWindow)
	{
		ImGui::Begin("Opem Simulation", &openSimWindow, ImGuiWindowFlags_NoCollapse);
		ImGui::Text("Open Sim");
		ImGui::End();
	}
=======
>>>>>>> parent of 82d0947... 6:00am 14/12/17
}

/**
* render
* function that draws all the items to the screen
*
* @param SDL_Window window
* @param SDL_Renderer renderer
*/
void SCGUI::render(SDL_Window *window, SDL_Renderer *renderer)
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
<<<<<<< HEAD

	//link viewports to the renderer
	SDL_RenderSetViewport(renderer, &vp);

	//render the world map
	SDL_RenderCopy(renderer, worldMap, &vpSrc, NULL);

=======
	
>>>>>>> parent of 82d0947... 6:00am 14/12/17
	//render the IMGUI elements
	glUseProgram(0);
	ImGui::Render();


	//update the screen
	SDL_RenderPresent(renderer);
	SDL_GL_SwapWindow(window);
}
<<<<<<< HEAD

/**
* ctrlN
* function called when the control + N shortcut is used.
* shortcut is to make a new simulation
*/
void SCGUI::ctrlN()
{
	newSimWindow = true;
}

/**
* ctrlO
* function called when the control + O shortcut is used.
* shortcut is used to open an existing simulation
*/
void SCGUI::ctrlO()
{
	openSimWindow = true;
}

/**
leftClick
When called, the function reads the screen and uses the pixel under the mouse cursor to determine if the user has selected a country
*/
void SCGUI::leftClick(SDL_Window *window)
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
void SCGUI::zoom(int zoomType)
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

void SCGUI::pan(SDL_Point *mPos, int motionX, int motionY)
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

=======
>>>>>>> parent of 82d0947... 6:00am 14/12/17
