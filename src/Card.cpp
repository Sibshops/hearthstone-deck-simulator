#include <sstream>

#include "include/Card.hpp"


Card_Cl::Card_Cl(
   const int& manaCost)
   : m_manaCost(manaCost),
     m_overload(0),
     m_needed(false),
     m_removal(false)
{
}


bool Card_Cl::operator==(
   const Card_Cl& rh) const
{
   return (m_manaCost == rh.m_manaCost);
}


std::string Card_Cl::getShortString() const
{
   std::ostringstream oss;

   oss << m_manaCost;

   if (m_overload > 0)
   {
      oss << "o" << m_overload;
   }

   // if (true == m_needed)
   // {
   //    oss << "n";
   // }

   if (true == m_removal)
   {
      oss << "r";
   }

   return oss.str();
}
   

Card_Cl Card_Ns::getFireguardDestroyer()
{
   Card_Cl fd(4);

   fd.setOverload(1);

   fd.setAsNeeded();

   return fd;
}


Card_Cl Card_Ns::getStormforgedAxe()
{
   Card_Cl fd(2);

   fd.setOverload(1);

   fd.setAsNeeded();

   return fd;
}

Card_Cl Card_Ns::getDoomhammer()
{
   Card_Cl fd(5);
   fd.setOverload(2);
   fd.setAsNeeded();

   return fd;
}


Card_Cl Card_Ns::getEarthElemental()
{
   Card_Cl fd(5);
   fd.setOverload(3);
   fd.setAsNeeded();

   return fd;
}

Card_Cl Card_Ns::getCrackle()
{
   Card_Cl fd(2);
   fd.setOverload(1);
   fd.setAsNeeded();
   fd.setAsRemoval();
   
   return fd;
}

Card_Cl Card_Ns::getHex()
{
   Card_Cl fd(3);
   fd.setAsNeeded();
   fd.setAsRemoval();
   
   return fd;
}

Card_Cl Card_Ns::getLightningStorm()
{
   Card_Cl fd(3);
   fd.setOverload(2);
   fd.setAsNeeded();
   fd.setAsRemoval();
   
   return fd;
}

Card_Cl Card_Ns::getEarthShock()
{
   Card_Cl fd(1);
   fd.setAsNeeded();
   fd.setAsRemoval();
   
   return fd;
}

Card_Cl Card_Ns::getLightningBolt()
{
   Card_Cl fd(1);
   fd.setOverload(1);
   fd.setAsNeeded();
   fd.setAsRemoval();
   
   return fd;
}

Card_Cl Card_Ns::getForkedLightning()
{
   Card_Cl fd(1);
   fd.setOverload(2);
   fd.setAsNeeded();
   fd.setAsRemoval();
   
   return fd;
}


Card_Cl Card_Ns::getFeralSpirit()
{
   Card_Cl fd(3);
   fd.setOverload(2);
   fd.setAsNeeded();
   
   return fd;
}


Card_Cl Card_Ns::getLavaShock()
{
   // Todo: see what crystals it unlocks. It is all or just current?
   Card_Cl fd(2);
   fd.setAsNeeded();
   fd.setAsRemoval();
   
   return fd;
}


Card_Cl Card_Ns::getLavaBurst()
{
   Card_Cl fd(3);
   fd.setOverload(2);
   fd.setAsNeeded();
   fd.setAsRemoval();
   
   return fd;
}


Card_Cl Card_Ns::getAvenge()
{
   Card_Cl fd(1);
   fd.setAsNeeded();
      
   return fd;
}



Card_Cl Card_Ns::getEquality()
{
   Card_Cl fd(2);
   fd.setAsNeeded();
   fd.setAsRemoval();
   
   return fd;
}

Card_Cl Card_Ns::getConsecration()
{
   Card_Cl fd(4);
   fd.setAsNeeded();
   fd.setAsRemoval();
   
   return fd;
}

