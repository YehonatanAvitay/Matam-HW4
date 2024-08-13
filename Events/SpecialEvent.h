#pragma once
#include "Event.h"

class SpecialEvent : public Event {
    string name;
public:
    string getDescription() const override;
    void play(Player &) override = 0;
};

class SolarEclipse : public SpecialEvent {
    string name = "SolarEclipse";
public:
    void play(Player &) override;
};

class PotionsMerchant : public SpecialEvent {
    string name = "PotionsMerchant";
public:
    void play(Player &) override;
};