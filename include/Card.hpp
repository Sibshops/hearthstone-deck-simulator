#ifndef CARD_HPP
#define CARD_HPP

#include <ctime>
#include <cstdlib>
#include <vector>
#include <list>

// A single card. Subclass to make special cards.
class Card_Cl
{
public:

   /// Define a vector type of cards.
   typedef std::vector<Card_Cl> Vector_Ty;

   /// Define the list type.
   typedef std::list<Card_Cl> List_Ty;

   /// A non default constructor, sets the mana cost.
   Card_Cl(
      /// The cost for the card.
      const int& manaCost);

   /// Get the mana cost for the card.
   int getManaCost() const;
   
private:

   // Don't use a private constructor
   Card_Cl();

   // How much mana does this card cost.
   int m_manaCost;
};


inline int Card_Cl::getManaCost() const
{
   return m_manaCost;
}

namespace Card_Ns
{
   // Generate a random cost card from 1-10.
   static Card_Cl generateRandomCard();

   const int cMIN = 1;

   const int cMAX = 9;
}


inline Card_Cl Card_Ns::generateRandomCard()
{
   // The manacost for the card.
   int manaCost = rand() % (Card_Ns::cMAX + 1 - Card_Ns::cMIN) + Card_Ns::cMIN;

   return Card_Cl(manaCost);
}


   
#endif /* CARD_HPP */
