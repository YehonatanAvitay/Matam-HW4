#pragma once

#include <string>
#include "Player.h"
using std::string;

class Character {
protected:
    string name;
    explicit Character(const string& name);
    Character(const Character&) = delete;
    Character& operator=(const Character&) = delete;

public:
    string getName() const;
    virtual unsigned int buy(Player&) const = 0;
    virtual ~Character() = default;
    virtual std::unique_ptr<Character> clone() = 0;

};

class RiskTaking : public Character {
public:
    RiskTaking();
    RiskTaking(const RiskTaking&) = delete;
    RiskTaking& operator=(const RiskTaking&) = delete;
    unsigned int buy(Player&) const override;
    std::unique_ptr<Character> clone() override;
};

class Responsible : public Character {
public:
    Responsible();
    Responsible(const Responsible&) = delete;
    Responsible& operator=(const Responsible&) = delete;
    unsigned int buy(Player&) const override;
    std::unique_ptr<Character> clone() override;
};