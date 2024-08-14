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
    static std::unordered_map<string,std::function<unique_ptr<Event>(const vector<string>&)>>
    eventsFactoriesMap;
    static vector<string> splitString(const string&);
    static unique_ptr<Pack> createPackRecursively(std::vector<string>::iterator it);
    static bool isInteger(const string&);
public:
    static unique_ptr<Pack> createPack(const vector<string>&);
    vector<unique_ptr<Event>> createEventList(std::istream& Eventsfile);
};
