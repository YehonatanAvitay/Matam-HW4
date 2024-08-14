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
};

class PlayersFactory::JobFactory {
public:
    // Functions to emulate constructors of jobs
    unique_ptr<Warrior> createWarrior();
    unique_ptr<Archer> createArcher();
    unique_ptr<Magician> createMagician();
};

class PlayersFactory::CharacterFactory {
public:
    unique_ptr<RiskTaking> createRiskTaking();
    unique_ptr<Responsible> createResponsible();
};