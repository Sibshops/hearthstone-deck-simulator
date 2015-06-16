#include "include/Card.hpp"


/*
Card_Cl::Card_Cl()
   : m_manaCost(-1)
{
}
*/

Card_Cl::Card_Cl(
   const int& manaCost)
   : m_manaCost(manaCost)
{
}


bool Card_Cl::operator==(
   const Card_Cl& rh) const
{
   return (m_manaCost == rh.m_manaCost);
}
   
