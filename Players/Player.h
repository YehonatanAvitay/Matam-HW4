
#pragma once

#include <string>
#include <iostream>
#include <memory>
#include "Job.h"
#include "Character.h"

using std::string;
using std::unique_ptr;

class Player {
    Player(string name, unique_ptr<Job> job, unique_ptr<Character> character);
    string name;
    unsigned int level;
    unsigned int force;
    unsigned int coins;
    unsigned int currentHealthPoints;
    unsigned int maxHealthPoints;
    bool isAlive;
    unique_ptr<Job> job;
    unique_ptr<Character> character;
public:
    /**
     * Gets the description of the player
     *
     * @return - description of the player
    */
    string getDescription() const;

    /**
     * Gets the name of the player
     *
     * @return - name of the player
    */
    string getName() const;

    /**
     * Gets the current level of the player
     *
     * @return - level of the player
    */
    int getLevel() const;

    /**
     * Gets the of force the player has
     *
     * @return - force points of the player
    */
    int getForce() const;

    /**
     * Gets the amount of health points the player currently has
     *
     * @return - health points of the player
    */
    int getHealthPoints() const;

    /**
     * Gets the amount of coins the player has
     *
     * @return - coins of the player
    */
    int getCoins() const;

    int getMaxHealthPoints() const;

    void setLevel(unsigned int);

    void setHealthPoints(int);

    void setCoins(unsigned int);

    void setForce(int);

    unsigned int getCombat() const;

    bool isMagical() const;

    bool isCloseFighter() const;

    void buy();

    bool operator<(Player&) const;
};