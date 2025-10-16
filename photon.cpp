// PHYS30762 Programming in C++
// Project - Particle Detector 24/04/2025
// Zak Trivedi 10841354
// Implementation of member functions for photon derived class

#include "photon.h"
#include <iostream>

// Parameterised constructor
Photon::Photon(const Four_Momentum &momentum)
  : Particle(momentum, 0.0, 0.0)
{}

// Print function
void Photon::print_data() const
{
  std::cout<<"Photon: "
           <<"Energy="<<m_momentum.get_energy()<<" MeV, "
           <<"Px="<<m_momentum.get_px()<<" MeV/c, "
           <<"Py="<<m_momentum.get_py()<<" MeV/c, "
           <<"Pz="<<m_momentum.get_pz()<<" MeV/c, "
           <<"Rest mass="<<m_rest_mass<<" MeV/c^2, "
           <<"Charge="<<m_charge<<" e\n";
}
