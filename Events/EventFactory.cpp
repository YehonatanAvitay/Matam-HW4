#include "EventFactory.h"

std::unordered_map<std::string, std::function<std::unique_ptr<Event>(const vector<string>&)>>
EventFactory::eventsFactoriesMap = {
{"Snail", [](const vector<string>&){return std::make_unique<Snail>();}},
{"Slime", [](const vector<string>&){return std::make_unique<Slime>();}},
{"Balrog", [](const vector<string>&){return std::make_unique<Balrog>();}},
{"Pack", [](const vector<string>& string1)
    {return EventFactory::createPack(string1);}},
{"SolarEclipse", [](const vector<string>&)
    {return std::make_unique<SolarEclipse>();}},
{"PotionsMerchant", [](const vector<string>&)
    {return std::make_unique<PotionsMerchant>();}},
};

bool EventFactory::isInteger(const string& string1) {
    for (char c : string1) {
        if(!std::isdigit(c)) {
            return false;
        }
    }
    return true;
}

vector<unique_ptr<Event>> EventFactory::createEventList(std::istream& eventsFile) {
    vector<unique_ptr<Event>> eventsList;
    string line;
    int counter = 0;
    while(std::getline(eventsFile, line)) {
        vector<string> splittedString = splitString(line);
        // Handeling the case that a number argument comes after the name of the class.
        // Only the words before the number (which define the Event) will be searched in the map.
        string stringToCheck;
        for (string string1 : splittedString) {
            if(std::isdigit(string1[0])) {
                break;
            }
            stringToCheck += string1;
        }
            auto it = eventsFactoriesMap.find(stringToCheck);
            if (it == eventsFactoriesMap.end()) {
                throw std::runtime_error("Invalid Events File");
            }
            std::unique_ptr<Event> event = it->second(splittedString);
            eventsList.push_back(std::move(event));
            counter++;
        }
    if (counter < 2) {
        throw std::runtime_error("Invalid Events File");
    }
    return eventsList;
    }

vector<string> EventFactory::splitString(const string& string1) {
    std::istringstream stream(string1);
    vector<string> vector1;
    string word;
    while(stream >> word) {
        vector1.push_back(word);
    }
    return std::move(vector1);
}

unique_ptr<Pack> EventFactory::createPack(const vector<string>& splittedString) {
    vector<unique_ptr<Encounter>> members;
    auto it = splittedString.begin();
    unique_ptr<Pack> pack = std::make_unique<Pack>();
    
    pack->setMembers(std::move(members));
    return pack;
}

unique_ptr<Pack> EventFactory::createPackRecursively(std::vector<string>::iterator it) {
    unsigned int size = stoi(*it);
    it++;
    unique_ptr<Pack> pack = std::make_unique<Pack>();
    vector<unique_ptr<Encounter>> members;
    for (int i = 0; i < size; ++i) {
        eventsFactoriesMap.find(*it)
        it++
    }
}
