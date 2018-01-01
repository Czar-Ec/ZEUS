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
#include <vector>
#include <string>
#include <algorithm>

//Visual C++ library
#include "Windows.h"

//other classes
#include "Country.h"

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

	//menu functions
	void save();

	//new scenario window
	void newScenarioWin(SDL_Renderer *renderer);
	void resetNewScenario();

	//add new country window
	void newCountryMenu(SDL_Renderer *renderer, int r, int g, int b);

	//gui rendering
	void render(SDL_Window *window, SDL_Renderer *renderer);

	//ease of access
	void helpMarker(const char* desc);
	void eyedropTool();

	//Control functions
	void zoom(int zoomType);	//function to allow zooming
	void pan(SDL_Point *mPos, int motionX, int motionY);	//function to allow panning of the map
	void panLimiting();	//ensures the pan is limited within the relevant zone of the texture

private:
	//colour of the background
	ImVec4 bkgColour = ImColor(0,0,44);

	bool newScenario = false;
	bool addNewCountry = false;

	//map to be shown on screen
	SDL_Texture *map = NULL;

	//region where the map will be drawn
	int worldX, worldY;
	SDL_Rect vp;
	//rectangle which allows for zooming and panning
	SDL_Rect vpSrc;

	#pragma region CONTROL VARIABLES
	//////////////////////////////////////////////////////////////////////////////////
	int wMapX, wMapY;
	
	float zoomVal = 1,
		maxZoom = 1,
		minZoom = 0.1,
		zoomInterval = 0.025;


	//////////////////////////////////////////////////////////////////////////////////
	#pragma endregion

	#pragma region SCENARIO GLOBAL VARIABLES
	//////////////////////////////////////////////////////////////////////////////////
	//scenario name
	char name[30] = "";
	//file path for the scenario map
	char imgFilePath[MAX_PATH] = "";
	std::string imgType = "";

	//loaded scenario
	bool scenarioLoaded = false;


	/////////////////////
	//TEMPORARY VARIABLES
	/////////////////////
	//temporary variables, will be pushed into global after pressing create simulation
	char tempName[30] = "";
	char tempMapFilePath[MAX_PATH] = "";
	std::string tempImgType = "";

	//booleans for error validation
	bool acceptName = false;
	bool acceptImgPath = false;
	bool existingImgPath = false;
	bool validType = false;

	//////////////////////////////////////////////////////////////////////////////////
	#pragma endregion

	#pragma region NEW COUNTRY VARIABLES
	//////////////////////////////////////////////////////////////////////////////////
	//temporary variables which hold country information
	char tempCName[30] = "";
	int tempR = 0,
		tempG = 0,
		tempB = 0;


	//active eye dropper
	bool eyedropperActive = false;

	//////////////////////////////////////////////////////////////////////////////////
	#pragma endregion

	#pragma region COUNTRY VARIABLES
	//////////////////////////////////////////////////////////////////////////////////
	//list of countries
	std::vector<Country> countryList;

	//current chosen country
	Country curCountry = Country("None", "None", 0, 0, 0, 0);

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
			newScenario = false;

			char filename[MAX_PATH];
			OPENFILENAME ofn;
			ZeroMemory(&filename, sizeof(filename));
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = NULL;  // If you have a window to center over, put its HANDLE here
			ofn.lpstrFilter = "ZEUS Simulation Files (*.sim)\0*.sim\0";
			ofn.lpstrFile = filename;
			ofn.nMaxFile = MAX_PATH;
			ofn.lpstrTitle = "Open Simulation";
			ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

			if (GetOpenFileNameA(&ofn))
			{
				std::cout << "You chose the file \"" << filename << "\"\n";
			}
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

	//View
	if (ImGui::BeginMenu("View"))
	{
		//view scenario details
		if (ImGui::MenuItem("View Scenario Details"))
		{

		}

		//view existing countries option
		if (ImGui::MenuItem("View all countries"))
		{

		}

		//add new country option
		if (ImGui::MenuItem("Add new country"))
		{
			if (scenarioLoaded)
			{
				addNewCountry = true;
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

	if (addNewCountry)
	{
		newCountryMenu(renderer, 0, 0, 0);
	}
}

void SCGUI::save()
{

}

void SCGUI::newScenarioWin(SDL_Renderer *renderer)
{
	//make the window
	ImGui::Begin("New Scenario", &newScenario, ImGuiWindowFlags_NoCollapse);

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
		ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

		if (GetOpenFileNameA(&ofn))
		{
			strcpy(tempMapFilePath, filename);
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
			acceptName = true;
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
		if (acceptName && acceptImgPath && existingImgPath)
		{
			//copy temp name to global name
			strcpy(name, tempName);

			//copy img path to global img path
			strcpy(imgFilePath, tempMapFilePath);

			//file type of image
			imgType = tempImgType;

			resetNewScenario();
			scenarioLoaded = true;
		}
		else
		{
			ImGui::OpenPopup("Cannot Create Scenario");
		}

	}
	ImGui::Separator();
	ImGui::Separator();

	bool open = true;
	if (ImGui::BeginPopupModal("Cannot Create Scenario", &open, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize))
	{
		if (!acceptName)
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
		if (ImGui::Button("Close"))
		{
			ImGui::CloseCurrentPopup();
		}
		ImGui::Separator();
		ImGui::EndPopup();
	}
	ImGui::End();

	//load the texture
	if (tempMapFilePath != "")
	{
		SDL_Surface* tempSurf = IMG_Load(imgFilePath);

		map = SDL_CreateTextureFromSurface(renderer, tempSurf);
		SDL_FreeSurface(tempSurf);
		SDL_RenderCopy(renderer, map, NULL, NULL);//get texture size
		SDL_QueryTexture(map, NULL, NULL, &wMapX, &wMapY);
		vpSrc = { 0, 0, wMapX, wMapY };
	}
	
}

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
	acceptName = false;
	acceptImgPath = false;
	existingImgPath = false;

	newScenario = false;
}

void SCGUI::newCountryMenu(SDL_Renderer * renderer, int r, int g, int b)
{
	tempR = r,
	tempG = g,
	tempB = b;

	//make the window
	ImGui::Begin("New Country", &addNewCountry, ImGuiWindowFlags_NoCollapse);

	ImGui::Separator();
	//country name label
	ImGui::Text("Country Name: ");
	//input box
	ImGui::SameLine();
	//help marker
	helpMarker("Country Name. Maximum 30 characters");
	//country input
	ImGui::SameLine();
	ImGui::InputText("##countryname", tempCName, sizeof(tempCName), NULL);
	ImGui::Separator();

	//region identifier
	ImGui::Text("Country Region: ");
	ImGui::SameLine();
	helpMarker(
		"The colour that identifies as the country.\n" 
		"You can either input the colour manually or use the\n"
		"eye dropper tool to display the colour values from the image");

	//separate inputs into 3 columns
	ImGui::BeginColumns("##countrycolourinputs", 4, ImGuiColumnsFlags_NoBorder);

	//red colour input
	ImGui::TextColored(ImVec4(255, 0, 0, 255), "R: ");
	ImGui::SameLine();
	ImGui::InputInt("##redcolourinput", &tempR, NULL, NULL, NULL);
	ImGui::SameLine();

	//green colour input
	ImGui::NextColumn();
	ImGui::TextColored(ImVec4(0, 255, 0, 255), "G: ");
	ImGui::SameLine();
	ImGui::InputInt("##redcolourinput", &tempG, NULL, NULL, NULL);
	ImGui::SameLine();

	//blue colour input
	ImGui::NextColumn();
	ImGui::TextColored(ImVec4(0, 0, 255, 255), "B: ");
	ImGui::SameLine();
	ImGui::InputInt("##redcolourinput", &tempB, NULL, NULL, NULL);

	//eye dropper tool that will help identify region colours
	ImGui::NextColumn();
	ImGui::Text("Eyedrop tool: ");
	ImGui::SameLine();
	ImGui::Checkbox("##eyeDropCheckbox", &eyedropperActive);

	ImGui::EndColumns();

	ImGui::Separator();



	//create new country button
	if (ImGui::Button("Create Country", ImVec2(ImGui::GetWindowWidth(), 20)))
	{

	}

	ImGui::End();

	//only work if the mouse is not over any imgui items
	if (eyedropperActive && !ImGui::IsAnyItemHovered() && !ImGui::IsAnyWindowHovered())
	{
		eyedropTool();
	}
}

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
	}

	//render the IMGUI elements
	glUseProgram(0);
	ImGui::Render();


	//update the screen
	SDL_RenderPresent(renderer);
	SDL_GL_SwapWindow(window);
}

void SCGUI::helpMarker(const char * desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(450.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

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

inline void SCGUI::zoom(int zoomType)
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

void SCGUI::pan(SDL_Point * mPos, int motionX, int motionY)
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
