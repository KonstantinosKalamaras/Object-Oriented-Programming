#include "card.h"
#include <iostream>

using namespace std;

// TODO: Implement here the methods of Card, CardMove, and CardMoney
//constructor
Card::Card(int id, string text){
    this->id = id;
    this->text = text;
}
//getters
int Card::getId(){return id; }
string Card::getText(){return text; }
//derivative class CardMove
CardMove::CardMove(int id, string text, int location) : Card (id,text){this->location = location; }
void CardMove :: cardAction(Bank* bank, Player* player){ player->setLocation(this->location); }
//derivative class CardMoney
CardMoney::CardMoney(int id, string text, int amount) : Card(id, text){this->amount = amount; }
void CardMoney :: cardAction(Bank* bank, Player* player){
    bank -> giveMoneyToBank(this->amount);
    player-> giveMoneyToPlayer(this->amount);
}
