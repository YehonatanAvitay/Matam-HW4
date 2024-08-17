#include "Factory.h"

Factory::FactoriesMap<Event> const Factory::eventsFactoriesMap = {
        {"Snail", [](std::istream&, const string&){
            return std::make_unique<Snail>();
        }
        },
        {"Slime", [](std::istream&, const string&){
            return std::make_unique<Slime>();
        }
        },
        {"Balrog", [](std::istream&, const string&){
            return std::make_unique<Balrog>();
        }
        },
        {"Pack", [](std::istream& file, const string&) {
            return createPack(file, "Invalid Events File");
        }
        },
        {"SolarEclipse", [](std::istream&, const string&) {
            return std::make_unique<SolarEclipse>();
        }
        },
        {"PotionsMerchant", [](std::istream&, const string&) {
            return std::make_unique<PotionsMerchant>();
        }
        },
};

Factory::FactoriesMap<Encounter> const Factory::encountersFactoriesMap = {
        {"Snail", [](std::istream&, const string&){
            return std::make_unique<Snail>();
        }
        },
        {"Slime", [](std::istream&, const string&){
            return std::make_unique<Slime>();
        }
        },
        {"Balrog", [](std::istream&, const string&){
            return std::make_unique<Balrog>();
        }
        },
        {"Pack", [](std::istream& file, const string&) {
            return Factory::createPack(file, "Invalid Events File");
        }
        },
};

Factory::FactoriesMap<Job> const Factory::jobFactoriesMap = {
        {"Warrior", [](std::istream&, const string&){
            return std::make_unique<Warrior>();
        }
        },
        {"Archer", [](std::istream&, const string&){
            return std::make_unique<Archer>();
        }
        },
        {"Magician", [](std::istream&, const string&){
            return std::make_unique<Magician>();
        }
        }
};

Factory::FactoriesMap<Character> const Factory::characterFactoriesMap = {
        {"RiskTaking", [](std::istream&, const string&) {
            return std::make_unique<RiskTaking>();
        }
        },
        {"Responsible", [](std::istream&, const string&) {
            return std::make_unique<Responsible>();
        }
        }
};

unique_ptr<Pack> Factory::createPack(std::istream& eventsFile, const string& errorMessage) {
    vector<unique_ptr<Encounter>> members;
    string packSize;
    eventsFile >> packSize;
    // Making sure after the word Pack appears a number:
    if(!isInteger(packSize)) {
        throw std::runtime_error(errorMessage);
    }
    int PackSizeNumber = std::stoi(packSize);
    if (PackSizeNumber < 2) {
        throw std::runtime_error(errorMessage);
    }
    int membersCounter = 0;
    string encounterString;

    // constructing the members vector. It may contain Events of Encounter type only:
    for (int i = 0; i < PackSizeNumber && eventsFile >> encounterString; ++i) {
        unique_ptr<Encounter> newEvent = create<Encounter>
                (encounterString ,eventsFile,
                 encountersFactoriesMap, errorMessage);
        members.push_back(std::move(newEvent));
        ++membersCounter;
    }
    if (membersCounter < PackSizeNumber) {
        throw std::runtime_error(errorMessage);
    }
    unique_ptr<Pack> newPack = std::make_unique<Pack>(std::move(members));
    return newPack;
}

std::unique_ptr<Player> Factory::createPlayer(std::istringstream& lineStream) {
    std::string name, jobName, characterName;
    string errorMessage = "Invalid Players File";
    if (!(lineStream >> name >> jobName >> characterName)) {
        throw std::runtime_error(errorMessage);
    }
    if(name.size() > 15 || name.size() < 3) {
        throw std::runtime_error(errorMessage);
    }

    std::string extra;
    if (lineStream >> extra) {
        throw std::runtime_error(errorMessage);
    }

    auto job = create<Job>(jobName, lineStream,
                           jobFactoriesMap, errorMessage);
    auto character = create<Character>(characterName, lineStream,
                                       characterFactoriesMap, errorMessage);

    return std::make_unique<Player>(name, std::move(job), std::move(character));
}

bool Factory::isInteger(const string& stringInput) {
    for (char character : stringInput) {
        if(!std::isdigit(character)) {
            return false;
        }
    }
    return true;
}

vector<unique_ptr<Event>> Factory::createEventList(std::istream& eventsFile,
                                                   const string& errorMessage) {
    vector<unique_ptr<Event>> eventsList;
    int counter = 0;
    string eventString;
    while(eventsFile >> eventString) {
        eventsList.push_back(std::move(create<Event>(eventString ,eventsFile,
                                                     eventsFactoriesMap, errorMessage)));
        counter++;
    }
    if (counter < 2) {
        throw std::runtime_error(errorMessage);
    }
    return eventsList;
}

std::vector<std::unique_ptr<Player>> Factory::readPlayers(std::istream& input) {
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