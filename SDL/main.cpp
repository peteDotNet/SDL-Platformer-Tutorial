#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <vector>
#include "RenderWindow.hpp"
#include "Entity.hpp"

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "SDL_Init has failed: " << SDL_GetError() << std::endl;

	if (!IMG_Init(IMG_INIT_PNG))
		std::cout << "IMG_init has failed: " << SDL_GetError() << std::endl;

	RenderWindow window("Game v1.0", 1280, 720);

	SDL_Texture* grassTexture = window.loadTexture("ground_grass_1.png");

	//Entity entities[3] = { Entity(0,0,grassTexture),
	//Entity(0,100,grassTexture),
	//Entity(100,0,grassTexture) };

	std::vector<Entity> entities = { Entity(0,0,grassTexture),
	Entity(0,100,grassTexture),
	Entity(100,0,grassTexture) };

	{
		Entity ent(100, 100, grassTexture);
		entities.push_back(ent);
	}
	

	bool gameRunning = true;

	SDL_Event event;

	while (gameRunning) {
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				gameRunning = false;
		}
		window.clear();

		for (Entity& e : entities)
		{
			window.render(e);
		}
		window.display();
	}

	window.cleanUp();


	SDL_Quit();

	return 0;
}