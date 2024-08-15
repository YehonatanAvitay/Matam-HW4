#pragma once

#include <unordered_map>
#include <functional>
#include <memory>
#include <string>
#include <sstream>
#include <stdexcept>
#include <vector>

#include "PlayersFactory.h"
#include "Player.h"
#include "Character.h"
#include "Job.h"

 std::vector<std::unique_ptr<Player>> PlayersFactory::readPlayers(std::istream& input) {
    std::vector<std::unique_ptr<Player>> players;
    std::string line;
    int playersCounter = 0;

    while (std::getline(input, line)) {
        std::istringstream lineStream(line);
        players.push_back(createPlayer(lineStream));
        playersCounter++;
        if (playersCounter > 6) {
            throw std::runtime_error("Invalid Players File");
        }
    }

    if (playersCounter < 2) {
        throw std::runtime_error("Invalid Players File");
    }
    return players;
}


std::unique_ptr<Player> PlayersFactory::createPlayer(std::istringstream& lineStream) {
    std::string name, jobName, characterName;

    if (!(lineStream >> name >> jobName >> characterName)) {
        throw std::runtime_error("Invalid Players File");
    }

    std::string extra;
    if (lineStream >> extra) {
        throw std::runtime_error("Invalid Players File");
    }

    auto job = createJob(jobName);
    auto character = createCharacter(characterName);

    return std::make_unique<Player>(name, std::move(job), std::move(character));
}

std::unique_ptr<Job> PlayersFactory::createJob(const std::string& jobName) {
    auto it = jobFactoriesMap.find(jobName);
    if (it == jobFactoriesMap.end()) {
        throw std::runtime_error("Invalid Players File");
    }
    return it->second();
}

std::unique_ptr<Character> PlayersFactory::createCharacter(const std::string& characterName) {
    auto it = characterFactoriesMap.find(characterName);
    if (it == characterFactoriesMap.end()) {
        throw std::runtime_error("Invalid Players File");
    }
    return it->second();
}

const std::unordered_map<std::string, std::function<std::unique_ptr<Job>()>>
        PlayersFactory::jobFactoriesMap = {
        {"Warrior", []() { return std::make_unique<Warrior>(); }},
        {"Archer", []() { return std::make_unique<Archer>(); }},
        {"Magician", []() { return std::make_unique<Magician>(); }}
};

const std::unordered_map<std::string, std::function<std::unique_ptr<Character>()>>
        PlayersFactory::characterFactoriesMap = {
        {"RiskTaking", []() { return std::make_unique<RiskTaking>(); }},
        {"Responsible", []() { return std::make_unique<Responsible>(); }}
};