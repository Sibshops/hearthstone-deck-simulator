#include <string>
#include <sstream>

#include "include/Hand.hpp"


Hand_Cl::Hand_Cl()
   : m_cards()
{
}

void Hand_Cl::draw(
   const Card_Cl& card)
{
   m_cards.push_back(card);
}

void Hand_Cl::playTurn(
   int& manaAvailable)
{
   /*
   // Try to burn as much mana with as few cards as possible.

   // Try without Ability
   int manaAvailableNoAbility = manaAvailable;
   Card_Cl::List_Ty cardsNoAbility = m_cards;
   Hand_Ns::cast(cardsNoAbility, manaAvailableNoAbility);

   // Try with ability.
   int manaAvailableWithAbility = 100000;
   Card_Cl::List_Ty cardsWithAbility;

   // Only use it if it is greater than 2
   if (manaAvailable >= 2)
   {
      manaAvailableWithAbility = manaAvailable - 2;
      cardsWithAbility = m_cards;
      Hand_Ns::cast(cardsWithAbility, manaAvailableWithAbility);
   }


   // If there is a choice between a 2 mana card or a 1 mana card +
   // hero ability. Use the 2 mana card.
   // The with ability has to beat the without ability by 2.
   if ((manaAvailableWithAbility + 1) < manaAvailableNoAbility)
   {
      m_cards = cardsWithAbility;
      manaAvailable = manaAvailableWithAbility;
   }
   else
   {
      m_cards = cardsNoAbility;
      manaAvailable = manaAvailableNoAbility;      
   }
   */
   
   Hand_Ns::cast(m_cards, manaAvailable);

   // If there is 2 mana available, use ability.
   if (manaAvailable >= 2)
   {
      manaAvailable -= 2;
   }
}



void Hand_Ns::cast(
   Card_Cl::List_Ty& cards,
   int& manaAvailable)
{
   // The hand with the lowest left over mana.
   Card_Cl::List_Ty handWithLowestMana = cards;

   // The best leftover mana.
   int lowestMana = manaAvailable;
   
   for (Card_Cl::List_Ty::iterator cardsIter = cards.begin();
        cardsIter != cards.end();
        ++cardsIter)
   {
      /// Mana cost for card.
      const int cMANA_COST = cardsIter->getManaCost();

      // Can we cast this card?
      if (cMANA_COST <= manaAvailable)
      {
         // Yes, we can cast it. Remove the card from the deck and recast.
         Card_Cl::List_Ty cardsAfterCast;

         {
            // A temporary iterator for building the cards.
            Card_Cl::List_Ty::iterator tmpCardsIter = cardsIter;
            
            cardsAfterCast.insert(cardsAfterCast.begin(), cards.begin(), tmpCardsIter);
            ++tmpCardsIter;
            cardsAfterCast.insert(cardsAfterCast.end(), tmpCardsIter, cards.end());
         }
            
         // Get th mana after the cast.
         int manaAfterCast = manaAvailable - cMANA_COST;

         // Cast without the card.
         cast(cardsAfterCast, manaAfterCast);

         if (manaAfterCast < lowestMana)
         {
            // This hand uses up more mana.
            lowestMana = manaAfterCast;
            handWithLowestMana = cardsAfterCast;
         }
         else if ((manaAfterCast == lowestMana) &&
                  (cardsAfterCast.size() > handWithLowestMana.size()))
         {
            // This hand is bigger after casting. It uses up less cards.
            lowestMana = manaAfterCast;
            handWithLowestMana = cardsAfterCast;
         }
         // If the hand is bigger, use this.
      }      
   }

   // Set the return value to the best.
   cards = handWithLowestMana;
   manaAvailable = lowestMana;   
}


std::string Hand_Cl::getString() const
{
   return Hand_Ns::getString(m_cards);
}


std::string Hand_Ns::getString(
   const Card_Cl::List_Ty& cards)
{
   std::ostringstream oss;

   for (Card_Cl::List_Ty::const_iterator cardIter = cards.begin();
        cards.end() != cardIter;
        ++cardIter)
   {
      oss << cardIter->getManaCost() << " ";
   }

   return oss.str();   
}
