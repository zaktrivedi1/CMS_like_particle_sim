// PHYS30762 Programming in C++
// Project - Particle Detector 24/04/2025
// Zak Trivedi 10841354
// Class header for photon derived class

#ifndef PHOTON_H
#define PHOTON_H

#include "particle.h"
#include "four_momentum.h"
#include <string>
#include <iostream>

class Photon : public Particle
{
public:
  // Parameterised constructor
  Photon(const Four_Momentum &momentum);

  // Destructor
  ~Photon() = default;
  
  // Overriding print function
  void print_data() const override;
};

#endif