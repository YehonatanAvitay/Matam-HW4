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
#include "../MatamStory.h"

class MatamStory::Factory {
    // for code readability using short names
    template <typename T>
    using FactoriesMap = std::unordered_map<std::string,
            std::function<std::unique_ptr<T>(std::istream&, const std::string&)>>;

    template <typename T>
    using FactoriesMapConstIterator = typename FactoriesMap<T>::const_iterator;

    // Functions to create elements for the Players and Events lists:
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
    static std::unique_ptr<Player> createPlayer(const string& name, const string& jobName,
                                                const string& characterName, std::istream&);
    static bool isInteger(const string&);

    // Maps that match each string to its constructor:
    static const FactoriesMap<Event> eventsFactoriesMap;
    static const FactoriesMap<Encounter> encountersFactoriesMap;
    static const FactoriesMap<Job> jobFactoriesMap;
    static const FactoriesMap<Character> characterFactoriesMap;

public:
    // Two public methods for MatamStory constructor to use:
    static vector<unique_ptr<Event>> createEventsList(std::istream&,
                                                     const string& = "Invalid Events File");
    static std::vector<std::unique_ptr<Player>> createPlayersList(std::istream& input);
};

// Template function to search for an element in the map. fits all maps:
template <class T>
MatamStory::Factory::FactoriesMapConstIterator<T> MatamStory::Factory::find(const string& eventName,
                                                    const FactoriesMap<T>& map,
                                                    const string& errorMessage) {
    auto it = map.find(eventName);
    if (it == map.end()) {
        throw std::runtime_error(errorMessage);
    }
    return it;
}

// Template function to create an element from the map. fits all maps:
template <class T>
unique_ptr<T> MatamStory::Factory::create(const std::string& eventName,
                              std::istream& eventFile,
                              const FactoriesMap<T>& map,
                              const string& errorMessage) {
    auto it = find<T>(eventName, map, errorMessage);
    std::unique_ptr<T> event = it->second(eventFile, errorMessage);
    return event;
}