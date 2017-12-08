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
#include <iostream>
#include <stdio.h>
#include <shellapi.h>
#include <vector>

//other items
#include "Country.h"

static class GUI
{
	public:
		GUI();
		GUI(SDL_Renderer *renderer, int winX, int winY);
		~GUI();

		//draw menu bar
		void menuBar(bool &appRun);

		//info box
		void infoBox();

		//menu bar functions
		void newSim();
		void openSim();

		//render items
		void render(SDL_Window *window, SDL_Renderer *renderer);

		//shortcuts
		void ctrlN();
		void ctrlO();


	private:
		//renderer
		SDL_Renderer *guiRenderer;

		//world size
		int worldX, worldY;

		//viewport rect
		SDL_Rect vp;

		//information box rect
		SDL_Rect infoBoxRect;

		//previous mouse position
		SDL_Point prevMouse;

		//viewport zoom
		//float zoomVal; //current zoom
		float zoomAmount = 0.1; //increment zoom by this amount
		float panSpeed = 20;
		float maxZoomIn = 4, maxZoomOut = 0.9;

		//bool for menubar windows
		bool newSimWindow, openSimWindow;

		#pragma region APPEARANCE PREFERENCES
		//Appearance Preferences
		//bool if window should be open or not
		bool aPrefWin;

		//bool to show colour map or not
		bool showColourMap;

		//colour of the background
		ImVec4 bkgColour;


		#pragma endregion


		//the texture which will be drawn to the screen
		SDL_Texture *worldMap;
		SDL_Texture *colourMap;
		//texture sizes
		int wMapX, wMapY, cMapX, cMapY;
		//list of countries
		std::vector<Country> countryList;
};

GUI::GUI()
{
	//temporarily empty but will then have values later on
}

GUI::GUI(SDL_Renderer *renderer, int winX, int winY)
{
	guiRenderer = renderer;
	
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

	SDL_Surface *colourSurf = IMG_Load("res\\img\\worldHighc.png");
	colourMap = SDL_CreateTextureFromSurface(renderer, colourSurf);
	//remove surface
	SDL_FreeSurface(colourSurf);
	//check if texture is loaded
	if (colourMap == NULL)
	{
		std::cerr << "Colour Map not found!\n" << IMG_GetError() << std::endl;
		worldX = worldY = 0;
	}

	SDL_QueryTexture(worldMap, NULL, NULL, &cMapX, &cMapY);
}


GUI::~GUI()
{
	
}

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
		ImGui::Text("Colour Map");
		ImGui::Checkbox("Colour Map: ", &showColourMap);
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
	


	ImGui::End();

}

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

void GUI::render(SDL_Window *window, SDL_Renderer *renderer)
{
	SDL_RenderCopy(renderer, colourMap, NULL, &vp);

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

	if (showColourMap)
	{
		SDL_RenderCopy(renderer, colourMap, NULL, NULL);
	}

	//only done if the user chose to show the country colourmap
	if (!showColourMap)
	{
		//render the world map
		SDL_RenderCopy(renderer, worldMap, NULL, NULL);
	}

	//render the IMGUI elements
	glUseProgram(0);
	ImGui::Render();

	SDL_RenderPresent(renderer);

	//update the screen
	SDL_GL_SwapWindow(window);
}

void GUI::ctrlN()
{
	newSimWindow = true;
}

void GUI::ctrlO()
{
	openSimWindow = true;
}

