#include "Character.h"

Character::Character(const string& name) : name(name) {
}

string Character::getName() const {
    return name;
}

RiskTaking::RiskTaking(): Character("RiskTaking") {
}

unsigned int RiskTaking::buy(Player & player) const {
    unsigned int coins = player.getCoins();
    unsigned int currentHealthPoints = player.getHealthPoints();
    if (currentHealthPoints < 50 && coins >= 5) {
        currentHealthPoints += 10;
        coins -= 5;
        player.setHealthPoints(currentHealthPoints);
        player.setCoins(coins);
        return 1;
    }
    return 0;
}

std::unique_ptr<Character> RiskTaking::clone() {
    unique_ptr<Character> copy = std::make_unique<RiskTaking>();
    return copy;
}

Responsible::Responsible() : Character("Responsible") {
}

unsigned int Responsible::buy(Player & player) const {
    unsigned int coins = player.getCoins();
    unsigned int currentHealthPoints = player.getHealthPoints();
    unsigned int maxHealthPoints = player.getMaxHealthPoints();

    unsigned int counter = 0;
    while (coins >= 5 && currentHealthPoints < maxHealthPoints) {
        coins -= 5;
        currentHealthPoints += 10;
        ++counter;
    }
    player.setCoins(coins);
    player.setHealthPoints(currentHealthPoints);
    return counter;
}

std::unique_ptr<Character> Responsible::clone() {
    unique_ptr<Character> copy = std::make_unique<Responsible>();
    return copy;
}