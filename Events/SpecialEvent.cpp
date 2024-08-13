#include "SpecialEvent.h"

string SpecialEvent::getDescription() const {
    return name;
}

void SolarEclipse::play(Player & player) {
    if(player.isMagical()) {
        player.setLevel(player.getLevel() + 1);
    }
    else {
        player.setForce(player.getForce() - 1);
    }
}

void PotionsMerchant::play(Player & player) {
    player.buy();
}