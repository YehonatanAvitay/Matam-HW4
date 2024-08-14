#pragma once

#include <vector>
#include <memory>
#include <sstream>
#include <map>
#include "Player.h"
#include "Job.h"
#include "Character.h"

class PlayersFactory {

    class JobFactory {
    public:
        // Functions to emulate constructors of jobs
        unique_ptr<Warrior> createWarrior();
        unique_ptr<Archer> createArcher();
        unique_ptr<Magician> createMagician();
    };

    class CharacterFactory {
        CharacterFactory() = default;
        unique_ptr<RiskTaking> createRiskTaking();
        unique_ptr<Responsible> createResponsible();

    };

public:
    std::vector<std::unique_ptr<Player>> readPlayers(std::istream& input);

    void changeCharacter(Player& player, string characterName);
    void changeJob(Player& player, string JobName);


};





