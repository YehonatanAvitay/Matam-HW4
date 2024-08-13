#pragma once
#include "Player.h"
#include <string>
using std::string;


class Player;

class Job {
    string name;
    const unsigned int level = 1;
    const unsigned int force = 5;
    const unsigned int maxHealthPoints = 100;
    const unsigned int coins = 10;
    const bool isMagical = false;
    const bool isCloseFighter = false;
    ;
public:
    string getName() const;
    unsigned int getLevel() const;
    unsigned int getForce() const;
    unsigned int getMaxHealthPoints() const;
    unsigned int getCoins() const;
    bool isItMagical() const;
    bool isItCloseFighter() const;
    virtual unsigned int getCombat(unsigned int force, unsigned int level) const = 0;
    virtual ~Job() = default;
};

class Warrior : public Job {
    string name = "Warrior";
    const unsigned int maxHealthPoints = 150;
    const bool isCloseFighter = true;
public:
    unsigned int getCombat(unsigned int force, unsigned int level) const override;
};

class Archer : public Job {
    string name = "Archer";
    const unsigned int coins = 20;
};

class Magician : public Job {
    string name = "Magician";
    const bool isMagical = true;
};