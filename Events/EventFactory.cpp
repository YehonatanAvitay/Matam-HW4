#include "EventFactory.h"

std::unordered_map<std::string, std::function<std::unique_ptr<Event>(std::istream&)>>
EventFactory::eventsFactoriesMap = {
    {"Snail", [](std::istream&){
    return std::make_unique<Snail>();
        }
    },
    {"Slime", [](std::istream&){
    return std::make_unique<Slime>();
        }
    },
    {"Balrog", [](std::istream&){
    return std::make_unique<Balrog>();
        }
    },
    {"Pack", [](std::istream& file) {
    return EventFactory::createPack(file);
        }
    },
    {"SolarEclipse", [](std::istream&) {
    return std::make_unique<SolarEclipse>();
        }
    },
    {"PotionsMerchant", [](std::istream&) {
    return std::make_unique<PotionsMerchant>();
        }
    },
};

std::unordered_map<std::string, std::function<std::unique_ptr<Encounter>(std::istream&)>>
        EventFactory::encountersFactoriesMap = {
        {"Snail", [](std::istream&){
            return std::make_unique<Snail>();
            }
        },
        {"Slime", [](std::istream&){
            return std::make_unique<Slime>();
            }
        },
        {"Balrog", [](std::istream&){
            return std::make_unique<Balrog>();
            }
        },
        {"Pack", [](std::istream& file) {
            return EventFactory::createPack(file);
            }
        },
};

unique_ptr<Pack> EventFactory::createPack(std::istream& eventsFile) {
    unique_ptr<Pack> newPack;
    vector<unique_ptr<Encounter>> members;
    string packSize;
    eventsFile >> packSize;
    // Making sure after the word Pack appears a number:
    if(!isInteger(packSize)) {
        throw std::runtime_error("Invalid Events File");
    }
    unsigned int PackSizeNumber = std::stoi(packSize);
    if (PackSizeNumber < 2) {
        throw std::runtime_error("Invalid Events File");
    }
    int membersCounter = 0;
    string encounterString;
    // constructing the members vector. It may contain Events of Encounter type only:
    for (int i = 0; i < PackSizeNumber && eventsFile >> encounterString; ++i) {
        unique_ptr<Encounter> newEvent = createEvent<Encounter>
                (encounterString ,eventsFile,encountersFactoriesMap);
        members.push_back(std::move(newEvent));
        ++membersCounter;
    }
    if (membersCounter < PackSizeNumber) {
        throw std::runtime_error("Invalid Events File");
    }
    newPack->setMembers(std::move(members));
    return newPack;
}

bool EventFactory::isInteger(const string& stringInput) {
    for (char character : stringInput) {
        if(!std::isdigit(character)) {
            return false;
        }
    }
    return true;
}

vector<unique_ptr<Event>> EventFactory::createEventList(std::istream& eventsFile) {
    vector<unique_ptr<Event>> eventsList;
    int counter = 0;
    string eventString;
    while(eventsFile >> eventString) {
        eventsList.push_back(std::move(createEvent<Event>(eventString ,eventsFile,
                                                          eventsFactoriesMap)));
        counter++;
    }
    if (counter < 2) {
        throw std::runtime_error("Invalid Events File");
    }
    return eventsList;
}

//std::unordered_map<std::string, std::function<std::unique_ptr<Encounter>(std::istream&)>>::iterator
//EventFactory::findEncounter(const string& eventName) {
//    auto it = encountersFactoriesMap.find(eventName);
//    if (it == encountersFactoriesMap.end()) {
//        throw std::runtime_error("Invalid Events File");
//    }
//    return it;
//}
//
//std::unordered_map<std::string, std::function<std::unique_ptr<Event>(std::istream&)>>::iterator
//EventFactory::findEvent(const string& eventName) {
//    auto it = eventsFactoriesMap.find(eventName);
//    if (it == eventsFactoriesMap.end()) {
//        throw std::runtime_error("Invalid Events File");
//    }
//    return it;
//}

//unique_ptr<Event> EventFactory::createEvent(const string& eventName, std::istream& eventFile) {
//    auto it = findEvent(eventName);
//    std::unique_ptr<Event> event = it->second(eventFile);
//    return std::move(event);
//}
//
//unique_ptr<Encounter> EventFactory::createEncounter(const string& eventName,
//                                                    std::istream& eventFile) {
//    auto it = findEncounter(eventName);
//    unique_ptr<Encounter> newEvent = it->second(eventFile);
//    return std::move(newEvent);
//}