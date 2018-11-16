#include "Main.h"

//entry point for the simulator
int main(int argc, char** argv)
{
	try {
		Main runSim;
		return 0;
	}
	catch (const char* msg) {
		std::cerr << "Something broke\n";
	}
	
}
