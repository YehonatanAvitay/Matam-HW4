#pragma once

#include <string>
#include <memory>
using std::string;

class Player;

class Job {
protected:
    string name;
    const unsigned int level;
    const unsigned int force;
    const int maxHealthPoints;
    const unsigned int coins;
    const bool isMagical;
    const bool isCloseFighter;
    Job(const string& name, unsigned int level, unsigned int force, unsigned int maxHealthPoints,
        unsigned int coins, bool isMagical, bool isCloseFighter);

public:
    string getName() const;
    unsigned int getLevel() const;
    unsigned int getForce() const;
    int getMaxHealthPoints() const;
    unsigned int getCoins() const;
    bool isItMagical() const;
    bool isItCloseFighter() const;
    virtual unsigned int getCombat(unsigned int force, unsigned int level) const;
    Job(const Job&) = delete;
    Job& operator=(const Job&) = delete;
    virtual std::unique_ptr<Job> clone() = 0;
    virtual ~Job() = default;
};

class Warrior : public Job {
public:
    Warrior();
    Warrior(const Warrior&) = delete;
    Warrior& operator=(const Warrior&) = delete;
    unsigned int getCombat(unsigned int force, unsigned int level) const override;
    std::unique_ptr<Job> clone() override;
};

class Archer : public Job {
public:
    Archer();
    Archer(const Archer&) = delete;
    Archer& operator=(const Archer&) = delete;
    std::unique_ptr<Job> clone() override;
};

class Magician : public Job {
public:
    Magician();
    Magician(const Magician&) = delete;
    Magician& operator=(const Magician&) = delete;
    std::unique_ptr<Job> clone() override;
};