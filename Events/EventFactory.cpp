#include "EventFactory.h"

std::unordered_map<std::string, std::function<std::unique_ptr<Event>(std::istream&)>>
EventFactory::eventsFactoriesMap = {
{"Snail", [](std::istream&){return std::make_unique<Snail>();}},
{"Slime", [](std::istream&){return std::make_unique<Slime>();}},
{"Balrog", [](std::istream&){return std::make_unique<Balrog>();}},
{"Pack", [](std::istream& file) {return EventFactory::createPack(file);}},
{"SolarEclipse", [](std::istream&) {return std::make_unique<SolarEclipse>();}},
{"PotionsMerchant", [](std::istream&) {return std::make_unique<PotionsMerchant>();}},
};

bool EventFactory::isInteger(const string& string1) {
    for (char c : string1) {
        if(!std::isdigit(c)) {
            return false;
        }
    }
    return true;
}

unique_ptr<Event> EventFactory::createEvent(const string& eventName, std::istream& eventFile) {
    auto it = eventsFactoriesMap.find(eventName);
    if (it == eventsFactoriesMap.end()) {
        throw std::runtime_error("Invalid Events File");
    }
    std::unique_ptr<Event> event = it->second(eventFile);
    return std::move(event);
}

vector<unique_ptr<Event>> EventFactory::createEventList(std::istream& eventsFile) {
    vector<unique_ptr<Event>> eventsList;
    int counter = 0;
    string eventString;
    while(eventsFile >> eventString) {
        eventsList.push_back(std::move(createEvent(eventString ,eventsFile)));
        counter++;
    }
    if (counter < 2) {
        throw std::runtime_error("Invalid Events File");
    }
    return eventsList;
    }

unique_ptr<Pack> EventFactory::createPack(std::istream& eventsFile) {
    vector<unique_ptr<Event>> members;
    string packSize;
    eventsFile >> packSize;
    if(!isInteger(packSize)) {
        throw std::runtime_error("Invalid Events File");
    }
    for (int i = 0; i < std::stoi(packSize); ++i) {
        string eventString;
        eventsFile >> eventString;
        unique_ptr<Event> newEvent = createEvent(eventString ,eventsFile);
        members.push_back();
    }
    return
}