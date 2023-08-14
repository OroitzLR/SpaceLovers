#include <iostream>
#include "SDL2/SDL_image.h"

#include "player.hpp"
#include "graphics.hpp"
#include "game.hpp"
#include "projectile.hpp"
#include "level.hpp"

Player *Player::instance = nullptr;

Player::Player()
	// Pour changer la couleur on modifie les trois premiers paramètres
	: Character(200, 200, 200, Graphics::screenWidth / 2 - 20, Graphics::screenHeight - 30, 40, 40, 0.02f, 100, 10, 10),
	  experience(0), numberOfProjectiles(1)
{
	Player::instance = this;
	SDL_Surface *player = IMG_Load("assets/player.png");
	this->texture = SDL_CreateTextureFromSurface(Graphics::renderer, player);
	this->timeSinceLastShot = 0;
	this->reloadSpeed = 500000000;
}

Player::~Player()
{
}

void Player::update()
{
	this->timeSinceLastShot += Game::frameTime;
	if (this->lifePoints <= 0)
	{
		this->die();
	}
	if (Game::inputs & BUTTON_LEFT && this->getX() > 0 + this->getWidth() / 2)
	{
		this->moveLeft();
	}
	else if (Game::inputs & BUTTON_RIGHT && this->getX() < Graphics::screenWidth - this->getWidth() / 2)
	{
		this->moveRight();
	}
	if (Game::inputs & BUTTON_SHOOT)
	{
		this->shoot();
	}
}

void Player::shoot()
{
	if (this->timeSinceLastShot > this->reloadSpeed)
	{
		// new Projectile(0, 255, 0, this->getX(), this->getY() - this->height, -1, 5, 0.1f);
		this->numberOfProjectiles = 3;
		for (int i = 0; i < this->numberOfProjectiles; i++)
		{
			new Projectile(0, 255, 0, this->getX() + 10 * (i + 1), this->getY() - this->getHeight() - 15 * i, 5, 0.1f, 0.2, -1, true);
			new Projectile(0, 255, 0, this->getX(), this->getY() - this->getHeight() - 15 * i, 5, 0.1f, 0, -1, true);
			new Projectile(0, 255, 0, this->getX() - 10 * (i + 1), this->getY() - this->getHeight() - 15 * i, 5, 0.1f, -0.2, -1, true);
		}
		// switch (this->numberOfProjectiles)
		// {
		// case 2:
		// 	new Projectile(0, 255, 0, this->getX() - 20, this->getY() - this->height, -1, this->power, 0.1f);
		// 	new Projectile(0, 255, 0, this->getX() + 20, this->getY() - this->height, -1, this->power, 0.1f);
		// 	break;
		// case 3:
		// 	new Projectile(0, 255, 0, this->getX() - 30, this->getY() - this->height, -1, this->power, 0.1f);
		// 	new Projectile(0, 255, 0, this->getX(), this->getY() - this->height, -1, this->power, 0.1f);
		// 	new Projectile(0, 255, 0, this->getX() + 30, this->getY() - this->height, -1, this->power, 0.1f);
		// 	break;
		// default:
		// 	new Projectile(0, 255, 0, this->getX(), this->getY() - this->height, -1, this->power, 0.1f);
		// 	break;
		// }
		// this->timeSinceLastShot = 0;
		// // new Projectile(0, 255, 0, this->getX(), this->getY() - this->height, -1, 5, 0.1f);
		// new Projectile(0, 255, 0, this->getX(), this->getY() - this->height, 5, 0.1f, 0, -1);
		// new Projectile(0, 255, 0, this->getX(), this->getY() - this->height, 5, 0.1f, 0.1, -1);
		// new Projectile(0, 255, 0, this->getX(), this->getY() - this->height, 5, 0.1f, -0.1, -1);
		this->timeSinceLastShot = 0;
	}
}

void Player::die()
{
	Level::instance->~Level();
}

void Player::gainExperience(float experience)
{
	Player::instance->experience += experience;
	char strXp[15];
	snprintf(strXp, 15, "Xp: %07.0f", Player::instance->experience);
	Level::instance->xpTotal->textUpdate(strXp);
}
