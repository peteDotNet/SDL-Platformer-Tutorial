#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class Text
{
public:
	Text(const std::string& font_path, int font_size, const std::string& message_text, const SDL_Color& color);

	void display() const;

	static SDL_Texture loadFont(const std::string& font_path, int font_size, const std::string& message_text, const SDL_Color& color);

private:
	SDL_Texture* _text_texture = nullptr;
	SDL_Rect _text_rect;
};
