#include "Encounter.h"

void Encounter::play(Player& player) {
    if (this->combatPower >= player.getCombat()) {
        int newHealthPoints = player.getHealthPoints() - this->getDamage();
        player.setHealthPoints(newHealthPoints);
    }
    else {
        player.setLevel(player.getLevel() + 1);
        player.setCoins(player.getCoins() + this->getLoot());
        if (player.isCloseFighter()) {
            player.setHealthPoints(player.getHealthPoints() - 10);
        }
    }
    updateCombat();
}

string Encounter::getDescription() const {
   string description = name + " ( power " + std::to_string(combatPower) + ", loot " +
           std::to_string(loot) + ", damage " + std::to_string(damage) + ")";
    return description;
}

unsigned int Encounter::getCombat() const {
    return combatPower;
}
unsigned int Encounter::getLoot() const {
    return loot;
}
unsigned int Encounter::getDamage() const {
    return damage;
}

void Encounter::updateCombat() {
}
void Balrog::updateCombat() {
    combatPower += 2;
};

void Pack::updateCombat() {
    for (unique_ptr<Encounter>& monster : members) {
        monster->updateCombat();
    }
};

unsigned int get(unsigned int (*getter)(const Encounter&),
                 const vector<unique_ptr<Encounter>>& members) {
    unsigned int sum = 0;
    for (const unique_ptr<Encounter>& monster : members) {
        sum += getter(*monster);
    }
    return sum;
}

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
