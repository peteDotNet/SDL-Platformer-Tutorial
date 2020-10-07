#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <vector>
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Utils.hpp"

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "SDL_Init has failed: " << SDL_GetError() << std::endl;

	if (!IMG_Init(IMG_INIT_PNG))
		std::cout << "IMG_init has failed: " << SDL_GetError() << std::endl;

	RenderWindow window("Game v1.0", 1280, 720);
	int windowRefreshRate = window.getRefreshRate();

	SDL_Texture* grassTexture = window.loadTexture("ground_grass_1.png");

	//Entity entities[3] = { Entity(0,0,grassTexture),
	//Entity(0,100,grassTexture),
	//Entity(100,0,grassTexture) };

	std::vector<Entity> entities = { Entity(Vector2f(0,0),grassTexture),
	Entity(Vector2f(50,0),grassTexture),
	Entity(Vector2f(0,100),grassTexture) };

	{
		Entity ent(Vector2f(100, 0), grassTexture);
		entities.push_back(ent);
	}


	bool gameRunning = true;

	SDL_Event event;

	const float timeStep = 0.01f;
	float accumlator = 0.0f;
	float currentTime = utils::hireTimeInSeconds();

	while (gameRunning) {

		int startTick = SDL_GetTicks();

		float newTime = utils::hireTimeInSeconds();
		float frameTime = newTime - currentTime;

		currentTime = newTime;

		accumlator += frameTime;

		while (accumlator >= timeStep) {

			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
					gameRunning = false;
			}

			accumlator -= timeStep;
		}

		const float alpha = accumlator / timeStep;

		window.clear();

		for (Entity& e : entities)
		{
			window.render(e);
		}


		window.display();

		int frameTicks = SDL_GetTicks() - startTick;

		if (frameTicks < 1000/ window.getRefreshRate())
			SDL_Delay((1000 / window.getRefreshRate()) - frameTicks);
	}

	window.cleanUp();


	SDL_Quit();

	return 0;
}