#include "Character.h"
#include "Player.h"

string Character::getName() const {
    return name;
}

unsigned int RiskTaking::buy(Player & player) const {
    unsigned int coins = player.getCoins();
    unsigned int currentHealthPoints = player.getHealthPoints();
    if (currentHealthPoints < 50 && coins >= 5) {
        currentHealthPoints += 5;
        coins -= 5;
        player.setHealthPoints(currentHealthPoints);
        player.setCoins(coins);
        return 1;
    }
    return 0;
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