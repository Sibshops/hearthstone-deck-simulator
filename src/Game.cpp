#include <iostream>
#include <algorithm>

#include "include/Game.hpp"

Game_Cl::Game_Cl()
   : m_deck(),
     m_hand(),
     m_unspentMana()
{
}

void Game_Cl::draw()
{
   // Draw a card from the deck.
   const Card_Cl cCARD = m_deck.draw();

   // Put it into my hand.
   m_hand.draw(cCARD);
}

void Game_Cl::play()
{
   // Clear my hand.
   m_hand = Hand_Cl();
   
   // We don't have any unspent mana.
   m_unspentMana = 0;

   // Shuffle deck.
   m_deck.shuffle();  
   
   // Draw 3 cards.
   draw();
   draw();
   draw();
   
   // Play 10 turns
   for (int turn = 1; turn <= Game_Ns::cTURNS; ++turn)
   {
#ifdef debug
      std::cout << "Turn " << turn << std::endl;
#endif
      int manaAvailable = turn;
      
      draw();
#ifdef debug
      std::cout << "My hand After Drawing: " << m_hand.getString() << std::endl;
#endif 
      m_hand.playTurn(manaAvailable);
      
      m_unspentMana += manaAvailable;
#ifdef debug
      std::cout << "Unspent this turn "  << manaAvailable
                << ", Total Unspent " <<  m_unspentMana 
                << ", Hand " << m_hand.getString() << std::endl;
#endif
   }
#ifdef debug
   std::cout << m_unspentMana << " Unspent for deck = " << m_deck.getDeckHistogram() << std::endl;
#endif
}
