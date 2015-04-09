#include "player.h"

Player::Player(QString name, bool infected, QObject *parent) :
    QObject(parent), originInfected(infected), potion(0),
    infected(infected), name(name)
{
    goodContacted.clear();
}

Player::~Player()
{
}

inline int Player::getPotion() const
{
    return potion;
}

inline bool Player::isInfected() const
{
    return infected;
}

QString Player::getName() const
{
    return name;
}

//use it only when restarting the game
void Player::reset()
{
    potion = 0;
    infected = originInfected;
}

void Player::infect()
{
    infected = true;
}

void Player::cure()
{
    infected = false;
}

void Player::takePills()
{
    if ( potion )
    {
        potion--;
        infected = false;
    }
}

void Player::contactwith(Player *p)
{
    if ( !p->isInfected() && !isInfected()
         && goodContacted.indexOf(p)==-1)
    {
        p->potion++;
        potion++;
        goodContacted << p;
        p->goodContacted << this;
    } else

    if ( p->isInfected() ^ isInfected() )
    {
        Player *good, *evil;
        if ( p->isInfected() )
        {
            good = this;
            evil = p;
        } else {
            good = p;
            evil = this;
        }
        if ( good->getPotion() )
        {
            good->potion--;
            evil->cure();
        }
        good->infect();
    }
}
