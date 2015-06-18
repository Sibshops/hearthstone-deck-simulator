#ifndef BOARD_HPP
#define BOARD_HPP

 
#include <vector>

#include "include/Card.hpp"

// My board
class Board_Cl
{
public:

   // The constructor
   Board_Cl();

   // Set the overload
   void setOverload(
      const int& overload);

   // Get the overload.
   int getOverload() const;

   // Set the manaOnBoard
   void setManaOnBoard(
      const double& manaOnBoard);

   // Get the manaOnBoard.
   double getManaOnBoard() const;

   // Set the manaAvailable
   void setManaAvailable(
      const int& manaAvailable);

   // Get the manaAvailable.
   int getManaAvailable() const;

   // Get the mana on the board at end game. Mana on board - mana overload.
   double getEndGameManaOnBoard() const;
   
   // Do the next turn. Subtracts overload from turn number.
   void nextTurn();
   
   // Get the string.
   std::string getString() const;

   // Play the card on the board. Return false if it can't be played.
   bool castCard(
      // The card to play.
      const Card_Cl& card);
   
   // Is his board better than best?
   bool boardBetterThan(
      const Card_Cl::List_Ty& handAfterCast,
      const Board_Cl& bestBoardState,
      const Card_Cl::List_Ty& handWithBestBoardState) const;        
   
private:

   double m_manaOnBoard;
   
   int m_manaCrystals;
   
   int m_overload;

   int m_manaAvailable;   
};

inline Board_Cl::Board_Cl()
   : m_manaOnBoard(0),
     m_manaCrystals(0),
     m_overload(0),
     m_manaAvailable(0)
{
}


inline void Board_Cl::setOverload(
   const int& overload)
{
   m_overload = overload;
}

inline int Board_Cl::getOverload() const
{
   return m_overload;
}
   
inline void Board_Cl::setManaOnBoard(
   const double& manaOnBoard)
{
   m_manaOnBoard = manaOnBoard;
}

inline double Board_Cl::getManaOnBoard() const
{
   return m_manaOnBoard;
}

inline void Board_Cl::setManaAvailable(
   const int& manaAvailable)
{
   m_manaAvailable = manaAvailable;
}

inline int Board_Cl::getManaAvailable() const
{
   return m_manaAvailable;
}

inline double Board_Cl::getEndGameManaOnBoard() const
{
   return m_manaOnBoard - m_overload;
}
   


#endif /* BOARD_HPP */

