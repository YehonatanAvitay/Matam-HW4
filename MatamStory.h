#pragma once


#include <iostream>
#include <vector>
#include "Players/Player.h"
#include "Events/Event.h"


class MatamStory {

private:
    std::vector<unique_ptr<Player>> players;
    std::vector<unique_ptr<Event>> events;

    Event& getNextEvent();
    unsigned int m_turnIndex;

    /**
     * Playes a single turn for a player
     *
     * @param player - the player to play the turn for
     *
     * @return - void
    */
    void playTurn(Player& player);

    /**
     * Plays a single round of the game
     *
     * @return - void
    */
    void playRound();

    /**
     * Checks if the game is over
     *
     * @return - true if the game is over, false otherwise
    */
    bool isGameOver() const;
    static bool comparePlayerPointers(const unique_ptr<Player>& player1,
                                      const unique_ptr<Player>& player2);
    void printLeaderBoard(const std::vector<unique_ptr<Player>>& playersList) const;
    void determineWinner();

    /*
     * Class Factory is defined inside the private section of MatamStory in order to make sure
     * only MatamStory methods can use Factory methods.
     */
    class Factory;

public:

    /**
     * Constructor of MatamStory class
     *
     * @param eventsStream - events input stream (file)
     * @param playersStream - players input stream (file)
     *
     * @return - MatamStory object with the given events and players
     *
    */
    MatamStory(std::istream& eventsStream, std::istream& playersStream);

    /**
     * Plays the entire game
     *
     * @return - void
    */
    void play();
};
