#pragma once
#include "Player.h"
#include <string>
using std::string;

class Player;

class Character {
    string name;

public:
    string getName() const;
    virtual void buy(Player&) const = 0;
    virtual ~Character() = default;
};

class RiskTaking : public Character {
    string name = "RiskTaking";
public:
    void buy(Player&) const override;
};

class Responsible : public Character {
    string name = "Responsible";
public:
    void buy(Player&) const override;
};