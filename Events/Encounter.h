#pragma once
#include "Event.h"
#include <vector>
using std::vector;

class Encounter : public Event {
    string name;
    unsigned int combatPower;
    unsigned int loot;
    unsigned int damage;
protected:
    Encounter() = default;
public:
    string getDescription() const override;
    virtual unsigned int getCombat() const;
    virtual unsigned int getLoot() const;
    virtual unsigned int getDamage() const;
    virtual void play(Player&) override;
    void fight(Player&, const Job&);
    virtual void updateCombat();
    virtual ~Encounter() = default;
};

class Snail : public Encounter {
    string name = "Snail";
    unsigned int combatPower = 5;
    unsigned int loot = 2;
    unsigned int damage = 10;
};

class Slime : public Encounter {
    string name = "Slime";
    unsigned int combatPower = 12;
    unsigned int loot = 5;
    unsigned int damage = 25;
};

class Balrog : public Encounter {
    string name = "Balrog";
    unsigned int combatPower = 15;
    unsigned int loot = 100;
    unsigned int damage = 9001;
public:
    void updateCombat() override;
};

class Pack : public Encounter {
    string name = "Pack";
    vector<unique_ptr<Encounter>> members;
    static unsigned int get(unsigned int (*getter)(const Encounter&),
                     const vector<unique_ptr<Encounter>>& members);
public:
    void updateCombat() override;
    unsigned int getCombat() const override;
    unsigned int getLoot() const override;
    unsigned int getDamage() const override;
};