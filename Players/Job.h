#pragma once

#include <string>
#include <memory>
using std::string;

class Player;

/**
 * Abstract base class representing a job in the game.
 */
class Job {
protected:
    string name;
    const unsigned int level;
    const unsigned int force;
    const int maxHealthPoints;
    const unsigned int coins;
    const bool isMagical;
    const bool isCloseFighter;

    /**
 * Constructor initializing the job with various attributes.
 *
 * @param name - Name of the job
 * @param level - Level of the job
 * @param force - Force of the job
 * @param maxHealthPoints - Maximum health points of the job
 * @param coins - Coins associated with the job
 * @param isMagical - Indicates if the job is magical
 * @param isCloseFighter - Indicates if the job is a close fighter
 */
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

    /**
     * Gets the combat value for the job based on its force and level.
     *
     * @param force - Force to be used in combat calculation
     * @param level - Level to be used in combat calculation
     * @return - Combat value
     */
    virtual unsigned int getCombat(unsigned int force, unsigned int level) const;

    // Deleted copy constructor and assignment operator to prevent copying
    Job(const Job&) = delete;
    Job& operator=(const Job&) = delete;

/**
 * Creates a clone of the job.
 * Must be overridden by derived classes.
 *
 * @return - A unique pointer to the cloned job
 */
    virtual std::unique_ptr<Job> clone() = 0;
    virtual ~Job() = default;
};

/**
 * Derived class representing a Warrior job.
 */
class Warrior : public Job {
public:
    Warrior();
    Warrior(const Warrior&) = delete;
    Warrior& operator=(const Warrior&) = delete;
    unsigned int getCombat(unsigned int force, unsigned int level) const override;
    std::unique_ptr<Job> clone() override;
};

/**
 * Derived class representing an Archer job.
 */
class Archer : public Job {
public:
    Archer();
    Archer(const Archer&) = delete;
    Archer& operator=(const Archer&) = delete;
    std::unique_ptr<Job> clone() override;
};

/**
 * Derived class representing a Magician job.
 */
class Magician : public Job {
public:
    Magician();
    Magician(const Magician&) = delete;
    Magician& operator=(const Magician&) = delete;
    std::unique_ptr<Job> clone() override;
};