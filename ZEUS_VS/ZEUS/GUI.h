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
		//world size
		int worldX, worldY;
		//viewport rect
		SDL_Rect vp;
		//focus point of camera
		SDL_Point center;

		//previous mouse position
		SDL_Point prevMouse;

		//viewport zoom
		float zoomVal; //current zoom
		float zoomAmount = 0.1; //increment zoom by this amount
		float panSpeed = 20;
		float maxZoomIn = 4, maxZoomOut = 0.9;

		//bool for menubar windows
		bool aPrefWin, newSimWindow, openSimWindow;

		#pragma region APPEARANCE PREFERENCES
		//Appearance Preferences
		//bool if window should be open or not


		ImVec4 bkgColour;


		#pragma endregion

		//the texture which will be drawn to the screen
		SDL_Texture *worldMap;

		//list of countries
		std::vector<Country> countryList;
};

GUI::GUI()
{
	//temporarily empty but will then have values later on
}

GUI::GUI(SDL_Renderer *renderer, int winX, int winY)
{
	//viewport location
	vp.x = vp.y = 0;

	worldX = (int)ImGui::GetIO().DisplaySize.x;
	worldY = (int)ImGui::GetIO().DisplaySize.y;

	//center is at center of the screen
	center.x = 0;
	center.y = 0;

	//set zoom to 1
	zoomVal = 1;

	//not initially open
	aPrefWin
		= newSimWindow
		= openSimWindow
		= false;

	//background colour
	bkgColour = ImColor(0, 0, 44);

	//load the worldmap texture
	SDL_Surface *worldSurf = IMG_Load("res\\img\\worldHigh.png");
	worldMap = SDL_CreateTextureFromSurface(renderer, worldSurf);
	//remove the surface, no longer needed
	SDL_FreeSurface(worldSurf);
	if (worldMap == NULL)
	{
		std::cerr << "World Map not found!\n" << IMG_GetError() << std::endl;
		worldX = worldY = 0;
	}
}


GUI::~GUI()
{

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

	//update viewport location to be set to the center
	vp.x = center.x;
	vp.y = center.y;

	//link viewport to the renderer
	SDL_RenderSetViewport(renderer, &vp);

	

	//debugging rect
	/*SDL_Rect rect = { 100, 100, 500, 500 };
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &rect);*/

	//render the world map
	SDL_RenderCopy(renderer, worldMap, NULL, NULL);

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
	center.y += panSpeed;

	//checks if the viewport stays within the bounds
	panLimiting();

	//debug
	//std::cout << "UP Test\n";
	//std::cout << "Center Y: " << center.y << std::endl;
}

void GUI::moveVPDown()
{
	//move down
	center.y -= panSpeed;

	//checks if the viewport stays within the bounds
	panLimiting();

	//debug
	//std::cout << "DOWN Test\n";
	//std::cout << "Center Y: " << center.y << std::endl;
}

void GUI::moveVPLeft()
{
	//move left
	center.x += panSpeed;

	//checks if the viewport stays within the bounds
	panLimiting();

	//debug
	//std::cout << "LEFT Test\n";
	//std::cout << "Center X: " << center.x << std::endl;
}

void GUI::moveVPRight()
{
	//move right
	center.x -= panSpeed;

	//checks if the viewport stays within the bounds
	panLimiting();

	//debug
	//std::cout << "RIGHT Test\n";
	//std::cout << "Center X: " << center.x << std::endl;
}

void GUI::zoom(int zoomType, SDL_Point mousePos)
{
	//get mouse pos relative to viewport
	float mX = mousePos.x - center.x;
	float mY = mousePos.y - center.y;

	//update old zoom
	float oldzoom = zoomVal;
	
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

	//figure out change in scale
	float scaleChange = zoomVal - oldzoom;

	//only change things if the scale changed
	if (scaleChange != 0)
	{
		//calculate offsets
		float offsetX = mX * (zoomVal / oldzoom);
		float offsetY = mY * (zoomVal / oldzoom);

		//std::cout << "Offtset X and Y: " << offsetX << ",  " << offsetY << std::endl << std::endl;

		//adjust camera
		center.x += mX - offsetX;
		center.y += mY - offsetY;

		panLimiting();
	}

	//std::cout << "D Scale: " << scaleChange << std::endl;
	//std::cout << "Mouse Pos: " << mousePos.x << ", " << mousePos.y << std::endl;
	//std::cout << "Center X and Y: " << center.x << ", " << center.y << std::endl << std::endl;
}


void GUI::pan(SDL_Point mousePos)
{
	//only pans if mouse is on the 1/8th outer region of the screen
	if ((worldX / 8) > mousePos.x)
	{
		moveVPLeft();
	}
	else if((worldX - worldX / 8) < mousePos.x)
	{
		moveVPRight();
	}
	if ((worldY / 8) > mousePos.y)
	{
		moveVPUp();
	}
	else if ((worldY - worldY / 8) < mousePos.y)
	{
		moveVPDown();
	}
}

void GUI::panLimiting()
{
	float upperLimit, lowerLimit, leftLimit, rightLimit;
	float rescaleWorldX = worldX * zoomVal,
		rescaleWorldY = worldY * zoomVal;
	upperLimit = vp.h / 16;
	lowerLimit = -rescaleWorldY * 13 / 16 + rescaleWorldY / 16;
	leftLimit = vp.w / 16;
	rightLimit = - rescaleWorldX * 13 / 16 + rescaleWorldX / 16;

	//print limits
	/*std::cout << std::endl;
	std::cout << "limit up: " << upperLimit << std::endl;
	std::cout << "limit down: " << lowerLimit << std::endl;
	std::cout << "limit left: " << leftLimit << std::endl;
	std::cout << "limit right: " << rightLimit << std::endl;
	std::cout << std::endl;
	std::cout << "VP size: " << vp.w << ", " << vp.h << std::endl;
	std::cout << "World size: " << worldX << ", " << worldY << std::endl;
	std::cout << "Zoom Val: " << zoomVal << std::endl;*/

	//limit panning upwards
	if (upperLimit < center.y)
	{
		center.y = upperLimit;
	}

	//limit panning downwards
	else if (lowerLimit > center.y)
	{
		center.y = lowerLimit;
	}

	//limit panning towards left
	if (leftLimit < center.x)
	{
		center.x = leftLimit;
	}

	//limit panning towards right
	if (rightLimit > center.x)
	{
		center.x = rightLimit;
	}

	//debug
	/*std::cout << std::endl;
	std::cout << "Center X: " << center.x << std::endl;
	std::cout << "Center Y: " << center.y << std::endl;*/
}

void GUI::ctrlN()
{
	newSimWindow = true;
}

void GUI::ctrlO()
{
	openSimWindow = true;
}

