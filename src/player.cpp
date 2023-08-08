#include "player.hpp"
#include "graphics.hpp"
#include "projectile.hpp"


Player::Player()
    //Pour changer la couleur on modifie les trois premiers paramètres
    : Character(200, 200, 200, Graphics::screenWidth / 2, Graphics::screenHeight - 40, 50, 50 , 10.0f)
{
}

Player::~Player()
{
}

void Player::update(int direction)
{
    if (direction == -1 && this->getX() > 0 + this->width / 2)
    {
        this->moveLeft();
    }
    else if (direction == 1 && this->getX() < Graphics::screenWidth - this->width / 2)
    {
        this->moveRight();
    }
}

void Player::shoot()
{
    new Projectile(0, 255, 0, this->getX(), this->getY(), -1);
}