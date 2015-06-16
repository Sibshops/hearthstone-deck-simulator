#include <string>
#include <sstream>
#include <set>

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
   const int& manaAvailable,
   double& manaOnBoard)
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
   
   Hand_Ns::cast(m_cards, manaAvailable, manaOnBoard);

   // If there is 2 mana available more than on the board, cast the hero power.
   if (manaAvailable - manaOnBoard >= 2)
   {
      // The hero power uses  half a mana.
      manaOnBoard += 0.5;
   }
}



void Hand_Ns::cast(
   Card_Cl::List_Ty& cards,
   const int& manaAvailable,
   double& manaOnBoard)
{
   // The hand with the lowest left over mana.
   Card_Cl::List_Ty handWithMostOnBoard = cards;

   // The best leftover mana.
   double mostManaOnBoard = manaOnBoard;
   
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
            
         // Get the mana after the cast.
         int manaAfterCast = manaAvailable - cMANA_COST;

         // The mana on board after cast
         double manaOnBoardAfterCast = manaOnBoard + cMANA_COST;
         
         // Cast without the card.
         cast(cardsAfterCast, manaAfterCast, manaOnBoardAfterCast);

         if (manaOnBoardAfterCast > mostManaOnBoard)
         {
            // There is more on the board after casting this card, set it as the best.
            mostManaOnBoard = manaOnBoardAfterCast;
            handWithMostOnBoard = cardsAfterCast;
         }
         else if ((manaAfterCast == mostManaOnBoard) &&
                  (cardsAfterCast.size() > handWithMostOnBoard.size()))
         {
            // This hand is bigger after casting. It uses up less
            // cards, one 5 mana card is better than a 2 and 3.
            mostManaOnBoard = manaOnBoardAfterCast;
            handWithMostOnBoard = cardsAfterCast;
         }

      }      
   }

   // Set the return value to the best.
   cards = handWithMostOnBoard;
   manaOnBoard = mostManaOnBoard;
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


void Hand_Cl::mulliganDiscard(
   const int& mulliganOver)
{
   // cards after mulliganing.
   Card_Cl::List_Ty cardsAfterMulligan;

   // Mulligane duplicates.
   std::set<int> inHand;
   
   for (Card_Cl::List_Ty::const_iterator oldHandIter = m_cards.begin();
        oldHandIter != m_cards.end();
        ++oldHandIter)
   {
      const int cMANA_COST = oldHandIter->getManaCost();
      
      if (cMANA_COST > mulliganOver)
      {
         // We don't want this card. It is over the mulligan.
      }
      else if (inHand.end() == inHand.find(cMANA_COST))
      {
         // Can't find the card. Add it.
         
         inHand.insert(cMANA_COST);
         cardsAfterMulligan.push_back(*oldHandIter);
      }
   }

   // Set my hand.
   m_cards = cardsAfterMulligan;
}
