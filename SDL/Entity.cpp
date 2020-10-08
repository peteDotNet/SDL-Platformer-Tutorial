#include "Entity.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <conio.h>
#include <vector>

Entity::Entity(Vector2f p_pos, SDL_Texture* p_tex)
	:pos(p_pos), tex(p_tex), dir(STOP)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 32;
	currentFrame.h = 32;
}


SDL_Texture* Entity::getTex()
{
	return tex;
}


SDL_Rect Entity::getCurrentFrame() 
{
	return currentFrame;
}

void Entity::Input()
{
	if (_kbhit()) {
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;

		case 's':
			dir = DOWN;
			break;
	
		}
	}
}

void Entity::Move()
{

	Vector2f currentPos = getPos();
	float x = currentPos.x;
	float y = currentPos.y;

	switch (dir)
	{

	case LEFT:
		x -= 5;
		break;
	case RIGHT:
		x += 5;
		break;
	case UP:
		y -= 5;
		break;
	case DOWN:
		y += 5;
		break;
	default:
		break;
	}

	Vector2f newPostition = Vector2f(x, y);

	SetPos(newPostition);
}

