#include "Factory.h"

// Factories maps: map between strings and constructors:
MatamStory::Factory::FactoriesMap<Event> const MatamStory::Factory::eventsFactoriesMap = {
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

MatamStory::Factory::FactoriesMap<Encounter> const MatamStory::Factory::encountersFactoriesMap = {
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

MatamStory::Factory::FactoriesMap<Job> const MatamStory::Factory::jobFactoriesMap = {
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

MatamStory::Factory::FactoriesMap<Character> const MatamStory::Factory::characterFactoriesMap = {
        {"RiskTaking", [](std::istream&, const string&) {
            return std::make_unique<RiskTaking>();
        }
        },
        {"Responsible", [](std::istream&, const string&) {
            return std::make_unique<Responsible>();
        }
        }
};

// Function that creates a Pack recursively:
unique_ptr<Pack> MatamStory::Factory::createPack
(std::istream& eventsFile, const string& errorMessage) {

    // Create the members vector, it may contain Events of Encounter type only
    vector<unique_ptr<Encounter>> members;
    string packSize;
    eventsFile >> packSize;

    // Making sure after the word Pack appears a number
    if(!isInteger(packSize)) {
        throw std::runtime_error(errorMessage);
    }
    int PackSizeNumber = std::stoi(packSize);

    // Making sure the Pack size is legal
    if (PackSizeNumber < 2) {
        throw std::runtime_error(errorMessage);
    }
    int membersCounter = 0;
    string encounterString;

    // Creating each member
    for (int i = 0; i < PackSizeNumber && eventsFile >> encounterString; ++i) {
        unique_ptr<Encounter> newEvent = create<Encounter>
                (encounterString ,eventsFile,
                 encountersFactoriesMap, errorMessage);
        members.push_back(std::move(newEvent));
        ++membersCounter;
    }

    // Checking if enough members were provided
    if (membersCounter < PackSizeNumber) {
        throw std::runtime_error(errorMessage);
    }

    // Assigning the members to a new Pack element
    unique_ptr<Pack> newPack = std::make_unique<Pack>(std::move(members));
    return newPack;
}

// Function to create a new player:
std::unique_ptr<Player> MatamStory::Factory::createPlayer(const string& name, const string& jobName,
                                              const string& characterName, std::istream& stream) {
    // Create Player's fields
    string errorMessage = "Invalid Players File";
    auto job = create<Job>(jobName, stream,
                           jobFactoriesMap, errorMessage);
    auto character = create<Character>(characterName, stream,
                                       characterFactoriesMap, errorMessage);

    // Construct the new player
    return std::make_unique<Player>(name, std::move(job), std::move(character));
}

// Function to check if a string is an integer:
bool MatamStory::Factory::isInteger(const string& stringInput) {
    for (char character : stringInput) {
        if(!std::isdigit(character)) {
            return false;
        }
    }
    return true;
}

// Function to create an Events list and making sure its length is valid:
vector<unique_ptr<Event>> MatamStory::Factory::createEventsList(std::istream& eventsFile,
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

// Function to create Players list
std::vector<std::unique_ptr<Player>> MatamStory::Factory::createPlayersList(std::istream& input) {
    string errorMessage = "Invalid Players File";
    std::vector<std::unique_ptr<Player>> players;
    int playersCounter = 0;
    std::string name, jobName, characterName;

    // For each name string that is given, 2 more strings are expected for the Job and Character
    for (int i = 0; i < 6 && input >> name; ++i) {
        // Verify the name length
        if(name.size() > 15 || name.size() < 3) {
            throw std::runtime_error(errorMessage);
        }
        if (!(input >> jobName)) {
            throw std::runtime_error(errorMessage);
        }
        if (!(input >> characterName)) {
            throw std::runtime_error(errorMessage);
        }
        // create the player from the 3 strings
        players.push_back(createPlayer(name, jobName, characterName, input));
        playersCounter++;
    }

    // If there are more than 6 players, throw an error
    string extra;
    if(input >> extra) {
        throw (std::runtime_error(errorMessage));
    }

    if (playersCounter < 2) {
        throw std::runtime_error("Invalid Players File");
    }
    return players;
}