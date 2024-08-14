#include "PlayersFactory.h"
#include <unordered_map>
#include "../Events/Event.h"
#include "../Events/Encounter.h"
#include "../Events/SpecialEvent.h"

std::vector<std::unique_ptr<Player>> PlayersFactory::readPlayers(std::istream& input) {
    std::vector<std::unique_ptr<Player>> players;
    string line;

    while (std::getline(input, line)) {
        std::istringstream lineStream(line);
        string name, jobName, characterName;

        if (!(lineStream >> name >> jobName >> characterName)) {
            throw std::runtime_error("Invalid player file");
        }

        JobFactory jobFactory;
        CharacterFactory characterFactory;

        // Create Job object based on the input
        std::unique_ptr<Job> job;
        if (jobName == "Warrior") {
            job = jobFactory.createWarrior();
        } else if (jobName == "Magician") {
            job = jobFactory.createMagician();
        } else if (jobName == "Archer") {
            job = jobFactory.createArcher();
        } else {
            throw std::runtime_error("Invalid player file");
        }

        // Create Character object based on the input
        std::unique_ptr<Character> character;
        if (characterName == "RiskTaking") {
            character = characterFactory.createRiskTaking();
        } else if (characterName == "Responsible") {
            character = characterFactory.createResponsible();
        } else {
            throw std::runtime_error("Invalid player file");
        }

        // Create a new Player and add it to the vector
        players.push_back(std::make_unique<Player>(name, std::move(job), std::move(character)));
    }

    return players;
}

unique_ptr<Warrior> PlayersFactory::JobFactory::createWarrior() {
    return std::make_unique<Warrior>();
}

unique_ptr<Archer> PlayersFactory::JobFactory::createArcher() {
    return std::make_unique<Archer>();
}

unique_ptr<Magician> PlayersFactory::JobFactory::createMagician() {
    return std::make_unique<Magician>();
}

unique_ptr<RiskTaking> PlayersFactory::CharacterFactory::createRiskTaking() {
    return std::make_unique<RiskTaking>();
}

unique_ptr<Responsible> PlayersFactory::CharacterFactory::createResponsible() {
    return std::make_unique<Responsible>();
}
