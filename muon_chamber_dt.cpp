// PHYS30762 Programming in C++
// Project - Particle Detector 24/04/2025
// Zak Trivedi 10841354
// Implementation of member functions for drift tube (DT) muon chamber derived class

#include "muon_chamber_dt.h"
#include "muon.h"
#include <random>
#include <cmath>
#include <iostream>
#include <iomanip>

// Definition of the static detection count.
int Muon_Chamber_DT::s_dt_detection_count=0;

// Parameterised constructor
Muon_Chamber_DT::Muon_Chamber_DT(const std::string &name, int component_count, double detection_efficiency,bool status)
  : Muon_Chamber(name, component_count, detection_efficiency, status)
{}

// Print function
void Muon_Chamber_DT::print_info() const
{
  std::cout<<"Muon Chamber DT: Name = "<<m_name
           <<", Component Count = "<<m_component_count
           <<", Efficiency = "<<m_detection_efficiency
           <<", Status = "<<(m_status ? "ON" : "OFF")<<"\n";
}

// Function to simulate particle detection
bool Muon_Chamber_DT::detect_particle(const Particle &particle)
{
  // Uses muon_chamber function to check for instant no detection
  if(!detect_common(particle))
  {
    return false;
  }

  // Detected
  ++s_dt_detection_count;
  std::cout<<"Muon detected by Muon Chamber DT!"<<std::endl;
  double true_energy = particle.get_momentum().get_energy();

  // Resolution of 1/sqrt(component count)
  double resolution = 1.0 / std::sqrt(static_cast<double>(m_component_count));

  // Simulates error from resolution
  static std::mt19937 random(std::random_device{}());
  std::normal_distribution<double> smear_distribution(true_energy, true_energy * resolution);
  double measured_energy = smear_distribution(random);
  if(measured_energy < 0.0)
  {
    measured_energy = 0.0;
  }

  // Prints true and measured energies
  std::cout<<std::fixed<<std::setprecision(2)<<"  True Energy="<<true_energy
           <<" MeV, Measured Energy="<<measured_energy<<" MeV"<<std::endl;

  return true;
}