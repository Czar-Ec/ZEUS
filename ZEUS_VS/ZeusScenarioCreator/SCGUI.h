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

	//new scenario window
	void newScenarioWin(SDL_Renderer *renderer);
	void resetNewScenario();

	//gui rendering
	void render(SDL_Window *window, SDL_Renderer *renderer);

	//ease of access
	void helpMarker(const char* desc);

private:
	//colour of the background
	ImVec4 bkgColour = ImColor(255,255,255);

	bool newScenario = false;

	//map to be shown on screen
	SDL_Texture *map = NULL;

	#pragma region SCENARIO GLOBAL VARIABLES
	//////////////////////////////////////////////////////////////////////////////////
	//scenario name
	char name[30] = "";
	//file path for the scenario map
	char imgFilePath[MAX_PATH] = "";
	std::string imgType = "";
	//whether or not zombies are involved
	bool simulateZombies = false;


	/////////////////////
	//TEMPORARY VARIABLES
	/////////////////////
	//temporary variables, will be pushed into global after pressing create simulation
	char tempName[30] = "";
	char tempMapFilePath[MAX_PATH] = "";
	std::string tempImgType = "";
	bool tempZombies = false;

	//booleans for error validation
	bool acceptName = false;
	bool acceptImgPath = false;
	bool existingImgPath = false;

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
			ofn.lpstrFilter = "DAT Files\0*.dat\0Any File\0*.*\0";
			ofn.lpstrFile = filename;
			ofn.nMaxFile = MAX_PATH;
			ofn.lpstrTitle = "Select a File, yo!";
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
}

void SCGUI::newScenarioWin(SDL_Renderer *renderer)
{
	//make the window
	ImGui::Begin("New Scenario", &newScenario, ImGuiWindowFlags_NoCollapse);

	ImGui::Separator();

	//Scenario name label
	ImGui::Text("Scenario Name: ");
	ImGui::SameLine();
	helpMarker("The name of the scenario. Maximum 30 characters.");
	//Scenario name input
	ImGui::InputText("##name", tempName, sizeof(tempName), NULL);
	
	ImGui::Separator();

	//Scenario map label
	ImGui::Text("Scenario Map: ");
	ImGui::SameLine();
	helpMarker("The file path the program follows to load the image which will be the map used in the simultion");
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
	//Scenario zombie settings label
	ImGui::Text("Zombie Scenario: ");
	ImGui::SameLine();
	helpMarker("Tick if the scenario should involve zombies during simulation");

	ImGui::SameLine();
	//check box for bool or no
	ImGui::Checkbox("##zombieSimOpt", &tempZombies);

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

			//setglobal zombie to temp zombie
			simulateZombies = tempZombies;

			resetNewScenario();
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
		
		if (!existingImgPath)
		{
			ImGui::Text("Map file does not exist.\n");
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
		SDL_RenderCopy(renderer, map, NULL, NULL);
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
	tempZombies = false;
	
	//reset validations
	acceptName = false;
	acceptImgPath = false;
	existingImgPath = false;

	newScenario = false;
}

void SCGUI::render(SDL_Window * window, SDL_Renderer * renderer)
{
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
		SDL_RenderCopy(renderer, map, NULL, NULL);
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
