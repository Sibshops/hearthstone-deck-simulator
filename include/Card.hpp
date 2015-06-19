#ifndef CARD_HPP
#define CARD_HPP

#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>
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

   // Get the mana on the board. Cost + overload.
   int getTotalManaCost() const;
   
   /// Get the mana cost for the card.
   int getManaCost() const;

   // Get the overload.
   void setManaCost(
      const int& manaCost);

   /// Get the mana cost for the card.
   int getOverload() const;
   
   // Set the overload.
   void setOverload(
      const int& overload);

   /// Define the equality operator.
   bool operator==(
      // Pass the right hand element.
      const Card_Cl& rh) const;

   /// Is the card needed in the deck?
   bool isNeeded() const;

   /// Mark the card as needed.
   bool setAsNeeded();

   /// Is the card needed in the deck?
   bool isRemoval() const;

   /// Mark the card as needed.
   bool setAsRemoval();

   /// Get a short string representation of the card.
   std::string getShortString() const;
   
private:

   // Don't use a private constructor
   Card_Cl();

   // How much mana does this card cost.
   int m_manaCost;

   // How much overload
   int m_overload;
   
   // Is the card needed in the deck?
   bool m_needed;

   // Is this a removal card? If so cast it if there is one more available mana crystal.
   bool m_removal;

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


inline int Card_Cl::getOverload() const
{
   return m_overload;
}

inline void Card_Cl::setOverload(
      const int& overload)
{
   m_overload = overload;
}

inline int Card_Cl::getTotalManaCost() const
{
   return (m_manaCost + m_overload);
}


inline bool Card_Cl::isNeeded() const
{
   return m_needed;
}

inline bool Card_Cl::setAsNeeded()
{
   m_needed = true;
}   

inline bool Card_Cl::isRemoval() const
{
   return m_removal;
}

inline bool Card_Cl::setAsRemoval()
{
   m_removal = true;
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

   /// Shaman
   Card_Cl getFireguardDestroyer();
   Card_Cl getStormforgedAxe();
   Card_Cl getDoomhammer();
   Card_Cl getEarthElemental();
   Card_Cl getCrackle();
   Card_Cl getHex();
   Card_Cl getLightningStorm();
   Card_Cl getEarthShock();
   Card_Cl getLightningBolt();
   Card_Cl getForkedLightning();
   Card_Cl getLavaShock();
   Card_Cl getFeralSpirit();
   Card_Cl getLavaBurst();
   
   /// Paladin
   Card_Cl getAvenge();
   Card_Cl getEquality();
   Card_Cl getConsecration();
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
