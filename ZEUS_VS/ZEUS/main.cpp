#include "Main.h"
//
//int main(int argc, char** argv)
//{
//	SDL_Window *window = nullptr;
//	SDL_DisplayMode currentDisplay;
//	//simulation renderer
//	SDL_Renderer *renderer;
//	//opengl context
//	//SDL_GLContext glcontext;
//	
//
//	//initialise SDL
//	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
//	{
//		//debug output
//		std::cerr << "Error: " << SDL_GetError() << std::endl;
//		exit(0);
//	}
//
//	else
//	{
//		// Setup window
//		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
//		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
//		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
//		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
//		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
//		SDL_GetCurrentDisplayMode(0, &currentDisplay);
//
//		//create the window
//		window = SDL_CreateWindow(
//			"ZEUS",
//			SDL_WINDOWPOS_CENTERED,
//			SDL_WINDOWPOS_CENTERED,
//			//1366
//			currentDisplay.w / 2,
//			//768
//			currentDisplay.h / 2,
//			//show window on screen
//			SDL_WINDOW_SHOWN
//			//resizable window
//			| SDL_WINDOW_MAXIMIZED
//			//opengl window
//			//| SDL_WINDOW_OPENGL
//		);
//
//		//opengl context
//		//glcontext = SDL_GL_CreateContext(window);
//
//		//check if window was created
//		if (window == NULL)
//		{
//			std::cout << "SDL Window error: " << SDL_GetError() << std::endl;
//			//exit the program
//			exit(0);
//		}
//		//continue setup
//		else
//		{
//			//initialise IMGUI
//			//ImGui_ImplSdlGL2_CreateDeviceObjects();
//			//ImGui_ImplSdlGL2_InvalidateDeviceObjects();
//			ImGui_ImplSdlGL2_Init(window);
//
//			//find GPU drivers
//			int oglIdx = -1;
//			int nRD = SDL_GetNumRenderDrivers();
//			for (int i = 0; i < nRD; i++)
//			{
//				SDL_RendererInfo info;
//				if (!SDL_GetRenderDriverInfo(i, &info))
//				{
//					if (!strcmp(info.name, "opengl"))
//					{
//						oglIdx = i;
//					}
//				}
//			}
//
//			//create the renderer, linking the number of GPU drivers
//			renderer = SDL_CreateRenderer(window, oglIdx,
//				SDL_RENDERER_ACCELERATED
//				| SDL_RENDERER_PRESENTVSYNC
//			);
//
//
//
//			//initiate glew
//			glewExperimental = true;
//			glewInit();
//
//			//setup ImGui style
//			//ImGuiStyle &style = ImGui::GetStyle();
//			//style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.6f, 0.0f, 0.0f, 1.0f);
//
//			//allow transparency
//			//SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
//		}
//	}
//
//	bool appRun = true;
//	SDL_Event eventMain;
//
//	//loop
//	while (appRun)
//	{
//		SDL_Point mousePos;
//		
//		//update mouse position
//		SDL_GetMouseState(&mousePos.x, &mousePos.y);
//		//std::cout << mousePos.x << ", " << mousePos.y << std::endl;
//		
//		//check for inputs
//		while (SDL_PollEvent(&eventMain) != 0)
//		{
//
//			//process event for IMGUI
//			ImGui_ImplSdlGL2_ProcessEvent(&eventMain);
//
//			if (eventMain.type == SDL_QUIT)
//			{
//				appRun = false;
//			}
//		}
//
//		//update frame for imgui
//		ImGui_ImplSdlGL2_NewFrame(window);
//		{
//			ImGui::ShowMetricsWindow();
//
//			//menubar
//			ImGui::BeginMainMenuBar();
//			//File
//			if (ImGui::BeginMenu("File"))
//			{
//				//Make a new simulation
//				if (ImGui::MenuItem("New Simulation", "CTRL+N"))
//				{
//					std::cout << "New Sim\n";
//				}
//
//				ImGui::EndMenu();
//			}
//			ImGui::EndMainMenuBar();
//		}
//
//
//		///////////////////////////////////////////////////////////////////////////////
//		//Rendering
//		SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
//		SDL_RenderClear(renderer);
//		SDL_Rect vp;
//		//get window size
//		vp.w = (int)ImGui::GetIO().DisplaySize.x;
//		vp.h = (int)ImGui::GetIO().DisplaySize.y;
//
//		//link viewport to the renderer
//		SDL_RenderSetViewport(renderer, &vp);
//
//
//		//render the world map
//		//SDL_RenderCopy(renderer, worldMap, NULL, NULL);
//
//		//render the IMGUI elements
//		glUseProgram(0);
//		ImGui::Render();
//
//		//update the screen
//		SDL_RenderPresent(renderer);
//	}
//	
//	return 0;
//}


//entry point for the simulator
int main(int argc, char** argv)
{
	Main runSim;
	return 0;
}
