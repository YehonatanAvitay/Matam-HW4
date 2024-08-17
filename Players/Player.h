#pragma once

#include <string>
#include <iostream>
#include <memory>
#include "Job.h"
#include "Character.h"

class Character;

using std::string;
using std::unique_ptr;

class Player {
    string name;
    unsigned int level;
    unsigned int force;
    unsigned int coins;
    int maxHealthPoints;
    unsigned int currentHealthPoints;
    unique_ptr<Job> job;
    unique_ptr<Character> character;
    bool isAlive = true;

public:
    // Constructor:
    Player(string name, unique_ptr<Job> job, unique_ptr<Character> character);
    Player(const Player&);
    Player& operator=(const Player&);

    // Getters:
    string getDescription() const;
    string getName() const;
    int getLevel() const;
    int getForce() const;
    int getCoins() const;
    int getMaxHealthPoints() const;
    int getHealthPoints() const;
    bool isStillPlaying() const;
    const Job& getJob() const;
    const Character& getCharacter() const;

    // Setters:
    void setLevel(unsigned int);
    void setForce(int);
    void setCoins(unsigned int);
    void setHealthPoints(int);

    // Comparison Operator:
    bool operator<(const Player&) const;
};