#include "Character.h"

string Character::getName() const {
    return name;
}

void RiskTaking::buy(Player & player) const {
    unsigned int coins = player.getCoins();
    unsigned int currentHealthPoints = player.getHealthPoints();
    if (currentHealthPoints < 50 && coins >= 5) {
        currentHealthPoints += 5;
        coins -= 5;
        player.setHealthPoints(currentHealthPoints);
        player.setCoins(coins);
    }
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