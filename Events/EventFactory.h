#pragma once
#include <map>
#include <vector>
#include <memory>
#include "Event.h"
#include "SpecialEvent.h"
#include "Encounter.h"

class EventFactory {
public:
    unique_ptr<Event> createEvent();
};
