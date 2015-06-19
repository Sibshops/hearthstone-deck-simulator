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
   Board_Cl& board)
{   
   Hand_Ns::cast(m_cards, board);

   // If there is 2 mana available more than on the board, cast the hero power

   if (board.getManaAvailable() >= 2)
   {
      board.setManaOnBoard(board.getManaOnBoard() + 0.5);
      board.setManaAvailable(board.getManaAvailable() - 2);
   }
}



void Hand_Ns::cast(
   Card_Cl::List_Ty& cards,
   Board_Cl& board)
{
   // The hand with the best board state.
   Card_Cl::List_Ty handWithBestBoardState = cards;

   // This is the best board state that we determined.
   Board_Cl bestBoardState = board;
   
   for (Card_Cl::List_Ty::iterator cardsIter = cards.begin();
        cardsIter != cards.end();
        ++cardsIter)
   {
      Board_Cl boardAfterCast(board);         
                  
      // Can we cast this card?
      if (boardAfterCast.castCard(*cardsIter))
      {
         // Yes, we can cast it. Remove the card from the deck and cast the next card.
         Card_Cl::List_Ty handAfterCast;

         {
            // A temporary iterator for building the cards.
            Card_Cl::List_Ty::iterator tmpCardsIter = cardsIter;
            
            handAfterCast.insert(handAfterCast.begin(), cards.begin(), tmpCardsIter);
            ++tmpCardsIter;
            handAfterCast.insert(handAfterCast.end(), tmpCardsIter, cards.end());
         }

         // Cast without the card.
         cast(handAfterCast, boardAfterCast);

         if (boardAfterCast.boardBetterThan(handAfterCast,
                                            bestBoardState,
                                            handWithBestBoardState))
         {
            // There is more on the board after casting this card, set it as the best.
            bestBoardState = boardAfterCast;
            handWithBestBoardState = handAfterCast;
         }
      }      
   }

   // Set the return value to the best.
   cards = handWithBestBoardState;
   board = bestBoardState;
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
      oss << cardIter->getShortString() << " ";
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
      else if (oldHandIter->isRemoval() &&
               (oldHandIter->getTotalManaCost() > mulliganOver))
      {
         // This card is removal. We can't play it until there is someone on the board who has a higher mana cost.
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
