#include <sstream>
#include <cmath>
#include <algorithm>
#include <limits>

#include "include/Board.hpp"


std::string Board_Cl::getString() const
{
   std::ostringstream oss;
   
   oss << "Mana on Board = " << m_manaOnBoard
       << ", Mana Crystals = " << m_manaCrystals
       << ", Overload = " << m_overload
       << ", Mana Available = " << m_manaAvailable;

   return oss.str();
}


void Board_Cl::nextTurn()
{
   // Increment mana crystals up to 10.
   m_manaCrystals = std::min(m_manaCrystals + 1, 10);

   // Mana available is the crystals minus the overload.
   m_manaAvailable = m_manaCrystals - m_overload;

   m_overload = 0;

   // Mana on board unaffected.
}



bool Board_Cl::boardBetterThan(
   const Card_Cl::List_Ty& handAfterCast,
   const Board_Cl& bestBoardState,
   const Card_Cl::List_Ty& handWithBestBoardState) const
{
   // Prefer more mana on board. But subtract overload debt.
   const double cADJ_MOB = getEndGameManaOnBoard();

   // 
   const double cADJ_MOB_BEST = bestBoardState.getEndGameManaOnBoard();

   // Prefer more mana on board.
   if (cADJ_MOB > cADJ_MOB_BEST)
   {
      return true;
   }
   else if (cADJ_MOB < cADJ_MOB_BEST)
   {
      return false;
   }
   else
   {
      // The have the same mana on board.
      // Pick the one with less cards.
      if (handAfterCast.size() > handWithBestBoardState.size())
      {
         return true;
      }
      else if (handAfterCast.size() < handWithBestBoardState.size())
      {
         return false;
      }
      else
      {
         // Same adjusted mana on board, same cards, Pick the one with more mana on the board. Prefer's overloaded cards.
         if (m_manaOnBoard > bestBoardState.m_manaOnBoard)
         {
            return true;
         }
         else if (m_manaOnBoard < bestBoardState.m_manaOnBoard)
         {
            return false;
         }
         else
         {
            return false;
         }
      }
   }  
}

bool Board_Cl::castCard(
   const Card_Cl& card)
{
   if (card.getManaCost() > m_manaAvailable)
   {
      // Not enough mana.
      return false;
   }
   else if (card.isRemoval())
   {
      // Is this card removal? In order for removal to be worth it, it
      // has to remove a more expensive card. This can only happen
      // when the opponent has enough mana.
      // For example, lightning bolt costs 2 mana total. Cast when there are 3 or more mana crystals.
      if (card.getManaOnBoard() >= m_manaCrystals)
      {
         return false;
      }
      else
      {
         // Assume we are removing a card that is the same cost or 1
         // higher. For example, Hex on a yetti, is 4 mana gained on
         // board since the yetti is gone.
         m_manaOnBoard = m_manaOnBoard + 0.5;         
      }
   }

   m_manaAvailable = m_manaAvailable - card.getManaCost();
   m_manaOnBoard = m_manaOnBoard + card.getManaOnBoard();
   m_overload = m_overload + card.getOverload();

   return true;
}
   
