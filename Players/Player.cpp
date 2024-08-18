#include "Player.h"

Player::Player(string name, unique_ptr<Job> job, unique_ptr<Character> character) :
        name(std::move(name)), level(job->getLevel()), force(job->getForce()),
        coins(job->getCoins()), maxHealthPoints(job->getMaxHealthPoints()),
        currentHealthPoints(maxHealthPoints), job(std::move(job)),
        character(std::move(character)) {
}

Player::Player(const Player& other) : name(other.name), level(other.level), force(other.force),
                                      coins(other.coins), maxHealthPoints(other.maxHealthPoints),
                                      currentHealthPoints(other.currentHealthPoints), job(other.job->clone()),
                                      character(other.character->clone()), isAlive(other.isAlive) {
}

Player& Player::operator=(const Player& other) {
    name = other.name;
    level = other.level;
    force = other.force;
    coins = other.coins;
    maxHealthPoints = other.maxHealthPoints;
    currentHealthPoints = other.currentHealthPoints;
    job = other.job->clone();
    character = other.character->clone();
    isAlive = other.isAlive;
    return *this;
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

/**
 * Gets the amount of health points the player currently has
 *
 * @return - health points of the player
*/
int Player::getHealthPoints() const {
    return currentHealthPoints;
}

bool Player::isStillPlaying() const {
    return isAlive;
}

const Job& Player::getJob() const {
    return *job;
}

const Character& Player::getCharacter() const {
    return *character;
}

void Player::setLevel(unsigned int num) {
    if (num > 10) {
        num = 10;
    }
    level = num;
}

void Player::setForce(int num) {
    if (num < 0) {
        num = 0;
    }
    force = num;
}

void Player::setCoins(unsigned int num) {
    coins = num;
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

bool Player::operator<(const Player& player) const {
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