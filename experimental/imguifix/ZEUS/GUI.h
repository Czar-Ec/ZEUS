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
		GUI(SDL_Renderer *renderer);
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

		//shortcuts
		void ctrlN();
		void ctrlO();


	private:
		//viewport rect
		SDL_Rect vp;
		//center of the screen
		SDL_Point vpCenter;
		//scaled original vp
		int scaledX, scaledY;

		//previous mouse position
		SDL_Point prevMouse;

		//viewport zoom
		float zoomVal;
		float zoomAmount = 0.05;
		float maxZoomIn = 2.5, maxZoomOut = 0.9;

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

GUI::GUI(SDL_Renderer *renderer)
{
	//viewport location
	vp.x = vp.y = 0;
	scaledX = vp.w = (int)ImGui::GetIO().DisplaySize.x;
	scaledY = vp.h = (int)ImGui::GetIO().DisplaySize.y;

	vpCenter.x = vp.x + vp.w/2;
	vpCenter.y = vp.y + vp.h/2;

	//setup prevmouse
	prevMouse.x = prevMouse.y = 0;

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
	SDL_Surface *worldSurf = IMG_Load("res\\img\\world1.png");
	worldMap = SDL_CreateTextureFromSurface(renderer, worldSurf);
	//remove the surface, no longer needed
	SDL_FreeSurface(worldSurf);
	if (worldMap == NULL)
	{
		std::cerr << "World Map not found!\n" << IMG_GetError() << std::endl;
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



	//std::cout << vpCenter.x << ", " << vpCenter.y << std::endl;

	//move the viewport to the correct place
	vp.x = vpCenter.x;
	vp.y = vpCenter.y;

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

	//update the screen
	SDL_GL_SwapWindow(window);
}

void GUI::moveVPUp()
{
	//get the top of the viewport and make sure at least a quarter of the window remains within the map
	if (vpCenter.y - (vp.h / 2) < -vp.h / 4)
	{
		vpCenter.y += 10;
	}
	//std::cout << "up\n";
	//std::cout << "UP: " << vpCenter.y - (vp.h / 2) << ", " << -vp.h/4 << std::endl;
}

void GUI::moveVPDown()
{
	//get the bottom of the viewport and make sure it stays within the map
	if (vpCenter.y + (vp.h / 2) > -vp.h / 4)
	{
		vpCenter.y -= 10;
	}
	//std::cout << "down\n";
	//std::cout << "DOWN: " << vpCenter.y + (vp.h / 2) << ", " << scaledY << std::endl;
}

void GUI::moveVPLeft()
{
	if (vpCenter.x - (vp.w / 2) < -vp.w / 4)
	{
		vpCenter.x += 10;
	}
	//std::cout << "left\n";
	//std::cout << "LEFT: " << vpCenter.x - (vp.w / 2) << ", " << -vp.w/4 << std::endl;
}

void GUI::moveVPRight()
{
	if (vpCenter.x + (vp.w / 2) > -vp.w / 4)
	{
		vpCenter.x -= 10;
	}
	//std::cout << "right\n";
	//std::cout << "RIGHT: " << vpCenter.x + (vp.w / 2) << ", " << -vp.w/4 << std::endl;
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

	//get window size
	vp.w = (int)ImGui::GetIO().DisplaySize.x;
	vp.h = (int)ImGui::GetIO().DisplaySize.y;

	////center on the mouse
	//vpCenter.x = vp.x + vp.w / 2;
	//vpCenter.y = vp.y + vp.h / 2;

	//std::cout << vpCenter.x << ", " << vpCenter.y << std::endl;

	//glOrtho(-vpW * zoomVal, vpW*zoomVal, -vpH*zoomVal, vpH * zoomVal, 1, -1);
	//glOrtho(0, vp.w * zoomVal, vp.h * zoomVal, 0, 1, -1);

	scaledX = vp.w * zoomVal;
	scaledY = vp.h * zoomVal;

	//adjust the vpcenter

}


void GUI::pan(SDL_Point mousePos)
{	
	//move by the difference of the mouse's movement
	/*vpCenter.x += mousePos.x - vpCenter.x;
	vpCenter.y += mousePos.y - vpCenter.y;*/

	//get screen size
	int screenX = (int)ImGui::GetIO().DisplaySize.x,
		screenY = (int)ImGui::GetIO().DisplaySize.y;

	//only pans if mouse is on the 1/8th outer region of the screen
	if ((screenX / 8) > mousePos.x)
	{
		moveVPLeft();
	}
	else if((screenX - screenX / 8) < mousePos.x)
	{
		moveVPRight();
	}
	if ((screenY / 8) > mousePos.y)
	{
		moveVPUp();
	}
	else if ((screenY - screenY / 8) < mousePos.y)
	{
		moveVPDown();
	}

	//std::cout << mousePos.x - prevMouse.x << "\n" << mousePos.y - prevMouse.y << "\n";
	//std::cout << vp.x << ", " << vp.y << std::endl;
}

void GUI::ctrlN()
{
	newSimWindow = true;
}

void GUI::ctrlO()
{
	openSimWindow = true;
}

