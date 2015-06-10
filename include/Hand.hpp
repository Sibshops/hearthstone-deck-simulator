#ifndef HAND_HPP
#define HAND_HPP
 
#include <vector>

#include "include/Card.hpp"

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
      /// The turn number or mana cost.
      int& manaAvailable);

   /// Get the hand as a string.
   std::string getString() const;
   
   // The cards in the hand.
   Card_Cl::List_Ty m_cards;
};


namespace Hand_Ns
{
   /// Cast a card from the hand, return mana unused.
   void cast(
      /// The cards in the hand, return the cards still available.
      Card_Cl::List_Ty& m_cards,
      /// Pass the mana available, return what is left after casting all the cards possible.
      int& manaAvailable);

   // Get a string for a list of cards.
   std::string getString(
      // The cards
      const Card_Cl::List_Ty& cards);
}
#endif /* HAND_HPP */

