// PHYS30762 Programming in C++
// Project - Particle Detector 24/04/2025
// Zak Trivedi 10841354
// Implementation of member functions for muon derived class

#include "muon.h"
#include <iostream>

// Parameterised constructor - automatically sets rest mass and charge
Muon::Muon(const Four_Momentum &momentum)
  : Particle(momentum, 105.7, -1.0)
{}

// Print function
void Muon::print_data() const
{
  std::cout<<"Muon: "
           <<"Energy="<<m_momentum.get_energy()<<" MeV, "
           <<"Px="<<m_momentum.get_px()<<" MeV/c, "
           <<"Py="<<m_momentum.get_py()<<" MeV/c, "
           <<"Pz="<<m_momentum.get_pz()<<" MeV/c, "
           <<"Rest mass="<<m_rest_mass<<" MeV/c^2, "
           <<"Charge="<<m_charge<<" e\n";
}
