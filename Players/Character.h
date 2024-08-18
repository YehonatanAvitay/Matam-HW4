#pragma once

#include <string>
#include "Player.h"
using std::string;

/**
 * Abstract base class representing a character in the game.
 */
class Character {
protected:
    string name;

    // Constructor initializing the character with a name
    explicit Character(const string& name);

    // Deleting copy constructor and assignment operator to prevent copying
    Character(const Character&) = delete;
    Character& operator=(const Character&) = delete;

public:
    string getName() const;

    // Abstract method for buying action; must be overridden in derived classes
    virtual unsigned int buy(Player&) const = 0;
    virtual ~Character() = default;
    virtual std::unique_ptr<Character> clone() = 0;

};

// Derived class representing a risk-taking character
class RiskTaking : public Character {
public:
    RiskTaking();
    RiskTaking(const RiskTaking&) = delete;
    RiskTaking& operator=(const RiskTaking&) = delete;
    unsigned int buy(Player&) const override;
    std::unique_ptr<Character> clone() override;
};

// Derived class representing a responsible character
class Responsible : public Character {
public:
    Responsible();
    Responsible(const Responsible&) = delete;
    Responsible& operator=(const Responsible&) = delete;
    unsigned int buy(Player&) const override;
    std::unique_ptr<Character> clone() override;
};