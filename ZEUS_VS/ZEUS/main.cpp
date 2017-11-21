#include "Main.h"

//entry point for the simulator
int main(int argc, char** argv)
{
	Main runSim;
	return 0;
}

Main::Main()
{
	//initialise
	init();

	//main loop
	mainLoop();
}


Main::~Main()
{
	close();
}

void Main::init()
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
		SDL_GetCurrentDisplayMode(0, &currentDisplay);
				
		//create the window
		window = SDL_CreateWindow(
			"ZEUS",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			//1366
			currentDisplay.w / 2,
			//768
			currentDisplay.h / 2,
			//show window on screen
			SDL_WINDOW_SHOWN 
			//resizable window
			| SDL_WINDOW_RESIZABLE
			//maximised window
			| SDL_WINDOW_MAXIMIZED
			//opengl window
			| SDL_WINDOW_OPENGL
		);

		//std::cout << oglIdx << std::endl;

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

			//initiate GUI
			gui = GUI(renderer);
		}
	}
	
}

void Main::close()
{
	//close everything
	ImGui_ImplSdlGL2_Shutdown();
	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Main::mainLoop()
{
	appRun = true;

	//keyboard input
	const Uint8 *key = SDL_GetKeyboardState(NULL);

	//debug mouse pos
	//std::cout << mousePos.x << ", " << mousePos.y << std::endl;

	//loop
	while (appRun)
	{
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
					if (eventMain.button.button == SDL_BUTTON_LEFT && key[SDL_SCANCODE_LSHIFT])
					{
						clickAndDrag = true;
					}
					break;

				//when the button is no longer pressed
				case SDL_MOUSEBUTTONUP:
					if (eventMain.button.button == SDL_BUTTON_LEFT)
					{
						clickAndDrag = false;
					}
					break;

				case SDL_MOUSEWHEEL:
					//mouse wheel for zoom control
					if (eventMain.wheel.y == -1)
					{
						//zoom in for scroll up
						gui.zoom(ZOOM_IN, mousePos);
					}
					else if (eventMain.wheel.y == 1)
					{
						//zoom out for scroll down
						gui.zoom(ZOOM_OUT, mousePos);
					}
					break;

				case SDL_KEYDOWN:
					if (eventMain.key.keysym.sym == SDLK_EQUALS)
					{
						gui.zoom(ZOOM_OUT, mousePos);
					}
					else if (eventMain.key.keysym.sym == SDLK_MINUS)
					{
						gui.zoom(ZOOM_IN, mousePos);
					}
					break;
			}

			//moving the viewport
			if (key[SDL_SCANCODE_UP]) gui.moveVPUp();
			if (key[SDL_SCANCODE_DOWN]) gui.moveVPDown();
			if (key[SDL_SCANCODE_LEFT]) gui.moveVPLeft();
			if (key[SDL_SCANCODE_RIGHT]) gui.moveVPRight();


			//ctrl + N shortcut
			if (key[SDL_SCANCODE_LCTRL] && key[SDL_SCANCODE_N] ||
				key[SDL_SCANCODE_RCTRL] && key[SDL_SCANCODE_N])
			{
				gui.ctrlN();
			}

			//ctrl + O shortcut
			if (key[SDL_SCANCODE_LCTRL] && key[SDL_SCANCODE_O] ||
				key[SDL_SCANCODE_RCTRL] && key[SDL_SCANCODE_O])
			{
				gui.ctrlO();
			}
				
			//panning
			if (clickAndDrag)
			{
				gui.pan(mousePos);
			}
			
		}

		//update frame for imgui
		ImGui_ImplSdlGL2_NewFrame(window);
		{
			ImGui::ShowMetricsWindow();
			gui.menuBar(appRun);
		}

		//draw
		updateMain();
	}

	//close components
	close();
}

void Main::updateMain()
{
	//render gui	
	gui.render(renderer);
}