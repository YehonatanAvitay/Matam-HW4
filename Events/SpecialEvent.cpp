#include "SpecialEvent.h"
#include "../Utilities.h"

// SpecialEvent constructor:
SpecialEvent::SpecialEvent(const string& name) : Event(name) {
}

// Function that returns the description of a SpecialEvent:
string SpecialEvent::getDescription() const {
    return name;
}

// SolarEclipse constructor:
SolarEclipse::SolarEclipse() : SpecialEvent("SolarEclipse") {
}

// Function to be used in "playTurn" function when the Event is SolarEclipse.
// It calculates the force that the player earns or loses and sets it:
void SolarEclipse::play(Player & player) {
    // Different calculation for magical Jobs
    if(player.getJob().isItMagical()) {
        player.setForce(player.getForce() + 1);
        printTurnOutcome(getSolarEclipseMessage(player, 1));
    }
    else {
        // Default calculation
        int playerForce = player.getForce();
        if (playerForce < 1) {
            printTurnOutcome(getSolarEclipseMessage(player, 0));
        }
        else {
        printTurnOutcome(getSolarEclipseMessage(player, -1));
        player.setForce(player.getForce() - 1);
        }
    }
}

// PotionsMerchant constructor:
PotionsMerchant::PotionsMerchant() : SpecialEvent("PotionsMerchant") {
}

// Function to be used in "playTurn" function when the Event is PotionsMerchant.
// It calls "buy" function according to the Player's character:
void PotionsMerchant::play(Player & player) {
    printTurnOutcome(getPotionsPurchaseMessage(player, player.getCharacter().buy(player)));
}