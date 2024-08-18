#include "MatamStory.h"
#include "Events/Factory.h"
#include "Players/Player.h"
#include "Players/Job.h"
#include "Utilities.h"
#include <set>

MatamStory::MatamStory(std::istream& eventsStream, std::istream& playersStream) {
    //Initiate events vector
    events = Factory::createEventList(eventsStream);

    // Initiate players vector
    players = Factory::readPlayers(playersStream);

    this->m_turnIndex = 1;
}

void MatamStory::playTurn(Player& player) {

    // Get the next event from the events list
    Event& event = getNextEvent();

    // Print the turn details with "printTurnDetails"
    printTurnDetails(m_turnIndex, player, event);

    // Print the turn details with "printTurnDetails"
    event.play(player); //Play the event

    m_turnIndex++;
}

void MatamStory::playRound() {

    printRoundStart();

    // Play a turn for each player
    for (unique_ptr<Player>& player: players) {
        if(player->isStillPlaying())
            playTurn(*player);
    }

    printRoundEnd();

    printLeaderBoardMessage();

    // Print leaderboard entry for each player
    printLeaderBoard(players);

    printBarrier();
}

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

void MatamStory::play() {
    printStartMessage();

    int index = 1;
    for (unique_ptr<Player>& player: players) {
        printStartPlayerEntry(index++, *player);
    }

    printBarrier();

    while (!isGameOver()) {
        playRound();
    }

    printGameOver();
    determineWinner();
}

void MatamStory::printLeaderBoard(const std::vector<unique_ptr<Player>>& playersList) const {
    std::set<Player> orderedPlayersList;
    for (const unique_ptr<Player>& player : players) {
        orderedPlayersList.insert(*player);
    }
    int i = 1;
    for (const Player& player : orderedPlayersList) {
        printLeaderBoardEntry(i, player);
        i++;
    }
}

void MatamStory::determineWinner() {
    std::sort(players.begin(), players.end(), comparePlayerPointers);
    if(players[0]->getLevel() == 10) {
        printWinner(*players[0]);
        return;
    }
    printNoWinners();
}

bool MatamStory::comparePlayerPointers(const unique_ptr<Player>& player1,
                                       const unique_ptr<Player>& player2) {
    return *player1 < *player2;
}

Event& MatamStory::getNextEvent() {
    static auto iterator = --events.end();

    if(++iterator == events.end()) {
        iterator = events.begin();
    }

    Event& nextEvent = *(*iterator);
    return nextEvent;
}