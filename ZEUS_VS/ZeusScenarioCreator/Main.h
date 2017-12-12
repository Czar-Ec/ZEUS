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

class Main
{
public:
	Main();
	~Main();

private:

};