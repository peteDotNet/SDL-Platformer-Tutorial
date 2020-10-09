#include "Text.hpp"
#include <string>
#include <iostream>

#include "RenderWindow.hpp"

Text::Text(SDL_Renderer* renderer, 
	const std::string& font_path,
	int font_size,
	const std::string& message_text, 
	const SDL_Color& color)
{
	_text_texture = loadFont(font_path, font_size, message_text, color, renderer);
	SDL_QueryTexture(_text_texture, nullptr, nullptr, &_text_rect.w, &_text_rect.h);

}


void Text::dispay(int x, int y, SDL_Renderer* renderer) const
{
	_text_rect.x = x;
	_text_rect.y = y;

	SDL_RenderCopy(renderer, _text_texture, nullptr, &_text_rect);

}

SDL_Texture* Text::loadFont(const std::string& font_path, int font_size, const std::string& message_text, const SDL_Color& color, SDL_Renderer* renderer)
{
	TTF_Font* font = TTF_OpenFont(font_path.c_str(), font_size);
	if (!font) {
		std::cout << "Failed to load font" << std::endl;
	}
	auto text_surface = TTF_RenderText_Solid(font, message_text.c_str(), color);

	if (!text_surface)
		std::cout << "Failed to create surface" << std::endl;

	auto text_Texture = SDL_CreateTextureFromSurface(renderer, text_surface);

	if (!text_Texture) {
		std::cout << "Failed to create text_texture" << std::endl;

	}
	SDL_FreeSurface(text_surface);

	return text_Texture;

}



