#pragma once

#include <unordered_map>
#include <functional>
#include <memory>
#include <string>
#include <sstream>
#include <stdexcept>
#include <vector>

//class Player;
//class Job;
//class Character;
//class Warrior;
//class Archer;
//class Magician;
//class RiskTaking;
//class Responsible;

class PlayersFactory {
private:
    static const std::unordered_map<std::string, std::function<std::unique_ptr<Job>()>> jobFactoriesMap;
    static const std::unordered_map<std::string, std::function<std::unique_ptr<Character>()>> characterFactoriesMap;

public:
    static std::vector<std::unique_ptr<Player>> readPlayers(std::istream& input);

private:
    static std::unique_ptr<Player> createPlayer(std::istringstream& lineStream);

    static std::unique_ptr<Job> createJob(const std::string& jobName);

    static std::unique_ptr<Character> createCharacter(const std::string& characterName);
};
