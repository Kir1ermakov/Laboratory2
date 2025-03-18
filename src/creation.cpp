#include "creation.h"

int Creation::getHealth() const {
    return health;
}

void Creation::setHealth(int newHealth) {
    if (newHealth >= 0)
    {
        health = newHealth;
    }
    
    else
    {
        health = 0;
    }
}