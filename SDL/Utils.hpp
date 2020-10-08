#pragma once
#include <SDL.h>

namespace utils {
	inline float hireTimeInSeconds() {
		float t = SDL_GetTicks();
		t *= 0.001f;
		return t;
	}


	void checkForClashWithFood(Entity head, Entity& food, std::vector<Entity>& tailEntities, SDL_Texture* p_tex) {

		Vector2f headPos = head.getPos();
		Vector2f foodPos = food.getPos();

		float deltaX = abs(headPos.x - foodPos.x);
		float deltaY = abs(headPos.y - foodPos.y);

		if (deltaX < 32 && deltaY < 32) {


			Vector2f pos = Vector2f(rand() % 500, rand() % 500);
			food.SetPos(pos);

			for (int i = 0; i < 5; i++) {
				Entity bodySegment = Entity(headPos, p_tex);
				tailEntities.push_back(bodySegment);
			}
		}
	}

	bool checkForClashWithWalls(Entity head) {
		Vector2f headPos = head.getPos();
		if (headPos.x > 500 || headPos.y > 500 || headPos.x < 0 || headPos.y < 0)
			return false;
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
