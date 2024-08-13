#pragma once
#include "Player.h"
#include <string>
using std::string;


class Player;

class Job {
    const unsigned int level = 1;
    const unsigned int force = 5;
    const unsigned int maxHealthPoints = 100;
    const unsigned int coins = 10;
    bool isMagical = false;
    bool isCloseFighter = false;
    ;
public:
    unsigned int getLevel() const;
    unsigned int getForce() const;
    unsigned int getMaxHealthPoints() const;
    unsigned int getCoins() const;
    virtual unsigned int getCombat(Player& player) const = 0;
    virtual ~Job() = default;
    virtual string getJobString() const = 0;
};

class Warrior : public Job {
    const unsigned int maxHealthPoints = 150;
    bool isCloseFighter = true;
public:
    unsigned int getCombat(Player& player) const override;
    string getJobString() const override;
};

class Archer : public Job {
    const unsigned int coins = 20;
public:
    string getJobString() const override;
};

class Magician : public Job {
    bool isMagical = true;
public:
    string getJobString() const override;
};