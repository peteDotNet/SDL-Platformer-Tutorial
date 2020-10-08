#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <SDL_ttf.h>


#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Utils.hpp"



int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "SDL_Init has failed: " << SDL_GetError() << std::endl;

	if (!IMG_Init(IMG_INIT_PNG))
		std::cout << "IMG_init has failed: " << SDL_GetError() << std::endl;

	if (TTF_Init() == -1)
		std::cout << "TTF_init has failed: " << SDL_GetError() << std::endl;
		

	RenderWindow window("Game v1.0", 500, 500);
	int windowRefreshRate = window.getRefreshRate();

	SDL_Texture* snakeBody = window.loadTexture("cobraBody.png");
	SDL_Texture* snakeHead = window.loadTexture("snake.png");
	SDL_Texture* appleTexture = window.loadTexture("apple.png");

	std::vector<Entity> tailEntities = { Entity(Vector2f(200,200),snakeBody) };
	Entity head = Entity(Vector2f(50,50),snakeHead);
	Entity food = Entity(Vector2f(100, 100), appleTexture);



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

		
		utils::initBody(head, tailEntities);

		head.Input();
		head.Move();



		gameRunning =  utils::checkForClashWithWalls(head);

		utils::checkForClashWithFood(head, food, tailEntities, snakeBody);

		for (Entity& e : tailEntities)
		{
			window.render(e);
		}

		window.render(food);
		window.render(head);



		window.display();

		int frameTicks = SDL_GetTicks() - startTick;

		if (frameTicks < 1000 / window.getRefreshRate())
			SDL_Delay((1000 / window.getRefreshRate()) - frameTicks);
	}



	window.clear();




	SDL_Delay(5000);
	window.cleanUp();



	SDL_Quit();
	TTF_Quit();

	return 0;

}








