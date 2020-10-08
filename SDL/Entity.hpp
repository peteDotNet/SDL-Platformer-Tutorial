#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Math.hpp"

class Entity {
public:
	Entity(Vector2f p_pos, SDL_Texture* p_tex);
	


	Vector2f& getPos()
	{
		return pos;
	}

	void SetPos(Vector2f p_pos){
		pos = p_pos;
	}

	void Move();

	void Input();
	
	SDL_Texture* getTex();
	SDL_Rect getCurrentFrame();



private:
	enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
	eDirection dir;
	Vector2f pos;
	Vector2f nextPos;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
};