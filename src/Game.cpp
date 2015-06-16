#include <iostream>
#include <algorithm>

#include "include/Game.hpp"

// #define debug
Game_Cl::Game_Cl()
   : m_deck(),
     m_hand(),
     m_manaOnBoard()
{
}

void Game_Cl::draw()
{
   // Draw a card from the deck.
   const Card_Cl cCARD = m_deck.draw();

   // Put it into my hand.
   m_hand.draw(cCARD);
}

void Game_Cl::play(const int& mulliganOver)
{
   // Clear my hand.
   m_hand = Hand_Cl();
   
   // We don't have any mana on the board to start.
   m_manaOnBoard = 0;

   // Shuffle deck.
   m_deck.shuffle();  
   
   // Draw 3 cards.
   draw();
   draw();
   draw();
#ifdef debug
   std::cout << "Hand before mulligan: " << m_hand.getString() << std::endl;
#endif   
   // mulligan
   mulligan(mulliganOver);
#ifdef debug
   std::cout << "Hand after mulligan: " << m_hand.getString() << std::endl;
#endif
   
   // Play turns
   for (int turn = 1; turn <= Game_Ns::cTURNS; ++turn)
   {
#ifdef debug
      std::cout << "Turn " << turn << std::endl;
#endif
      draw();
#ifdef debug
      std::cout << "My hand After Drawing: " << m_hand.getString() << std::endl;
#endif

      double manaOnBoard = 0;
      
      m_hand.playTurn(turn, manaOnBoard);
      
      m_manaOnBoard += manaOnBoard;
#ifdef debug
      std::cout << "OnBoard this turn "  << manaOnBoard
                << ", Total On Board " <<  m_manaOnBoard 
                << ", Hand " << m_hand.getString() << std::endl;
#endif
   }
#ifdef debug
   std::cout << m_manaOnBoard << " On Board for deck = " << m_deck.getDeckHistogram() << std::endl;
#endif
}


void Game_Cl::mulligan(
   const int& mulliganOver)
{
   m_hand.mulliganDiscard(mulliganOver);

   // Get cards still in my hand.
   const Card_Cl::List_Ty& cCARDS_IN_HAND = m_hand.getHand();
   
   // Keep these cards in hand. cards back into the deck.
   m_deck.mulliganKeep(cCARDS_IN_HAND);

   // Draw until my hand is up to 3.
   for (int i = cCARDS_IN_HAND.size(); i < 3; ++i)
   {
      draw();
   }
}
