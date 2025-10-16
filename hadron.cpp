// PHYS30762 Programming in C++
// Project - Particle Detector 24/04/2025
// Zak Trivedi 10841354
// Implementation of member functions for hadron derived class

#include "hadron.h"
#include <iostream>

// Parameterised constructor 
Hadron::Hadron(const Four_Momentum &momentum, const std::string &name, double rest_mass, double charge)
  : Particle(momentum, rest_mass, charge), m_name(name)
{}

// Print function
void Hadron::print_data() const
{
  std::cout<<"Hadron ("<<m_name<<"): "
           <<"Energy="<<m_momentum.get_energy()<<" MeV, "
           <<"Px="<<m_momentum.get_px()<<" MeV/c, "
           <<"Py="<<m_momentum.get_py()<<" MeV/c, "
           <<"Pz="<<m_momentum.get_pz()<<" MeV/c, "
           <<"Rest mass="<<m_rest_mass<<"MeV/c^2, "
           <<"Charge="<<m_charge<<" e\n";
}

