// PHYS30762 Programming in C++
// Project - Particle Detector 24/04/2025
// Zak Trivedi 10841354
// Class header for hadron derived class

#ifndef HADRON_H
#define HADRON_H

#include "particle.h"
#include "four_momentum.h"
#include <string>
#include <iostream>

class Hadron : public Particle
{
private:
  std::string m_name;

public:
  // Parameterised constructor
  Hadron(const Four_Momentum &momentum,const std::string &name, double rest_mass, double charge);

  // Destructor
  ~Hadron() = default;
  
  // Getter for name
  const std::string &get_name() const {return m_name;}

  // Setter for name
  void set_name(const std::string name) {m_name = name;}
  
  // Overriding print function
  void print_data() const override;
};

#endif 