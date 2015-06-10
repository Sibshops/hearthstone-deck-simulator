#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <cassert>

#include "include/Game.hpp"


// todo fix for hero power
void oneManaDeck()
{
   
   // Make a deck of all one mana cards.
   Deck_Cl deck;

   // A one mana card.
   const Card_Cl cONE_MANA_CARD(1);
   
   for (int i = 0; i < Deck_Ns::cSIZE; ++i)
   {
      deck.addCard(cONE_MANA_CARD);
   }
 
   // Start game.
   Game_Cl game;
   game.setDeck(deck);
 
   game.play();

   const int cUNSPENT_MANA = game.getUnspentMana();

   // The amount of mana after 10 turns.
   const int cTOTAL_MANA = 10 * (10 + 1) / 2;
   
   const int cEXPECTED_SPENT = 10 + 3;

   const int cEXPECTED_UNSPENT = cTOTAL_MANA - cEXPECTED_SPENT;

   std::cout << "Unspent = " << cUNSPENT_MANA << ", Expected = " << cEXPECTED_UNSPENT << std::endl;

   assert(cUNSPENT_MANA == cEXPECTED_UNSPENT);
}

void tenManaDeck()
{  
   // Make a deck of all ten mana cards.
   Deck_Cl deck;

   // A ten mana card.
   const Card_Cl cTEN_MANA_CARD(10);
   
   for (int i = 0; i < Deck_Ns::cSIZE; ++i)
   {
      deck.addCard(cTEN_MANA_CARD);
   }
 
   // Start game.
   Game_Cl game;
   game.setDeck(deck);
 
   game.play();

   const int cUNSPENT_MANA = game.getUnspentMana();

   // The amount of mana after 10 turns.
   const int cTOTAL_MANA = 10 * (10 + 1) / 2;

   // Use the 2 mana turns 2-9, then the 10 mana card turn 10.
   const int cEXPECTED_SPENT =  2 * 8 + 10;

   const int cEXPECTED_UNSPENT = cTOTAL_MANA - cEXPECTED_SPENT;

   std::cout << "Unspent = " << cUNSPENT_MANA << ", Expected = " << cEXPECTED_UNSPENT << std::endl;

   assert(cUNSPENT_MANA == cEXPECTED_UNSPENT);
}


void randomDeck()
{
   while (true)
   {
      // Fill a random deck
      Deck_Cl deck;
      deck.populateWithRandom();

      // Start game.
      Game_Cl game;
      game.setDeck(deck);

      // The number of games to play per deck
      const double cGAMES_PER_DECK = 50;

      int unspentMana = 0;
   
      for (int i = 0; i < cGAMES_PER_DECK; ++i)
      {
         game.play();
         const int cUNSPENT_GAME = game.getUnspentMana();
      
         unspentMana += cUNSPENT_GAME;
         // std::cout << cUNSPENT_GAME << " - game " << std::endl;

      
         // std::cout << unspentMana / (double)(i+1) << " - average so far " << std::endl;
      }
   
      // The average unspent mana.
      const double cAVERAGE_UNSPENT_MANA = unspentMana / cGAMES_PER_DECK;

      if (cAVERAGE_UNSPENT_MANA < 1.6)
      {
         // lowestAvg = cAVERAGE_UNSPENT_MANA;

         std::cout << std::setw(5) << cAVERAGE_UNSPENT_MANA << " - average: " << deck.getDeckHistogram() << std::endl;
      }

   }
}

int main()
{
   // Seed the random number generator
   srand(time(NULL));
   
   randomDeck();

   // tenManaDeck();
	return 0;
}
    
