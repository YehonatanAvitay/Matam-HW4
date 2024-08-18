#include "Job.h"

// Job Constructor
Job::Job(const string& name, unsigned int level, unsigned int force, unsigned int maxHealthPoints,
         unsigned int coins, bool isMagical, bool isCloseFighter) : name(name), level(level),
                                                                    force(force), maxHealthPoints(maxHealthPoints), coins(coins), isMagical(isMagical),
                                                                    isCloseFighter(isCloseFighter) {
}


string Job::getName() const {
    return name;
}

unsigned int Job::getLevel() const {
    return level;
}

unsigned int Job::getForce() const {
    return force;
}

int Job::getMaxHealthPoints() const {
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

// Default implementation of getCombat: Returns sum of force and level.
unsigned int Job::getCombat(unsigned int force, unsigned int level) const {
    return force + level;
}

Warrior::Warrior(): Job("Warrior", 1, 5, 150, 10,
                        false, true) {
}

// Warrior's implementation of getCombat: Returns double the force plus level.
unsigned int Warrior::getCombat(unsigned int force, unsigned int level) const {
    return force * 2 + level;
}

Archer::Archer(): Job("Archer", 1, 5, 100, 20,
                      false, false) {
}

Magician::Magician() : Job("Magician", 1, 5, 100, 10,
                           true, false) {
}

std::unique_ptr<Job> Warrior::clone() {
    std::unique_ptr<Job> copy = std::make_unique<Warrior>();
    return copy;
}

std::unique_ptr<Job> Archer::clone() {
    std::unique_ptr<Job> copy = std::make_unique<Archer>();
    return copy;
}

std::unique_ptr<Job> Magician::clone() {
    std::unique_ptr<Job> copy = std::make_unique<Magician>();
    return copy;
}