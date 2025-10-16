// PHYS30762 Programming in C++
// Project - Particle Detector 24/04/2025
// Zak Trivedi 10841354
// Implementation of member functions for neutrino derived class

#include "neutrino.h"
#include <iostream>

// Parameterised constructor - automatically sets rest mass and charge
Neutrino::Neutrino(const Four_Momentum &momentum, const std::string &flavour)
  : Particle(momentum, 0.0, 0.0), m_flavour(flavour)
{}

// Print function
void Neutrino::print_data() const
{
  std::cout<<"Neutrino ("<<m_flavour<<"): "
           <<"Energy="<<m_momentum.get_energy()<<" MeV, "
           <<"Px="<<m_momentum.get_px()<<" MeV/c, "
           <<"Py="<<m_momentum.get_py()<<" MeV/c, "
           <<"Pz="<<m_momentum.get_pz()<<" MeV/c, "
           <<"Rest mass="<<m_rest_mass<<" MeV/c^2, "
           <<"Charge="<<m_charge<<" e\n";
}