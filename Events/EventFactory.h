#pragma once
#include <map>
#include <vector>
#include <memory>
#include "Event.h"
#include "SpecialEvent.h"
#include "Encounter.h"
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <functional>

class Factory {
    template <typename T>
    using FactoriesMap = std::unordered_map<std::string,
            std::function<std::unique_ptr<T>(std::istream&, const std::string&)>>;

    template <typename T>
    using FactoriesMapConstIterator = typename FactoriesMap<T>::const_iterator;

    template <class T>
    static FactoriesMapConstIterator<T> find(const string& eventName,
                                              const FactoriesMap<T>& map,
                                             const string& ErrorMessage);

    template <class T>
    static unique_ptr<T> create(const string& eventName,
                                std::istream& eventFile,
                                const FactoriesMap<T>& map,
                                const string& errorMessage);

    static unique_ptr<Pack> createPack(std::istream&, const string&);
    static std::unique_ptr<Player> createPlayer(std::istringstream& lineStream);
    static bool isInteger(const string&);

    static const FactoriesMap<Event> eventsFactoriesMap;
    static const FactoriesMap<Encounter> encountersFactoriesMap;
    static const FactoriesMap<Job> jobFactoriesMap;
    static const FactoriesMap<Character> characterFactoriesMap;



public:
    static vector<unique_ptr<Event>> createEventList(std::istream&,
                                                     const string& = "Invalid Events File");
    static std::vector<std::unique_ptr<Player>> readPlayers(std::istream& input);
};

template <class T>
Factory::FactoriesMapConstIterator<T> Factory::find(const string& eventName,
                                                const FactoriesMap<T>& map,
                                                const string& errorMessage) {
    auto it = map.find(eventName);
    if (it == map.end()) {
        throw std::runtime_error(errorMessage);
    }
    return it;
}

template <class T>
unique_ptr<T> Factory::create(const std::string& eventName,
                                   std::istream& eventFile,
                                   const FactoriesMap<T>& map,
                                   const string& errorMessage) {
    auto it = find<T>(eventName, map, errorMessage);
    std::unique_ptr<T> event = it->second(eventFile, errorMessage);
    return std::move(event);
}