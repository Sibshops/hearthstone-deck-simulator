#ifndef GAME_HPP
#define GAME_HPP

#include <ctime>
#include <cstdlib>
#include <vector>

#include "include/Deck.hpp"
#include "include/Hand.hpp"

// A single game. Subclass to make special games.
class Game_Cl
{
public:

   /// Don't use a private constructor
   Game_Cl();

   /// Set the Deck for the game.
   void setDeck(
      /// Set the Deck
      const Deck_Cl& deck);
   
   /// Play a game with the deck.
   void play(
      // Mulligan cards greater than this number.
      const int& mulliganOver);

   /// Get the amount of mana on the board after the game.
   double getManaOnBoard() const;

   void mulligan(
      // mulligan cards over this value.
      const int& mulliganOver);
   
private:

   // Draw a card from the deck and put it into my hand.
   void draw();
   
   /// My deck.
   Deck_Cl m_deck;

   /// My hand.
   Hand_Cl m_hand;

   /// The amount of mana lost this game.
   double m_manaOnBoard;
};

inline double Game_Cl::getManaOnBoard() const
{
   return m_manaOnBoard;
}

inline void Game_Cl::setDeck(
   const Deck_Cl& deck)
{
   m_deck = deck;
}
   
namespace Game_Ns
{
   // The number of turns to play.
   const int cTURNS = 9;
}

#endif /* GAME_HPP */
