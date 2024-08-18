#include "Event.h"

// Event Constructor. Name field is used for getDescription function
Event::Event(const string& name) : name(name) {
}

// Function that returns the name
string Event::getName() const {
    return name;
}
