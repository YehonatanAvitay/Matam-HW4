#pragma once

#include <vector>
#include <memory>
#include <sstream>
#include <map>
#include "Player.h"
#include "Job.h"
#include "Character.h"


class PlayersFactory {
    class JobFactory;
    class CharacterFactory;
public:
    std::vector<std::unique_ptr<Player>> readPlayers(std::istream& input);
    std::unique_ptr<Player> createPlayer(std::istringstream& lineStream);


};

class PlayersFactory::JobFactory {
public:
    // Functions to emulate constructors of jobs
    unique_ptr<Warrior> createWarrior();
    unique_ptr<Archer> createArcher();
    unique_ptr<Magician> createMagician();
};

class PlayersFactory::CharacterFactory {
    // Map to store character creation functions
    std::map<std::string, std::unique_ptr<Character>(*)()> characterCreators;

public:
    CharacterFactory() {
        characterCreators["RiskTaking"] = &createRiskTaking;
        characterCreators["Responsible"] = &createResponsible;
    }

    // Function prototypes for character creation
    std::unique_ptr<Character> createRiskTaking();
    std::unique_ptr<Character> createResponsible();
    ;
};