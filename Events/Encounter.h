#pragma once
#include "Event.h"
#include <vector>
using std::vector;

// Class to represent Monsters that the player can encounter during game:
class Encounter : public Event {
protected:
    unsigned int combatPower;
    unsigned int loot;
    unsigned int damage;
    Encounter(const string& name, unsigned int combatPower, unsigned int loot, unsigned int damage);
public:
    virtual string getDescription() const override;
    virtual unsigned int getCombat() const;
    virtual unsigned int getLoot() const;
    virtual unsigned int getDamage() const;
    virtual void play(Player&) override;
    void fight(Player&, const Job&);
    virtual void updateCombat();
    virtual ~Encounter() = default;
};

// Classes for each of the monsters
class Snail : public Encounter {
public:
    Snail();
    Snail(const Snail&) = delete;
    Snail& operator=(const Snail&) = delete;
};

class Slime : public Encounter {
public:
    Slime();
    Slime(const Slime&) = delete;
    Slime& operator=(const Slime&) = delete;
};

class Balrog : public Encounter {
public:
    Balrog();
    Balrog(const Balrog&) = delete;
    Balrog& operator=(const Balrog&) = delete;
    void updateCombat() override;
};

class Pack : public Encounter {
    vector<std::unique_ptr<Encounter>> members;
    int size;
    static unsigned int get(unsigned int (*getter)(const Encounter&),
                            const vector<unique_ptr<Encounter>>& members);
public:
    explicit Pack(vector<unique_ptr<Encounter>>&& members);
    Pack(const Pack&) = delete;
    Pack& operator=(const Pack&) = delete;
    void updateCombat() override;
    unsigned int getCombat() const override;
    unsigned int getLoot() const override;
    unsigned int getDamage() const override;
    string getDescription() const override;
};