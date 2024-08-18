#pragma once

#include "Event.h"

// Class to represent special events:
class SpecialEvent : public Event {
protected:
    explicit SpecialEvent(const string&);
public:
    SpecialEvent(const SpecialEvent&) = delete;
    SpecialEvent& operator=(const SpecialEvent&) = delete;
    string getDescription() const override;
    virtual void play(Player &) override = 0;
    virtual ~SpecialEvent() = default;
};

// Classes to represent each of the special events:
class SolarEclipse : public SpecialEvent {
public:
    SolarEclipse();
    SolarEclipse(const SolarEclipse&) = delete;
    SolarEclipse& operator=(const SolarEclipse&) = delete;
    void play(Player &) override;
};

class PotionsMerchant : public SpecialEvent {
public:
    PotionsMerchant();
    PotionsMerchant(const PotionsMerchant&) = delete;
    PotionsMerchant& operator=(const PotionsMerchant&) = delete;
    void play(Player &) override;
};