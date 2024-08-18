#include "Encounter.h"
#include "../Utilities.h"

// Encounter constructor:
Encounter::Encounter(const string& name, unsigned int combatPower, unsigned int loot,
                     unsigned int damage): Event(name), combatPower(combatPower), loot(loot),
                                           damage(damage) {
}

// Function that returns the description of the monster:
string Encounter::getDescription() const {
    string description = name + " (power " + std::to_string(getCombat()) + ", loot " +
                         std::to_string(getLoot()) + ", damage " +
                         std::to_string(getDamage()) + ")";
    return description;
}

//Encounter generic getters:
unsigned int Encounter::getCombat() const {
    return combatPower;
}

unsigned int Encounter::getLoot() const {
    return loot;
}

unsigned int Encounter::getDamage() const {
    return damage;
}

// Function to be called by playTurn function with Events of Encounter type.
// It plays a turn of fighting a monster:
void Encounter::play(Player& player) {
    fight(player, player.getJob());
}

// Function to calculate the profit or damage to the player after the fight:
void Encounter::fight(Player& player, const Job& job) {
    if /** player lost **/ (getCombat() >= job.getCombat(player.getForce(),
                                                         player.getLevel())) {
        int newHealthPoints = player.getHealthPoints() - this->getDamage();
        player.setHealthPoints(newHealthPoints);
        printTurnOutcome(getEncounterLostMessage(player, getDamage()));
    }
    else /** player won **/ {
        player.setLevel(player.getLevel() + 1);
        player.setCoins(player.getCoins() + this->getLoot());
        if (job.isItCloseFighter()) {
            player.setHealthPoints(player.getHealthPoints() - 10);
        }
        printTurnOutcome(getEncounterWonMessage(player, getLoot()));

    }
    updateCombat();
}

// Generic function that allows each monster to update its combat after fight.
// The default is no change.
void Encounter::updateCombat() {
}

// Function to update combat of a Balrog:
void Balrog::updateCombat() {
    combatPower += 2;
};

// Function to update combat of a Pack. updates for each member:
void Pack::updateCombat() {
    for (unique_ptr<Encounter>& monster : members) {
        monster->updateCombat();
    }
};

// Function to get information about the Pack from each of its members:
unsigned int Pack::get(unsigned int (*getter)(const Encounter&),
                       const vector<unique_ptr<Encounter>>& members) {
    unsigned int sum = 0;
    for (const unique_ptr<Encounter>& monster : members) {
        sum += getter(*monster);
    }
    return sum;
}

// Pack Constructor:
Pack::Pack(vector<unique_ptr<Encounter>>&& membersInput) :
        Encounter("Pack", 0, 0, 0), members(std::move(membersInput)) {
    size = members.size();
}

// Pack getters that use "get" function:
unsigned int Pack::getCombat() const {
    return get([](const Encounter& encounter) { return encounter.getCombat(); },
               members);
}

unsigned int Pack::getLoot() const {
    return get([](const Encounter& encounter) {return encounter.getLoot(); },
               members);
}

unsigned int Pack::getDamage() const {
    return get([](const Encounter& encounter) {return encounter.getDamage(); },
               members);
}

// Function that returns the description of a Pack
string Pack::getDescription() const {
    string membersSize = std::to_string(this->size);
    string description = name + " of " + membersSize + " members (power " +
                         std::to_string(getCombat()) + ", loot " + std::to_string(getLoot()) +
                         ", damage " + std::to_string(getDamage()) + ")";
    return description;
}

// Monsters Constructors:
Snail::Snail() : Encounter("Snail", 5, 2, 10) {
}

Slime::Slime() : Encounter("Slime", 12, 5, 25) {
}

Balrog::Balrog() : Encounter("Balrog", 15, 100, 9001) {
}
