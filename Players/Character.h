#pragma once
#include "Player.h"
#include <string>
using std::string;

class Player;

class Character {
public:
    virtual void buy(Player&) const = 0;
    virtual ~Character();
    virtual string getCharacterString() const = 0;
};

class RiskTaking : public Character {
public:
    void buy(Player&) const override;
    string getCharacterString() const override;
};

class Responsible : public Character {
public:
    void buy(Player&) const override;
    string getCharacterString() const override;
};