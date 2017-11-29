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
#include "GUI.h"

class Main
{
public:
	Main();
	~Main();

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
	SDL_DisplayMode currentDisplay;
	//simulation renderer
	SDL_Renderer *renderer;

	//initiate GUI
	GUI gui;

	//bool to store application run
	bool appRun;

	//SDL Events
	SDL_Event eventMain;
	bool clickAndDrag;
	
	//mouse position
	SDL_Point mousePos;

	//opengl context
	SDL_GLContext glcontext;

	//time handling
	int frames = 0;
	float fps = 0;
	int fpsLimit = 60;

	//pause sim
	bool pauseSim;
};

