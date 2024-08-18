#include "SpecialEvent.h"
#include "../Utilities.h"

SpecialEvent::SpecialEvent(const string& name) : Event(name) {
}

string SpecialEvent::getDescription() const {
    return name;
}

SolarEclipse::SolarEclipse() : SpecialEvent("SolarEclipse") {
}

void SolarEclipse::play(Player & player) {
    if(player.getJob().isItMagical()) {
        player.setForce(player.getForce() + 1);
        printTurnOutcome(getSolarEclipseMessage(player, 1));
    }
    else {
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

PotionsMerchant::PotionsMerchant() : SpecialEvent("PotionsMerchant") {
}

void PotionsMerchant::play(Player & player) {
    printTurnOutcome(getPotionsPurchaseMessage(player, player.getCharacter().buy(player)));
}