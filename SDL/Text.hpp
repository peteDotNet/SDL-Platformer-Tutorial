#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class Text
{
public:
	Text( SDL_Renderer* renderer, const std::string& font_path, int font_size, const std::string& message_text, const SDL_Color& color);
	
	void dispay(int x, int y, SDL_Renderer* renderer) const;

	static SDL_Texture* loadFont(const std::string& font_path, int font_size, const std::string& message_text, const SDL_Color& color, SDL_Renderer* renderer);;

private:
	SDL_Texture* _text_texture = nullptr;
	mutable SDL_Rect _text_rect;

};
