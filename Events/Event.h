#pragma once
#include "../Players/Player.h"

class Event {
protected:
    explicit Event(const string&);
    string name;
public:
    /**
     * Gets the description of the event
     *
     * @return - the description of the event
    */
    Event(const Event&) = delete;
    Event& operator=(const Event&) = delete;
    string getName() const;
    virtual string getDescription() const = 0;
    virtual void play(Player&) = 0;
    virtual ~Event() = default;
};