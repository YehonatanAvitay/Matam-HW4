#include "Event.h"

Event::Event(const string& name) : name(name) {
}

string Event::getName() const {
    return name;
}
