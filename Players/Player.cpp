#include "Player.h"
#include <iostream>
using std::cout, std::endl;

/**
    * Gets the description of the player
    *
    * @return - description of the player
   */
string Player::getDescription() const {
    string description = name + ", " + job->getJobString() + " with " +
            character->getCharacterString() + " " + character->getCharacterString() + " (level "
            + std::to_string(level) + ", force " + std::to_string(force) + ")";
    return description;
}

/**
 * Gets the name of the player
 *
 * @return - name of the player
*/
string Player::getName() const {
    return name;
}

/**
 * Gets the current level of the player
 *
 * @return - level of the player
*/
int Player::getLevel() const {
    return level;
}

/**
 * Gets the of force the player has
 *
 * @return - force points of the player
*/
int Player::getForce() const {
    return force;
}

/**
 * Gets the amount of health points the player currently has
 *
 * @return - health points of the player
*/
int Player::getHealthPoints() const {
    return currentHealthPoints;
}

/**
 * Gets the amount of coins the player has
 *
 * @return - coins of the player
*/
int Player::getCoins() const {
    return coins;
}

int Player::getMaxHealthPoints() const {
    return maxHealthPoints;
}

void Player::setLevel(unsigned int num) {
    level = num;
}

void Player::setHealthPoints(unsigned int num) {
    if (num > maxHealthPoints) {
        num = maxHealthPoints;
    }
    currentHealthPoints = num;
}

void Player::setCoins(unsigned int num) {
    coins = num;
}

bool Player::operator<(Player& player) const {
    if (this->level > player.level) {
       return true;
    }
    if (this->level == player.level) {
        if (this->coins > player.coins) {
            return true;
        }
        if (this->coins == player.coins) {
            if (this->name < player.name) {
                return true;
            }
        }
    }
    return false;
}
