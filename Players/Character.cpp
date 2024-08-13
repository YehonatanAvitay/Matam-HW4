#include "Character.h"

void RiskTaking::buy(Player & player) const {
    unsigned int coins = player.getCoins();
    unsigned int currentHealthPoints = player.getHealthPoints();
    unsigned int maxHealthPoints = player.getMaxHealthPoints();
    if (currentHealthPoints < 50 && coins >= 5) {
        currentHealthPoints += 5;
        coins -= 5;
        player.setHealthPoints(currentHealthPoints);
        player.setCoins(coins);
    }
}

string RiskTaking::getCharacterString() const {
    return "RiskTaking";
}

void Responsible::buy(Player & player) const {
    unsigned int coins = player.getCoins();
    unsigned int currentHealthPoints = player.getHealthPoints();
    unsigned int maxHealthPoints = player.getMaxHealthPoints();
    while (coins >= 5 && currentHealthPoints < maxHealthPoints) {
        coins -= 5;
        currentHealthPoints += 10;
    }
    player.setCoins(coins);
    player.setHealthPoints(currentHealthPoints);
}

string Responsible::getCharacterString() const {
    return "Responsible";
}