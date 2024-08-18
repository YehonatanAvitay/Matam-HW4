#include "Character.h"

// Character constructor: Initializes the character with the given name.
Character::Character(const string& name) : name(name) {
}

// Returns the name of the character.
string Character::getName() const {
    return name;
}

// RiskTaking constructor: Initializes RiskTaking with the name "RiskTaking".
RiskTaking::RiskTaking(): Character("RiskTaking") {
}

// RiskTaking's implementation of buy: Increases the player's health if
// health is low and coins are sufficient.
// Deducts coins and returns 1 if health is increased, otherwise returns 0.
unsigned int RiskTaking::buy(Player & player) const {
    unsigned int coins = player.getCoins();
    unsigned int currentHealthPoints = player.getHealthPoints();
    if (currentHealthPoints < 50 && coins >= 5) {
        currentHealthPoints += 10;
        coins -= 5;
        player.setHealthPoints(currentHealthPoints);
        player.setCoins(coins);
        return 1; // Successful purchase
    }
    return 0; // Purchase not possible
}

// Creates a clone of the RiskTaking character and returns it.
std::unique_ptr<Character> RiskTaking::clone() {
    unique_ptr<Character> copy = std::make_unique<RiskTaking>();
    return copy;
}

// Responsible constructor: Initializes Responsible with the name "Responsible".
Responsible::Responsible() : Character("Responsible") {
}

// Responsible's implementation of buy: Increases the player's health in increments of 10
// as long as coins are available and health is below maximum.
// Returns the number of successful purchases.
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

// Creates a clone of the Responsible character and returns it.
std::unique_ptr<Character> Responsible::clone() {
    unique_ptr<Character> copy = std::make_unique<Responsible>();
    return copy;
}