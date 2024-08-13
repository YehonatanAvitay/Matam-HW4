
#pragma once

#include "../Players/Player.h"

class Event {
    string name;
public:
    /**
     * Gets the description of the event
     *
     * @return - the description of the event
    */
    string getName() const;
    virtual string getDescription() const = 0;
    virtual void play(Player&) = 0;
};
