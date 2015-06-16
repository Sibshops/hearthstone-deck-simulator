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

   /// Define the equality operator.
   bool operator==(
      // Pass the right hand element.
      const Card_Cl& rh) const;

   void setManaCost(
      const int& manaCost);
   
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

inline void Card_Cl::setManaCost(
      const int& manaCost)
{
   m_manaCost = manaCost;
}

namespace Card_Ns
{
   // Generate a random cost card from 1-10.
   Card_Cl generateRandomCard(
      const int min,
      const int max);

   // generate a mana cost between min and max.
   int generateRandom(
      const int min,
      const int max);
   
   const int cMIN = 1;

   const int cMAX = 9;
}

inline int Card_Ns::generateRandom(
   const int min,
   const int max)
{
   // The manacost for the card.
   int randomNum = rand() % (max + 1 - min) + min;

   return randomNum;
}

inline Card_Cl Card_Ns::generateRandomCard(
   const int min,
   const int max)
{
   // The manacost for the card.
   int manaCost = rand() % (max + 1 - min) + min;

   return Card_Cl(manaCost);
}


   
#endif /* CARD_HPP */
