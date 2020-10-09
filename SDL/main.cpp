#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <SDL_ttf.h>
#include<sstream>


#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Utils.hpp"
#include "Text.hpp"
using namespace std;



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

	int score = 0;
	
	
	SDL_Renderer* renderer = window.GetRenderer();
	Text text = Text(renderer, "ARLRDBD.TTF", 20, "Score: 0", { 255,255,255,255 });


	SDL_Texture* snakeBody = window.loadTexture("cobraBody.png");
	SDL_Texture* snakeHead = window.loadTexture("snake.png");
	SDL_Texture* appleTexture = window.loadTexture("apple.png");

	std::vector<Entity> tailEntities = { Entity(Vector2f(200,200),snakeBody) };
	Entity head = Entity(Vector2f(50, 50), snakeHead);
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



		gameRunning = utils::checkForClashWithSelf(head, tailEntities);

		if (gameRunning)
			gameRunning = utils::checkForClashWithWalls(head);


		if (utils::checkForClashWithFood(head, food, tailEntities, snakeBody)) {

			score++;
			auto scoreString = "Score: " +  to_string(score);
			text = Text(renderer, "ARLRDBD.TTF", 20, scoreString, { 255,255,255,255 });
		}

		
		for (Entity& e : tailEntities)
		{
			window.render(e);
		}

		window.render(food);
		window.render(head);


		text.dispay(5, 475, renderer);
		window.display();


		int frameTicks = SDL_GetTicks() - startTick;

		if (frameTicks < 1000 / window.getRefreshRate())
			SDL_Delay((1000 / window.getRefreshRate()) - frameTicks);
	}



	window.clear();

	auto scoreString = "You Scored: " + to_string(score) + "!!";
	Text text1 = Text(renderer, "ARLRDBD.TTF", 50, scoreString, { 255,0,0,255 });
	text1.dispay(70, 200, renderer);

	Text text2 = Text(renderer, "ARLRDBD.TTF", 50, "Game Over!!!", { 255,0,0,255 });
	text2.dispay(70, 100, renderer);


	SDL_RenderPresent(renderer);

	SDL_Delay(3000);
	window.cleanUp();



	SDL_Quit();
	TTF_Quit();

	return 0;

}








