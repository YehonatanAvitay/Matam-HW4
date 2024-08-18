#include "MatamStory.h"
#include "Events/Factory.h"
#include "Players/Player.h"
#include "Players/Job.h"
#include "Utilities.h"
#include <set>

// MatamStory Constructor. constructs Players list and Events list:
MatamStory::MatamStory(std::istream& eventsStream, std::istream& playersStream) {
    //Initiate events vector
    events = Factory::createEventsList(eventsStream);

    // Initiate players vector
    players = Factory::createPlayersList(playersStream);

    this->m_turnIndex = 1;
}

// Function that plays one turn. in every turn a player meets an event and it's data is changed:
void MatamStory::playTurn(Player& player) {

    // Get the next event from the events list
    Event& event = getNextEvent();

    // Print the turn details with "printTurnDetails"
    printTurnDetails(m_turnIndex, player, event);

    // Print the turn details with "printTurnDetails"
    event.play(player); //Play the event

    m_turnIndex++;
}

// Function that plays a round. In every round all the players who are alive play by their original
// order, then the sorted players list is printed:
void MatamStory::playRound() {

    printRoundStart();

    // Play a turn for each player
    for (unique_ptr<Player>& player: players) {
        if(player->isStillPlaying())
            playTurn(*player);
    }

    printRoundEnd();

    printLeaderBoardMessage();

    // Print leaderboard entry for each player by sorted order
    printLeaderBoard(players);

    printBarrier();
}

// Function that checks if the game is over:
bool MatamStory::isGameOver() const {
    // check if one of the players got to level 10:
    for (const unique_ptr<Player>& player: players) {
        if (player->getLevel() == 10) {
            return true;
        }
    }
    // if no player got to level 10, check if there is still someone alive:
    for (const unique_ptr<Player>& player: players) {
        if (player->isStillPlaying()) {
            return false;
        }
    }
    // if all the players are dead the game is over:
    return true;
}

// Function that wraps the whole game.
// As long as there is one player alive, new rounds are played until all are dead or someone won:
void MatamStory::play() {
    printStartMessage();

    int index = 1;
    for (unique_ptr<Player>& player: players) {
        printStartPlayerEntry(index++, *player);
    }

    printBarrier();

    // As long as the game isn't over, play another round
    while (!isGameOver()) {
        playRound();
    }

    printGameOver();
    determineWinner();
}

// Function that sorts the Players list, then prints it,
// without changing the order of the original list:
void MatamStory::printLeaderBoard(const std::vector<unique_ptr<Player>>& playersList) const {
    // Sort the Players list
    std::set<Player> orderedPlayersList;
    for (const unique_ptr<Player>& player : players) {
        orderedPlayersList.insert(*player);
    }
    // Print sorted leaderboard
    int i = 1;
    for (const Player& player : orderedPlayersList) {
        printLeaderBoardEntry(i, player);
        i++;
    }
}

// Function that determines the winner.
// The highest player in the sorted list is the winner if they are in level 10:
void MatamStory::determineWinner() {
    std::sort(players.begin(), players.end(), comparePlayerPointers);
    if(players[0]->getLevel() == 10) {
        printWinner(*players[0]);
        return;
    }
    printNoWinners();
}

// Function to sort the smart pointers list:
bool MatamStory::comparePlayerPointers(const unique_ptr<Player>& player1,
                                       const unique_ptr<Player>& player2) {
    return *player1 < *player2;
}

// Function to determine the next Event:
Event& MatamStory::getNextEvent() {
    // Set to the last Event so that in the first turn it will be advanced to the first Event
    static auto iterator = --events.end();

    if(++iterator == events.end()) {
        iterator = events.begin();
    }

    // Return reference to the Event saved in the vector
    Event& nextEvent = *(*iterator);
    return nextEvent;
}