// PHYS30762 Programming in C++
// Project - Particle Detector 24/04/2025
// Zak Trivedi 10841354
// Implementation of member functions for particle abstract base class

#include "Particle.h"
#include <stdexcept>

// Parameterised constructor using setters for validation.
Particle::Particle(const Four_Momentum &momentum, double rest_mass, double charge)
  : m_momentum(momentum)
{
  set_rest_mass(rest_mass);
  set_charge(charge);
}

// Setter for rest mass - throws an error if negative
void Particle::set_rest_mass(double rest_mass)
{
  if(rest_mass >= 0.0)
  {
    m_rest_mass = rest_mass;
  }
  else
  {
    throw std::invalid_argument("Rest mass must be non-negative.\n");
  }
}
