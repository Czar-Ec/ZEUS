#pragma once

//GLEW
#include <GL\glew.h>

//SDL libraries
#define SDL_STATIC
#include <SDL\SDL.h>
#include <SDL\SDL_main.h>
#include <SDL\SDL_ttf.h>
#include <SDL\SDL_opengl.h>

//IMGUI
#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_sdl.h"
#include "stb_rect_pack.h"
#include "stb_textedit.h"
#include "stb_truetype.h"

//C/C++ libraries
#include <iostream>
#include <stdio.h>
#include "Windows.h"


//other items
#include "SCGUI.h"

/**
* Main Class
* the class which handles everything that is relevant to the program.
* Main is the central point of the program and is what will contain the main loop
*/
class SCMain
{
public:
	SCMain();
	~SCMain();

	//initialise simulator
	void init();

	//close app
	void close();

	//main loop
	void mainLoop();

	//update main loop
	void updateMain();

private:

	//constant values
	const int ZOOM_IN = 1;
	const int ZOOM_OUT = 0;

	//window size
	int winWidth, winHeight;

	//simulation window
	SDL_Window *window;
	int winX, winY;
	//simulation renderer
	SDL_Renderer *renderer;

	//bool to store application run
	bool appRun;

	//SDL Events
	SDL_Event eventMain;

	//mouse position
	SDL_Point mousePos;

	//opengl context
	SDL_GLContext glcontext;

	//time handling
	int frames = 0;
	float fps = 0;
	int fpsLimit = 60;

	//pause sim
	bool pauseSim = false;

	//panning
	bool isPanning = false;

	//the GUI class used with the Main
	SCGUI gui;
};

/**
* Main constructor
* Calls init to initialise the program then runs the main loop
*/
SCMain::SCMain()
{
	//initialise
	init();

	//main loop
	mainLoop();
}

/**
* Main destructor
* called when the instance of Main is destroyed
*/
SCMain::~SCMain()
{
	close();
}

/**
* init
* Initialises the program and sets up the window which the program will use.
* The function also sets up the imgui library by calling its initialisation functions
*/
void SCMain::init()
{
	//initialise window as a null pointer
	window = nullptr;

	//initialise SDL and SDL font
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0 || TTF_Init() < 0)
	{
		//if initialisation is not possible, print the error
		std::cout << "SDL Initialisation error: " << SDL_GetError() << std::endl;
		//exit the program
		exit(0);
	}
	//once initiated, set up new window
	else
	{
		// Setup window
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

		//create the window
		window = SDL_CreateWindow(
			"ZEUS",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			//window width
			winX,
			//window height
			winY,
			//show window on screen
			SDL_WINDOW_SHOWN
			//resizable window
			| SDL_WINDOW_RESIZABLE
			//maximised window
			| SDL_WINDOW_MAXIMIZED
			//opengl window
			| SDL_WINDOW_OPENGL
		);

		//get display size
		SDL_GetWindowSize(window, &winX, &winY);

		//opengl context
		glcontext = SDL_GL_CreateContext(window);

		//check if window was created
		if (window == NULL)
		{
			std::cout << "SDL Window error: " << SDL_GetError() << std::endl;
			//exit the program
			exit(0);
		}
		//continue setup
		else
		{
			//initialise IMGUI
			ImGui_ImplSdlGL2_CreateDeviceObjects();
			ImGui_ImplSdlGL2_InvalidateDeviceObjects();
			ImGui_ImplSdlGL2_Init(window);

			//find GPU drivers
			int oglIdx = -1;
			int nRD = SDL_GetNumRenderDrivers();
			for (int i = 0; i<nRD; i++)
			{
				SDL_RendererInfo info;
				if (!SDL_GetRenderDriverInfo(i, &info))
				{
					if (!strcmp(info.name, "opengl"))
					{
						oglIdx = i;
					}
				}
			}

			//create the renderer, linking the number of GPU drivers
			renderer = SDL_CreateRenderer(window, oglIdx,
				SDL_RENDERER_ACCELERATED
				| SDL_RENDERER_PRESENTVSYNC
			);



			//initiate glew
			glewExperimental = true;
			glewInit();

			//setup ImGui style
			//ImGuiStyle &style = ImGui::GetStyle();
			//style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.6f, 0.0f, 0.0f, 1.0f);

			//allow transparency
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

			gui = SCGUI(renderer, winX, winY);
		}
	}

}

/**
* close
* function that calls the functions which closes down the imgui library and the SDL library
*/
void SCMain::close()
{
	//close everything
	ImGui_ImplSdlGL2_Shutdown();
	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

/**
* mainLoop
* function which will be the main loop of the entire program i.e. once the loop is exited, the program stops
*/
void SCMain::mainLoop()
{
	//handling frames per second
	float frameTime = 0,
		prevTime = 0,
		curTime = 0,
		deltaTime = 0;

	Uint32 startTime, elapsedTime;
	startTime = SDL_GetTicks();

	frames = 0, fps = 0;

	appRun = true;

	//keyboard input
	const Uint8 *key = SDL_GetKeyboardState(NULL);

	//debug mouse pos
	//std::cout << mousePos.x << ", " << mousePos.y << std::endl;

	//loop
	while (appRun)
	{
		//calculating frame time
		frames++;

		//the overall elapsed time
		elapsedTime = SDL_GetTicks() - startTime;

		//setting previous time to current time
		prevTime = curTime;
		//update current time
		curTime = SDL_GetTicks();

		//update mouse position
		SDL_GetMouseState(&mousePos.x, &mousePos.y);

		//check for inputs
		while (SDL_PollEvent(&eventMain) != 0)
		{
			//process event for IMGUI
			ImGui_ImplSdlGL2_ProcessEvent(&eventMain);

			//process events via SDL
			switch (eventMain.type)
			{
			case SDL_QUIT:
				appRun = false;
				break;

				//while clicking the left button
			case SDL_MOUSEBUTTONDOWN:
				if (eventMain.button.button == SDL_BUTTON_LEFT)
				{

				}
				//middle mouse button
				if (eventMain.button.button == SDL_BUTTON_RIGHT)
				{
					isPanning = true;
				}
				break;

				//when the button is no longer pressed
			case SDL_MOUSEBUTTONUP:
				if (eventMain.button.button == SDL_BUTTON_LEFT)
				{

				}

				//middle mouse button
				if (eventMain.button.button == SDL_BUTTON_RIGHT)
				{
					isPanning = false;
				}
				break;

			case SDL_MOUSEWHEEL:
				//mouse wheel for zoom control
				if (eventMain.wheel.y == -1)
				{
					//zoom in for scroll up
					gui.zoom(ZOOM_IN);
				}
				else if (eventMain.wheel.y == 1)
				{
					//zoom out for scroll down
					gui.zoom(ZOOM_OUT);
				}
				break;

			case SDL_KEYDOWN:
				if (eventMain.key.keysym.sym == SDLK_EQUALS)
				{
					gui.zoom(ZOOM_IN);
				}
				else if (eventMain.key.keysym.sym == SDLK_MINUS)
				{
					gui.zoom(ZOOM_OUT);
				}
				break;
			}

			//moving the viewport
			if (key[SDL_SCANCODE_UP]);
			if (key[SDL_SCANCODE_DOWN]);
			if (key[SDL_SCANCODE_LEFT]);
			if (key[SDL_SCANCODE_RIGHT]);


			//ctrl + N shortcut
			if (key[SDL_SCANCODE_LCTRL] && key[SDL_SCANCODE_N] ||
				key[SDL_SCANCODE_RCTRL] && key[SDL_SCANCODE_N])
			{

			}

			//ctrl + O shortcut
			if (key[SDL_SCANCODE_LCTRL] && key[SDL_SCANCODE_O] ||
				key[SDL_SCANCODE_RCTRL] && key[SDL_SCANCODE_O])
			{

			}
		}

		//only done if the simulation is not paused
		if (!pauseSim)
		{
			//update frame for imgui
			ImGui_ImplSdlGL2_NewFrame(window);

			//call the gui menubar
			gui.menuBar(renderer, appRun);

			//draw
			updateMain();

			//if the user is panning the world map
			if (isPanning)
			{
				if (eventMain.type == SDL_MOUSEMOTION)
				{
					//pan
					gui.pan(&mousePos, -eventMain.motion.xrel, -eventMain.motion.yrel);
				}
			}
		}

		//skips first frame to prevent crash
		if (elapsedTime)
		{
			//calculate time between frames
			deltaTime = (curTime - prevTime) / 1000.0f;

			//update frame time
			frameTime += deltaTime;

			//convert elapsed time to seconds
			double elapsedSec = elapsedTime / 1000;
			fps = frames / elapsedSec;

			//debug fps
			//std::cout << fps << std::endl;

			//controlling frame rate
			if (deltaTime < 1000 / fpsLimit)
			{
				if (fpsLimit != 0)
				{
					//sleep the remaining frame time
					SDL_Delay((1000 / fpsLimit) - deltaTime);
				}
			}
		}

	}

	//close components
	close();
}

/**
* updateMain
* function which is called at every iteration of the main loop.
* The function calls te rendering/drawing functons of the gui
*/
void SCMain::updateMain()
{
	gui.render(window, renderer);
}

