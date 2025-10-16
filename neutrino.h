// PHYS30762 Programming in C++
// Project - Particle Detector 24/04/2025
// Zak Trivedi 10841354
// Class header for neutrino derived class

#ifndef NEUTRINO_H
#define NEUTRINO_H

#include "particle.h"
#include <string>

class Neutrino : public Particle
{
private:
  std::string m_flavour;

public:
  // Parameterised constructor
  Neutrino(const Four_Momentum &momentum,const std::string &flavour);

  // Destructor 
  ~Neutrino() = default;
  
  // Getter for flavour
  const std::string &get_flavour() const {return m_flavour;}

  // Overriding print function
  void print_data() const override;
};

#endif