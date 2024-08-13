#include "Job.h"
#include "Player.h"

string Job::getName() const {
    return name;
}
unsigned int Job::getLevel() const {
    return level;
}
unsigned int Job::getForce() const {
    return force;
}
unsigned int Job::getMaxHealthPoints() const {
    return maxHealthPoints;
}
unsigned int Job::getCoins() const {
    return coins;
}
bool Job::isItMagical() const {
    return this->isMagical;
}
bool Job::isItCloseFighter() const {
    return this->isCloseFighter;
}
unsigned int Job::getCombat(unsigned int force, unsigned int level) const {
    return force + level;
}
unsigned int Warrior::getCombat(unsigned int force, unsigned int level) const {
    return force * 2 + level;
}