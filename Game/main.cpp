#include "engine.h"
//#include "GalagaGame.h"
#include "game.h"
#include "SDL.h"
#include <SDL_ttf.h>

int main(int argc, char* argv[])
{


	Engine engine;
	//GalagaGame game(&engine);
	Game game(&engine);

	game.Initialize();
	while (game.Run()) {
		game.Update();
	}
	engine.Shutdown();

	return 0;
}

