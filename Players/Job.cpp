#include "Job.h"
#include "Player.h"

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
unsigned int Job::getCombat(Player& player) const {
    return player.getForce() + player.getLevel();
}
unsigned int Warrior::getCombat(Player &player) const {
    return player.getForce() * 2 + player.getLevel();
}
string Warrior::getJobString() const {
    return "Warrior";
}
string Magician::getJobString() const {
    return "Magician";
}
string Archer::getJobString() const {
    return "Archer";
}