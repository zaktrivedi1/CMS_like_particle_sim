// PHYS30762 Programming in C++
// Project - Particle Detector 24/04/2025
// Zak Trivedi 10841354
// Electron derived class implementation 

#include "electron.h"
#include <iostream>

// Parameterised constructor - automatically sets rest mass and charge
Electron::Electron(const Four_Momentum &momentum)
: Particle(momentum, 0.511, -1) 
{}

// Print function
void Electron::print_data() const
{
  std::cout<<"Electron: ";
  std::cout<<"Energy="<<m_momentum.get_energy()<<" MeV, ";
  std::cout<<"Px="<<m_momentum.get_px()<<" MeV/c, ";
  std::cout<<"Py="<<m_momentum.get_py()<<" MeV/c, ";
  std::cout<<"Pz="<<m_momentum.get_pz()<<" MeV/c, ";
  std::cout<<"Charge="<<m_charge<<" e, ";
  std::cout<<"Mass="<<m_rest_mass<<" MeV\n";
}