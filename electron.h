// PHYS30762 Programming in C++
// Project - Particle Detector 24/04/2025
// Zak Trivedi 10841354
// Class header for derived electron class

#ifndef ELECTRON_H
#define ELECTRON_H

#include <string>
#include <iostream>
#include "particle.h"

class Electron : public Particle
{
public:

  // Parameterised constructor
  Electron(const Four_Momentum &momentum);

  // Destructor
  ~Electron() = default;
  
  // Overriding print function
  void print_data() const override;
};

#endif

