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

    // Methods and fields to create events:
    static std::unordered_map<std::string, std::function<std::unique_ptr<Event>(std::istream&)>>
    eventsFactoriesMap;
    static std::unordered_map<std::string, std::function<std::unique_ptr<Event>
    (std::istream&)>>::iterator findEvent(const string& eventName);
    static unique_ptr<Event> createEvent(const string& eventName, std::istream& eventFile);

    // Methods and fields to create Encounters (to be used while constructing Pack members):
    static std::unordered_map<std::string, std::function<std::unique_ptr<Encounter>(std::istream&)>>
            encountersFactoriesMap;
    static std::unordered_map<std::string, std::function<std::unique_ptr<Encounter>
            (std::istream&)>>::iterator findEncounter(const string& eventName);
    static unique_ptr<Encounter> createEncounter(const string& eventName, std::istream& eventFile);
    static unique_ptr<Pack> createPack(std::istream&);
    static bool isInteger(const string&);

public:
    static vector<unique_ptr<Event>> createEventList(std::istream&);
};
