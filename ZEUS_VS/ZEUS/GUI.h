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

		//update window size
		void winSizeUpdate(int winX, int winY);

		//draw menu bar
		void menuBar(bool &appRun);

		//menu bar functions
		void newSim();
		void openSim();

		void render(SDL_Window *window, SDL_Renderer *renderer);

		//move the viewport
		void moveVPUp();
		void moveVPDown();
		void moveVPLeft();
		void moveVPRight();

		//zooming the viewport
		void zoom(int zoomType, SDL_Point mousePos);
		void pan(SDL_Point mousePos);
		void panLimiting();

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

		//previous mouse position
		SDL_Point prevMouse;

		//viewport zoom
		float zoomVal; //current zoom
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

	//std::cout << center.x << ", " << center.y << std::endl;

	//set zoom to 1
	zoomVal = 1;

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
	//destroy the textures
	//SDL_DestroyTexture(worldMap);
	//SDL_DestroyTexture(colourMap);
}

inline void GUI::winSizeUpdate(int winX, int winY)
{
	worldX = winX,
	worldY = winY;
}

void GUI::menuBar(bool &appRun)
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

	newSim();
	openSim();
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

	//clear the screen
	SDL_SetRenderDrawColor(renderer,
		bkgColour.x * 255.0f,
		bkgColour.y * 255.0f,
		bkgColour.z * 255.0f,
		bkgColour.w * 255.0f);
	SDL_RenderClear(renderer);
	
	//get window size
	vp.w = (int)ImGui::GetIO().DisplaySize.x * zoomVal;
	vp.h = (int)ImGui::GetIO().DisplaySize.y * zoomVal;

	//gets the world size
	SDL_GetWindowSize(window, &worldX, &worldY);
	//std::cout << worldX << ", " << worldY << std::endl;
	//std::cout << vp.x << ", " << vp.y << std::endl;

	//link viewport to the renderer
	SDL_RenderSetViewport(renderer, &vp);

	

	//debugging rect
	/*SDL_Rect rect = { 100, 100, 500, 500 };
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &rect);*/

	if (showColourMap)
	{
		SDL_RenderCopy(renderer, colourMap, NULL, &vp);
	}

	//only done if the user chose to show the country colourmap
	if (!showColourMap)
	{
		//render the world map
		SDL_RenderCopy(renderer, worldMap, NULL, &vp);
	}

	//render the IMGUI elements
	glUseProgram(0);
	ImGui::Render();

	SDL_RenderPresent(renderer);

	//update the screen
	SDL_GL_SwapWindow(window);
}

void GUI::moveVPUp()
{
	//move up
	vp.y -= panSpeed;

	//checks if the viewport stays within the bounds
	panLimiting();

	//debug
	//std::cout << "UP Test\n";
	//std::cout << "Center Y: " << center.y << std::endl;
}

void GUI::moveVPDown()
{
	//move down
	vp.y += panSpeed;

	//checks if the viewport stays within the bounds
	panLimiting();

	//debug
	//std::cout << "DOWN Test\n";
	//std::cout << "Center Y: " << center.y << std::endl;
}

void GUI::moveVPLeft()
{
	//move left
	vp.x -= panSpeed;

	//checks if the viewport stays within the bounds
	panLimiting();

	//debug
	//std::cout << "LEFT Test\n";
	//std::cout << "Center X: " << center.x << std::endl;
}

void GUI::moveVPRight()
{
	//move right
	vp.x += panSpeed;

	//checks if the viewport stays within the bounds
	panLimiting();

	//debug
	//std::cout << "RIGHT Test\n";
	//std::cout << "Center X: " << center.x << std::endl;
}

void GUI::zoom(int zoomType, SDL_Point mousePos)
{	
	switch (zoomType)
	{
		//catches null type zooms
	case -1:
		break;


		//zooming in
	case 1:
		if (zoomVal - zoomAmount > maxZoomOut)
		{
			zoomVal -= zoomAmount;
		}
		break;

		//zooming out
	case 0:
		if (zoomVal + zoomAmount < maxZoomIn)
		{
			zoomVal += zoomAmount;
		}
		break;

		//catches invalid values
	default:
		//warning to console
		std::cout << "Warning invalid zoomtype: " << zoomType << "\n";
		break;
	}

	//panLimiting();

	//std::cout << "D Scale: " << scaleChange << std::endl;
	//std::cout << "Mouse Pos: " << mousePos.x << ", " << mousePos.y << std::endl;
	//std::cout << "Center X and Y: " << center.x << ", " << center.y << std::endl << std::endl;

	//panLimiting();
}


void GUI::pan(SDL_Point mousePos)
{
	//only pans if mouse is on the 1/8th outer region of the screen
	if ((vp.w / 8) > mousePos.x)
	{
		moveVPRight();
	}
	else if((vp.w - vp.w / 8) < mousePos.x)
	{
		moveVPLeft();
	}
	if ((vp.h / 8) > mousePos.y)
	{
		moveVPDown();
	}
	else if ((vp.h - vp.h / 8) < mousePos.y)
	{
		moveVPUp();
	}
}

void GUI::panLimiting()
{
	float upperLimit, lowerLimit, leftLimit, rightLimit;
	float rescaleWorldX = worldX * zoomVal,
		rescaleWorldY = worldY * zoomVal;
	upperLimit = vp.h/16;
	leftLimit = vp.w/16;
	lowerLimit = vp.h / 16;

	float offsetCenterX = vp.x - vp.w / 2;
	float offsetCenterY = vp.y - vp.h / 2;

	//print limits
	//std::cout << std::endl;
	//std::cout << "limit up: " << upperLimit << std::endl;
	//std::cout << "limit down: " << lowerLimit << std::endl;
	//std::cout << "limit left: " << leftLimit << std::endl;
	//std::cout << "limit right: " << rightLimit << std::endl;
	//std::cout << std::endl;
	//std::cout << "VP size: " << vp.w << ", " << vp.h << std::endl;
	//std::cout << "World size: " << worldX << ", " << worldY << std::endl;
	//std::cout << "Zoom Val: " << zoomVal << std::endl;

	//debug
	//std::cout << std::endl;
	//std::cout << "Center X: " << center.x << std::endl;
	//std::cout << "VP Y: " << vp.y << std::endl;

	////limit panning upwards
	//if (upperLimit < offsetCenterY)
	//{
	//	vp.y = upperLimit + vp.h / 2;
	//}

	////limit panning towards left
	//if (leftLimit < offsetCenterX)
	//{
	//	vp.x = leftLimit + vp.w / 2;
	//}	

	////limit panning towards right
	//if (rightLimit > center.x)
	//{
	//	center.x = rightLimit;
	//}
}

void GUI::ctrlN()
{
	newSimWindow = true;
}

void GUI::ctrlO()
{
	openSimWindow = true;
}

