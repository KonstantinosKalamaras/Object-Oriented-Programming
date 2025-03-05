#include "player.h"
#include "iostream"

using namespace std;

SmartPlayer::SmartPlayer(int id) : Player(id)
{
    name = "Team 101"; // TODO: Change this to your team number e.g. "Team 099"
}

bool SmartPlayer::decideBuy(Space* space)
{
    // TODO: Implement this function (some useful objects that you may use are **spaces and *opponent, which are inherited from Player)
    // This strategy should probably be based on the money and the location of the players, and the spaces (i.e. what is owned from which player, how many houses are there in each property, etc.)
    int i;
    bool safe = false;
    for(i = 0; i < 40; i++){
        if(safe) break;
        if(i % 5 == 0) safe = true;
        if(spaces[i]->typeIs(PropertyType)){
            if(!opponent->ownsProperty(spaces[i])) safe = false;
        }
    }
    if(space->ownerIs(0) && this->getMoney() >= 300 + 700 * safe) return true;
    return false;
}

int SmartPlayer::decideUpgrade()
{
    // TODO: Implement this function (some useful objects that you may use are **spaces and *opponent, which are inherited from Player)
    // This strategy should probably be based on the money and the location of the players, and the spaces (i.e. what is owned from which player, how many houses are there in each property, etc)
    float probabilities[11], maxprob = 0;
    int i, boxid[11], maxprobid = 0;
    for(i = 0; i < 11; i++){
        if(i < 6)probabilities[i] = (i + 1)*1.0/36;
        else probabilities[i] = (11 - i)*1.0/36;

    }
    // probabilities index: 0-> 2 , 1 -> 3 ... 10 -> 12
    for(i = 0; i < 11; i++) boxid[i] = 0;
    for(i = 1; i <= 11; i++){
        if(opponent->getLocation() + i + 1  < 40){
            if(spaces[opponent->getLocation() + i + 1]->typeIs(PropertyType)){
                if(canUpgrade(((Property*)spaces[opponent->getLocation() + i + 1])) ) boxid[i - 1] = opponent->getLocation() + i + 1;
            }
        }
        else{
            if(spaces[opponent->getLocation() + i + 1 - 40]->typeIs(PropertyType)){
                if(canUpgrade(((Property*)spaces[opponent->getLocation() + i + 1 - 40]))) boxid[i - 1] = opponent->getLocation() + i + 1 - 40;
            }
        }
    }
    for(i = 0; i < 11; i++){
        if(probabilities[i] * (1 - ((Property *)spaces[boxid[i]])->getNumberOfHouses()*1.0/5) * (boxid[i] > 0) > maxprob){
            maxprob = probabilities[i];
            maxprobid = boxid[i];
        }
    }

    bool check=true;

    for(i=0; i<11; i++){

        if(boxid[i] != 0){
            check=false;
        }
    }

    int id=0,minimum=5;

    for(i=0; i<40; i++){
        if(spaces[i]->typeIs(PropertyType)){
            if(((Property *)spaces[i])->getNumberOfHouses() <= minimum && this->canUpgrade((Property *)spaces[i])){
                minimum=((Property *)spaces[i])->getNumberOfHouses();
                id=i;
            }
        }
    }

    bool safe = false;
    for(i = 0; i < 40; i++){
        if(safe) break;
        if(i % 5 == 0) safe = true;
        if(spaces[i]->typeIs(PropertyType)){
            if(!opponent->ownsProperty(spaces[i])) safe = false;
        }
    }

    if(check && this->getMoney()-((Property *)spaces[id])->getUpgradeCost() >= 300 + safe * 700){
            return id;
    }

    if(maxprobid > 0 && this->getMoney()-((Property *)spaces[maxprobid])->getUpgradeCost() >= 300 + safe * 700) return maxprobid;
    else return -1;
}
