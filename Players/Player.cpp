#include "Player.h"

Player::Player(string name, unique_ptr<Job> job, unique_ptr<Character> character):name(name),
job(std::move(job)), character(std::move(character)) {

}

/**
    * Gets the description of the player
    *
    * @return - description of the player
   */
string Player::getDescription() const {
    string description = name + ", " + job->getName() + " with " +
            character->getName() + " character (level " + std::to_string(level)
            + ", force " + std::to_string(force) + ")";
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

void Player::setHealthPoints(int num) {
    if (num <= 0) {
        num = 0;
        isAlive = false;
    }
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

unsigned int Player::getCombat() const {
    return job->getCombat(this->force, this->level);
}

bool Player::isMagical() const {
    return job->isItMagical();
}

bool Player::isCloseFighter() const {
    return job->isItCloseFighter();
}