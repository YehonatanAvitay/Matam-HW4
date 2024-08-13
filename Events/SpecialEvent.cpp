#include "SpecialEvent.h"

string SpecialEvent::getDescription() const {
    return name;
}

void SolarEclipse::play(Player & player) {
    if(player.getJob().isItMagical()) {
        player.setLevel(player.getLevel() + 1);
    }
    else {
        player.setForce(player.getForce() - 1);
    }
}

void PotionsMerchant::play(Player & player) {
    player.getCharacter().buy(player);
}