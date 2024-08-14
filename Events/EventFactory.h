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
    static std::unordered_map<string,std::function<unique_ptr<Event>(std::istream&)>>
    eventsFactoriesMap;
    static bool isInteger(const string&);
    static unique_ptr<Event> createEvent(const string& eventName, std::istream& eventFile);

public:
    static unique_ptr<Pack> createPack(std::istream&);
    vector<unique_ptr<Event>> createEventList(std::istream&);
};
