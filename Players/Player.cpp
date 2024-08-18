#include "Player.h"

/**
 * Constructor for Player .
 *
 * Initializes a Player object with the given name, job, and character.
 *
 * @param name The name of the player.
 * @param job A unique pointer to the player's job.
 * @param character A unique pointer to the player's character.
 */
Player::Player(string name, unique_ptr<Job> job, unique_ptr<Character> character) :
        name(std::move(name)), level(job->getLevel()), force(job->getForce()),
        coins(job->getCoins()), maxHealthPoints(job->getMaxHealthPoints()),
        currentHealthPoints(maxHealthPoints), job(std::move(job)),
        character(std::move(character)) {
}

/**
 * Copy constructor for Player.
 *
 * @param other The Player object to copy from.
 */
Player::Player(const Player& other) : name(other.name), level(other.level), force(other.force),
                                      coins(other.coins), maxHealthPoints(other.maxHealthPoints),
                                      currentHealthPoints(other.currentHealthPoints), job(other.job->clone()),
                                      character(other.character->clone()), isAlive(other.isAlive) {
}

/**
 * Assignment operator for Player.
 *
 * @param other The Player object to assign from.
 * @return A reference to this Player object.
 */
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

/**
 * Gets the maximum health points of the player.
 *
 * @return The maximum health points of the player.
 */
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

/**
 * Checks if the player is still alive.
 *
 * @return True if the player is alive, false otherwise.
 */
bool Player::isStillPlaying() const {
    return isAlive;
}

/**
 * Gets a constant reference to the player's job.
 *
 * @return A constant reference to the Job object.
 */
const Job& Player::getJob() const {
    return *job;
}

/**
 * Gets a constant reference to the player's character.
 *
 * @return A constant reference to the Character object.
 */
const Character& Player::getCharacter() const {
    return *character;
}

/**
 * Sets the player's level.
 *
 * @param num The new level of the player. max value at 10.
 */
void Player::setLevel(unsigned int num) {
    if (num > 10) {
        num = 10;
    }
    level = num;
}

/**
 * Sets the player's force points.
 *
 * @param num The new force points of the player. Minimum value at 0.
 */
void Player::setForce(int num) {
    if (num < 0) {
        num = 0;
    }
    force = num;
}

/**
 * Sets the amount of coins the player has.
 *
 * @param num The new amount of coins.
 */
void Player::setCoins(unsigned int num) {
    coins = num;
}

/**
 * Sets the player's current health points.
 *
 * @param num The new amount of health points. Values are capped at 0 and the maximum health points.
 */
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

/**
 * Comparison operator: compares this Player to another Player
 * @return true if this Player is considered "less than" the other Player
 * Criteria for comparison:
 * -> Higher level is considered greater (i.e., "less than" in reverse)
 * --> If levels are equal, more coins is considered greater
 * ----> If levels and coins are equal, the Player with a lexicographically smaller name is considered less
**/

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