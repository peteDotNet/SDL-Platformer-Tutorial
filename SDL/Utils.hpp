#pragma once
#include <SDL.h>
#include <string>
#include <string>

namespace utils {
	inline float hireTimeInSeconds() {
		float t = SDL_GetTicks();
		t *= 0.001f;
		return t;
	}


	bool checkForClashWithFood(Entity head, Entity& food, std::vector<Entity>& tailEntities, SDL_Texture* p_tex) {

		Vector2f headPos = head.getPos();
		Vector2f foodPos = food.getPos();

		float deltaX = abs(headPos.x - foodPos.x);
		float deltaY = abs(headPos.y - foodPos.y);

		if (deltaX < 32 && deltaY < 32) {


			Vector2f pos = Vector2f(rand() % 468, rand() % 468);
			food.SetPos(pos);

			for (int i = 0; i < 5; i++) {
				Entity bodySegment = Entity(food.getPos(), p_tex);
				tailEntities.push_back(bodySegment);
			}

			return true;
		}

		return false;

	}

	bool checkForClashWithWalls(Entity head) {
		Vector2f headPos = head.getPos();
		if (headPos.x > 468 || headPos.y > 468 || headPos.x < 0 || headPos.y < 0)
			return false;
		return true;
	}

	bool checkForClashWithSelf(Entity head, std::vector<Entity> tailEntities) {
		Vector2f headPos = head.getPos();

		int i = 0;
		for (Entity e : tailEntities)
		{
			float  deltaX = abs(headPos.x - e.getPos().x);
			float deltaY = abs(headPos.y - e.getPos().y);

			if (deltaX < 20 && deltaY < 20 && i > 10) {
				std::cout << "Clash!!" << std::endl;
				return false;
			}
			i++;		
		}
		return true;
	}


	void initBody(Entity head, std::vector<Entity>& tailEntities) {

		Vector2f nextPos = head.getPos();;
		for (Entity& e : tailEntities)
		{
			Vector2f currentPos = e.getPos();
			e.SetPos(nextPos);
			nextPos = currentPos;
		}

	}



}
