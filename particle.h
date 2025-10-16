// PHYS30762 Programming in C++
// Project - Particle Detector 24/04/2025
// Zak Trivedi 10841354
// Particle abstract base class header

#ifndef PARTICLE_H
#define PARTICLE_H

#include "four_momentum.h"

class Particle
{
protected:
  Four_Momentum m_momentum;
  double m_rest_mass;
  double m_charge;

public:
  // Parameterised constructor.
  Particle(const Four_Momentum &momentum, double rest_mass, double charge);

  // Destructor.
  virtual ~Particle() = default;

  // Pure virtual print function
  virtual void print_data() const=0;

  // Getters
  const Four_Momentum &get_momentum() const {return m_momentum;}
  double get_rest_mass() const {return m_rest_mass;}
  double get_charge() const {return m_charge;}
  
  // Setters
  void set_rest_mass(double rest_mass);
  void set_charge(double charge) {m_charge = charge;}
};

#endif