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

class EventFactory {

    static std::unordered_map<std::string, std::function<std::unique_ptr<Event>(std::istream&)>>
    eventsFactoriesMap;
    static std::unordered_map<std::string, std::function<std::unique_ptr<Encounter>(std::istream&)>>
    encountersFactoriesMap;
    template <class T>
    static std::unordered_map<std::string, std::function<std::unique_ptr<T>(std::istream&)>>
    ::const_iterator findEventInMap(const string& eventName, const std::unordered_map<std::string,
            std::function<std::unique_ptr<T>(std::istream&)>>& map);
    template <class T>
    static unique_ptr<T> createEvent(const string& eventName, std::istream& eventFile,
                              const std::unordered_map<std::string,
                                      std::function<std::unique_ptr<T>(std::istream&)>>& map);
    static unique_ptr<Pack> createPack(std::istream&);
    static bool isInteger(const string&);

public:
    static vector<unique_ptr<Event>> createEventList(std::istream&);
};

template <class T>
std::unordered_map<std::string, std::function<std::unique_ptr<T>(std::istream&)>>::const_iterator
EventFactory::findEventInMap(const string& eventName,
                             const std::unordered_map<std::string,
                                     std::function<std::unique_ptr<T>(std::istream&)>>& map) {
    auto it = map.find(eventName);
    if (it == map.end()) {
        throw std::runtime_error("Invalid Events File");
    }
    return it;
}

template <class T>
unique_ptr<T> EventFactory::createEvent(const string& eventName, std::istream& eventFile,
                                        const std::unordered_map<std::string,
                                        std::function<std::unique_ptr<T>(std::istream&)>>& map) {
    auto it = findEventInMap(eventName, map);
    std::unique_ptr<T> event = it->second(eventFile);
    return std::move(event);
}

//    static std::unordered_map<std::string, std::function<std::unique_ptr<Event>
//    (std::istream&)>>::iterator findEvent(const string& eventName);
//    static unique_ptr<Event> createEvent(const string& eventName, std::istream& eventFile);

//    static std::unordered_map<std::string, std::function<std::unique_ptr<Encounter>
//            (std::istream&)>>::iterator findEncounter(const string& eventName);
//    static unique_ptr<Encounter> createEncounter(const string& eventName, std::istream& eventFile);