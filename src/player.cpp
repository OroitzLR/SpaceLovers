#include <iostream>

#include "player.hpp"
#include "graphics.hpp"
#include "game.hpp"
#include "projectile.hpp"
#include "level.hpp"

Player *Player::instance = nullptr;

Player::Player()
	// Pour changer la couleur on modifie les trois premiers paramètres
	// Demander difference dans le constructeur
	// Demander si il faut qu'il le reçoive la speed en params pour pouvoir la modifier
	// demander pour l'ajout de power et defense (comment proceder et ou initialiser)
	: Character(200, 200, 200, Graphics::screenWidth / 2 - 20, Graphics::screenHeight - 30, 40, 40, 0.02f, 100)
{
	Player::instance = this;
	this->timeSinceLastShot = 0;
	this->experience = 0.0f;
	this->numberOfProjectiles = 3;
	this->power = 1;
	this->defense = 1;
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
	if (Game::inputs & BUTTON_LEFT && this->getX() > 0 + this->width / 2)
	{
		this->moveLeft();
	}
	else if (Game::inputs & BUTTON_RIGHT && this->getX() < Graphics::screenWidth - this->width / 2)
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
		switch (this->numberOfProjectiles)
		{
		case 2:
			new Projectile(0, 255, 0, this->getX() - 20, this->getY() - this->height, -1, 5, 0.1f);
			new Projectile(0, 255, 0, this->getX() + 20, this->getY() - this->height, -1, 5, 0.1f);
			break;
		case 3:
			new Projectile(0, 255, 0, this->getX() - 30, this->getY() - this->height, -1, 5, 0.1f);
			new Projectile(0, 255, 0, this->getX(), this->getY() - this->height, -1, 5, 0.1f);
			new Projectile(0, 255, 0, this->getX() + 30, this->getY() - this->height, -1, 5, 0.1f);
			break;
		default:
			new Projectile(0, 255, 0, this->getX(), this->getY() - this->height, -1, 5, 0.1f);
			break;
		}
		this->timeSinceLastShot = 0;
	}
}

void Player::die()
{
	Level::instance->~Level();
}
