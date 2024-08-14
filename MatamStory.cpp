
#include "MatamStory.h"
#include "PlayersFactory.h"
#include "EventFactory.h"
#include "Utilities.h"

MatamStory::MatamStory(std::istream& eventsStream, std::istream& playersStream) {
    // Open and read events file
    EventFactory eventsFactory;

    //Initiate events vector
    events = eventsFactory.createEventList(eventsStream);

    // Open and read players file
    PlayersFactory playersFactory;

    // Initiate players vector
    players = playersFactory.readPlayers(playersStream);


    this->m_turnIndex = 1;

}

void MatamStory::playTurn(Player& player) {

    // Get the next event from the events list
    Event* event = getNextEvent();

    // Print the turn details with "printTurnDetails"
    printTurnDetails(m_turnIndex, player, *event);

    // Print the turn details with "printTurnDetails"
    event->play(player); //Play the event

    m_turnIndex++;
}

void MatamStory::playRound() {

    printRoundStart();

    // Play a turn for each player
    for (unique_ptr<Player>& x: players) {
        playTurn(*x);
    }

    printRoundEnd();

    printLeaderBoardMessage();

    // Print leaderboard entry for each player
    int i = 1;
    for (unique_ptr<Player>& x: players) {
        printLeaderBoardEntry(i++,*x);
    }

    printBarrier();
}

bool MatamStory::isGameOver() const {
    /*===== TODO: Implement the game over condition =====*/
    return false; // Replace this line
    /*===================================================*/
}

void MatamStory::play() {
    printStartMessage();
    /*===== TODO: Print start message entry for each player using "printStartPlayerEntry" =====*/

    /*=========================================================================================*/
    printBarrier();

    while (!isGameOver()) {
        playRound();
    }

    printGameOver();
    /*===== TODO: Print either a "winner" message or "no winner" message =====*/

    /*========================================================================*/
}

 Event* MatamStory::getNextEvent() {

    static auto iterator = events.begin();

    if(++iterator == events.end()) {
        iterator = events.begin();
    }
    Event* eventPtr = (*iterator).get();  // get the raw pointer to nextEvent

    return eventPtr;

}
