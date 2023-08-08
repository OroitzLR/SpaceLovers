#include <SDL2/SDL.h>
#include "character.hpp"
#include "projectile.hpp"
#include "level.hpp"
#include "graphics.hpp"

Projectile::Projectile(int r, int g, int b, SDL_Rect rect, int direction)
	: Character(r, g, b, rect, 1.0f),
	  direction(direction)

{
	Level::projectiles.insert(this);
}

Projectile::~Projectile()
{
	Level::projectiles.erase(this);
}

void Projectile::update()
{
	if (this->direction == 1)
		this->moveDown();
	else if (this->direction == -1)
		this->moveUp();

	// if (SDL_HasIntersection(&this->rect, &Level::player->rect))
	// {
	// 	Level::player->takeDamage(1);
	// 	this->~Projectile();
	// 	return;
	// }

	if (this->rect.y > Graphics::screenHeight || this->rect.y < 0 || this->rect.x > Graphics::screenWidth || this->rect.x < 0)
	{
		this->~Projectile();
	}
}