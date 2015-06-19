#ifndef HAND_HPP
#define HAND_HPP
 
#include <vector>

#include "include/Card.hpp"
#include "include/Board.hpp"

// My hand
class Hand_Cl
{
public:

   // The constructor
   Hand_Cl();

   /// Draw a card into the hand.
   void draw(
      /// This is the card drawn
      const Card_Cl& card);

   /// Play a turn. Turn = mana. Return the amount of mana lost.
   void playTurn(
      /// The amount of mana on board after the turn is played.
      Board_Cl& board);

   /// Mulligan these cards from the hand. Discard if they are over this value.
   void mulliganDiscard(
      // Discard cards over this value.
      const int& mulliganOver);   
   
   /// Get the hand as a string.
   std::string getString() const;

   /// Get my hand.
   const Card_Cl::List_Ty& getHand() const;

private:
   
   // The cards in the hand.
   Card_Cl::List_Ty m_cards;
};


inline const Card_Cl::List_Ty& Hand_Cl::getHand() const
{
   return m_cards;
}

namespace Hand_Ns
{
   // Set the mulligan for this run.
   const int cMULLIGAN = 4;
   
   /// Cast a card from the hand, return mana unused.
   void cast(
      /// The cards in the hand, return the cards still available.
      Card_Cl::List_Ty& m_cards,
      /// Pass the boardstate before casting. Return the board state
      /// after casting.
      Board_Cl& board);      

   // Get a string for a list of cards.
   std::string getString(
      // The cards
      const Card_Cl::List_Ty& cards);
}
#endif /* HAND_HPP */

