#ifndef DECK_HPP
#define DECK_HPP

 
#include <vector>
#include <string>

#include "include/Card.hpp"


// My deck
class Deck_Cl
{
public:

   // The constructor
   Deck_Cl();

   // Populate the deck with 30 random cards. Mana 1-10.
   void populateWithRandom();

   // Get the deck histogram as a string
   std::string getDeckHistogram() const;

   /// Draw a card from the deck.
   Card_Cl draw();

   /// Shuffle the deck.
   void shuffle();

   /// Add a card to the deck.
   void addCard(
      /// The card to add.
      const Card_Cl& card);

   // Pass the cards that are still in my hand. Shuffle the rest of the deck.
   void mulliganKeep(
      // These cards are still in my hand.
      const Card_Cl::List_Ty& stillInHand);

   // Modify one card in the deck. If a card of that value can't be found, return false.
   bool modifyOneCard(
      // The value of the card to modify.
      const int fromValue,
      // The new value of that card.
      const int toValue);
   
private:
   
   // The cards in the deck. Assume the deck is already shuffled.
   Card_Cl::Vector_Ty m_cards;

   // The current card.
   int m_cardIndex;
};

inline Card_Cl Deck_Cl::draw()
{
   return m_cards[m_cardIndex++];
}

inline void Deck_Cl::addCard(
   const Card_Cl& card)
{
   m_cards.push_back(card);
}


namespace Deck_Ns
{
   const int cSIZE = 30;
};

#endif /* DECK_HPP */
