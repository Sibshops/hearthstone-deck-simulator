#include <iostream>
#include <algorithm>

#include "include/Game.hpp"

//#define debug

Game_Cl::Game_Cl()
   : m_deck(),
     m_hand(),
     m_board()
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
   
   // Clear the board.
   m_board = Board_Cl();

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
      // Take the next turn.
      m_board.nextTurn();
      
      m_hand.playTurn(m_board);
      
#ifdef debug
      std::cout << "After turn - "  << m_board.getString() 
                << ", Hand " << m_hand.getString() << std::endl;
#endif
   }
#ifdef debug
   std::cout << m_board.getString() << " On Board for deck = " << m_deck.getDeckHistogram() << std::endl;
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
