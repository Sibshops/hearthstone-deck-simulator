#include <cstdlib>
#include <iostream>
#include <ctime>
#include <sstream>
#include <algorithm>

#include "include/Deck.hpp"

Deck_Cl::Deck_Cl()
   : m_cards(),
     m_cardIndex(0)
{
}

void Deck_Cl::fillRestWithRandom()
{
   for (int cardIdx = m_cards.size();
        cardIdx < Deck_Ns::cSIZE;
        ++cardIdx)
   {
      //m_cards.push_back(Card_Ns::generateRandomCard(Card_Ns::cMIN, Card_Ns::cMAX));
      m_cards.push_back(Card_Ns::generateRandomCard(Card_Ns::cMIN+1, Card_Ns::cMAX-1));
   }
}


bool Deck_Cl::modifyOneCard(
   const int fromValue,
   const int toValue)
{
   bool found = false;
   
   // Go through the deck looking for the card.
   for (Card_Cl::Vector_Ty::iterator deckIter = m_cards.begin();
        deckIter != m_cards.end();
        ++deckIter)
   {
      if (true == deckIter->isNeeded())
      {
         // Ignore needed cards.
      }
      else if (fromValue == deckIter->getManaCost())
      {
         deckIter->setManaCost(toValue);
         found = true;
         break;
      }
   }

   return found;
}
   


std::string Deck_Cl::getDeckHistogram() const
{
   std::vector<int> histogram(Card_Ns::cMAX + 1, 0);

   // Build the histogram
   for(Card_Cl::Vector_Ty::const_iterator cardIter = m_cards.begin();
       cardIter != m_cards.end();
       ++cardIter)
   {
      // The cost of the card.
      const int cMANA_COST = cardIter->getManaCost();

      ++histogram[cMANA_COST];      
   }

   // The output string stream.
   std::stringstream oss;
   
   // Print the histogram
   for (int i = 1; i < histogram.size(); ++i)
   {
      oss << i << "-" << histogram[i] << " ";
   }

   const std::string cNEEDED_STRING = getNeededString();

   if (!cNEEDED_STRING.empty())
   {
      oss << "- with: " << cNEEDED_STRING;
   } 
  
   return oss.str();
}
   

void Deck_Cl::shuffle()
{
   m_cardIndex = 0;
   std::random_shuffle(m_cards.begin(), m_cards.end());   
}


void Deck_Cl::mulliganKeep(const Card_Cl::List_Ty& stillInHand)
{
   // If there are two cards in the hand, point the card index to 2.
   m_cardIndex = stillInHand.size();
   
   // The iterator to swap to.
   Card_Cl::Vector_Ty::iterator startDeckIter = m_cards.begin();

   // Find each card in the deck and put it into the start index.
   for (Card_Cl::List_Ty::const_iterator handIter = stillInHand.begin();
        stillInHand.end() != handIter;
        ++handIter)
   {
      // Go through the deck looking for the card.
      for (Card_Cl::Vector_Ty::iterator deckIter = startDeckIter;
           deckIter != m_cards.end();
           ++deckIter)
      {
         if (*handIter == *deckIter)
         {
            // We found the card, swap it with the first element and increment the start of the deck.
            iter_swap(deckIter, startDeckIter);

            startDeckIter++;          

            break;
         }
      }
   }
   
   // Shuffle the rest of the deck.
   std::random_shuffle(startDeckIter, m_cards.end());
}


std::string Deck_Cl::getFullDeckString() const
{
   std::ostringstream oss;

   for (Card_Cl::Vector_Ty::const_iterator cardIter = m_cards.begin();
        m_cards.end() != cardIter;
        ++cardIter)
   {
      oss << cardIter->getShortString() << " ";
   }

   return oss.str();   
}

std::string Deck_Cl::getNeededString() const
{
   std::ostringstream oss;

   for (Card_Cl::Vector_Ty::const_iterator cardIter = m_cards.begin();
        m_cards.end() != cardIter;
        ++cardIter)
   {
      if (cardIter->isNeeded())
      {
         oss << cardIter->getShortString() << " ";
      }
   }

   return oss.str();   

}

