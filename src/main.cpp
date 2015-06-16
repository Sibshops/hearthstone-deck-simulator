#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <cmath>

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
 
   game.play(3);

   const int cUNSPENT_MANA = game.getManaOnBoard();

   // The amount of mana after 10 turns.
   const int cTOTAL_MANA = 10 * (10 + 1) / 2;
   
   const int cEXPECTED_SPENT = 10 + 3;

   const int cEXPECTED_UNSPENT = cTOTAL_MANA - cEXPECTED_SPENT;

   std::cout << "Unspent = " << cUNSPENT_MANA << ", Expected = " << cEXPECTED_UNSPENT << std::endl;

   assert(cUNSPENT_MANA == cEXPECTED_UNSPENT);
}

void nineManaDeck()
{  
   // Make a deck of all nine mana cards.
   Deck_Cl deck;

   // A nine mana card.
   const Card_Cl cNINE_MANA_CARD(9);
   
   for (int i = 0; i < Deck_Ns::cSIZE; ++i)
   {
      deck.addCard(cNINE_MANA_CARD);
   }
 
   // Start game.
   Game_Cl game;
   game.setDeck(deck);
 
   game.play(3);

   const double cMANA_ON_BOARD = game.getManaOnBoard();

   // Use the 2 mana turns 2-9, then the 9 mana card turn 9.
   const double cEXPECTED_ONBOARD =  0.5 * 7 + 9;

   std::cout << "On Board = " << cMANA_ON_BOARD << ", Expected = " << cEXPECTED_ONBOARD  << std::endl;

   assert(fabs(cMANA_ON_BOARD - cEXPECTED_ONBOARD) < 0.1);
}

void randomOnce()
{
   // Fill a random deck
   Deck_Cl deck;
   deck.populateWithRandom();
      
   // Start game.
   Game_Cl game;
   game.setDeck(deck);

   double manaOnBoard = 0;

   const int cMULLIGAN_OVER = Card_Ns::generateRandom(Card_Ns::cMIN, Card_Ns::cMAX);
   
   game.play(cMULLIGAN_OVER);
   const double cUNSPENT_GAME = game.getManaOnBoard();
      
   manaOnBoard += cUNSPENT_GAME;
   std::cout << cUNSPENT_GAME << " - mulligan: " << cMULLIGAN_OVER
             << ", deck: "  << deck.getDeckHistogram() << std::endl;
            
}

double runWithDeck(
   const Deck_Cl& deck)
{
   // Start game.
   Game_Cl game;
   game.setDeck(deck);

   double manaOnBoard = 0;

   // The average unspent mana.
   double averageManaOnBoard = 0;

   const double cGAMES_PER_DECK = 10000;
   
   for (int i = 0; i < cGAMES_PER_DECK; ++i)
   {         
      game.play(Hand_Ns::cMULLIGAN);
      const double cUNSPENT_GAME = game.getManaOnBoard();
      
      manaOnBoard += cUNSPENT_GAME;
      // std::cout << cUNSPENT_GAME << " - game " << std::endl;

      
      // std::cout << manaOnBoard / (double)(i+1) << " - average so far " << std::endl;
   }

   averageManaOnBoard = manaOnBoard / cGAMES_PER_DECK;
   
   // {
   //    std::cout << std::setw(5) << averageManaOnBoard <<
   //       " - average - mulligan: " << Hand_Ns::cMULLIGAN << " - deck: " << deck.getDeckHistogram() << std::endl;
   // }

   return averageManaOnBoard;
}

void changeByOne()
{
   Deck_Cl deckWithHighestMana;
   deckWithHighestMana.populateWithRandom();

   // The current highest mana on the board.
   double highestMana = 0;

   // Is the deck the highest on the board?
   bool isAtHighest = false;

   // The number of games to play per deck
   const double cGAMES_PER_DECK = 10000;

   
   const double cMAX_MANA_ON_BOARD = (Game_Ns::cTURNS)*(Game_Ns::cTURNS + 1)/(double)2;
   
   while (false == isAtHighest)
   {
      isAtHighest = true;
      
      for (int a = Card_Ns::cMAX; a >= Card_Ns::cMIN; --a)
      {
         for (int b = Card_Ns::cMAX; b >= Card_Ns::cMIN; --b)
         {
            if (a != b)
            {
               Deck_Cl currentDeck(deckWithHighestMana);
              
               if(true == currentDeck.modifyOneCard(a,b))
               {                  
                  double highestManaCurrentDeck = runWithDeck(currentDeck);
                  
                  // std::cout << std::setw(6) << highestManaCurrentDeck << " - Try this deck: " << currentDeck.getDeckHistogram() << std::endl;

                  if (highestManaCurrentDeck > highestMana)
                  {
                     // Set new best.
                     deckWithHighestMana = currentDeck;
                     highestMana = highestManaCurrentDeck;
                     isAtHighest = false;

                     std::cout << std::fixed;
                     std::cout << std::setprecision(2) << cMAX_MANA_ON_BOARD - highestManaCurrentDeck <<
                        " - Turns: " << Game_Ns::cTURNS << 
                        " - mulligan: " << Hand_Ns::cMULLIGAN << " - new best deck: " << currentDeck.getDeckHistogram() << std::endl;

                     // Break out of loops.
                     a = Card_Ns::cMAX;
                     b = Card_Ns::cMAX;
                  }
               }
            }            
         }
      }

      
   }
   
   
   // Generate a random deck.

   // Change a card in the deck.

   // Rerun
   
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
      const double cGAMES_PER_DECK = 100;

      double manaOnBoard = 0;

      // Generate mulligan for this deck.
      const int cMULLIGAN_OVER = Card_Ns::generateRandom(2, 6);
   
      for (int i = 0; i < cGAMES_PER_DECK; ++i)
      {         
         game.play(cMULLIGAN_OVER);
         const double cUNSPENT_GAME = game.getManaOnBoard();
      
         manaOnBoard += cUNSPENT_GAME;
         // std::cout << cUNSPENT_GAME << " - game " << std::endl;

      
         // std::cout << manaOnBoard / (double)(i+1) << " - average so far " << std::endl;
      }
   
      // The average unspent mana.
      const double cAVERAGE_MANA_ON_BOARD = manaOnBoard / cGAMES_PER_DECK;

      // if (cAVERAGE_MANA_ON_BOARD > 51.2)
      //if (cAVERAGE_MANA_ON_BOARD > 26.3) 
      if (cAVERAGE_MANA_ON_BOARD > 42.4) // turn 9
      // if (cAVERAGE_MANA_ON_BOARD > 51.7) // turn 10
      //if (cAVERAGE_MANA_ON_BOARD > 62.1) // turn 11
      {
         std::cout << std::setw(5) << cAVERAGE_MANA_ON_BOARD <<
            " - average - mulligan: " << cMULLIGAN_OVER << " - deck: " << deck.getDeckHistogram() << std::endl;
      }

   }
}

int main()
{
   // Seed the random number generator
   srand(time(NULL));

   // randomOnce();
   //randomDeck();
   changeByOne();
   
   // nineManaDeck();
	return 0;
}
    
