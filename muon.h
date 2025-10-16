// PHYS30762 Programming in C++
// Project - Particle Detector 24/04/2025
// Zak Trivedi 10841354
// Class header for muon derived class

#ifndef MUON_H
#define MUON_H

#include "particle.h"

class Muon : public Particle
{
public:
  // Parameterised constructor 
  Muon(const Four_Momentum &momentum);

  // Destructor
  ~Muon() = default;
  
  // Overriding print function
  void print_data() const override;
};

#endif