// PHYS30762 Programming in C++
// Project - Particle Detector 24/04/2025
// Zak Trivedi 10841354
// Implementation of member functions for 4 momentum class

#include "four_momentum.h"
#include <stdexcept>

// Parameterised Constructor using setters.
Four_Momentum::Four_Momentum(double energy,double px,double py,double pz)
{
  set_energy(energy);
  set_px(px);
  set_py(py);
  set_pz(pz);
}

// Setter definitions
void Four_Momentum::set_energy(double energy)
{
  if(energy < 0)
  {
    throw std::invalid_argument("Particle energy cannot be negative!");
  }
  else
  {
  m_energy=energy;
  }
}