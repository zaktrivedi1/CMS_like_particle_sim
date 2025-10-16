// PHYS30762 Programming in C++
// Project - Particle Detector 24/04/2025
// Zak Trivedi 10841354
// Implementation of member functions for ECAL derived class

#include "ecal.h"
#include "electron.h"
#include "photon.h"
#include <random>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>

// Definition of the static detection count.
int ECAL::s_detection_count = 0;

// Parameterised constructor - using setter for input validation
ECAL::ECAL(const std::string &name, const std::string &material, int number_of_cells, double resolution, double detection_efficiency, bool status)
  : Calorimeter(name, material, number_of_cells, detection_efficiency, status)
{
  set_resolution(resolution);
}

// Print function
void ECAL::print_info() const
{
  std::cout<<"ECAL: Name = "<<m_name
           <<", Material = "<<m_material
           <<", Number of Cells = "<<m_number_of_cells
           <<", Resolution = "<<m_resolution
           <<", Efficiency = "<<m_detection_efficiency
           <<", Status = "<<(m_status ? "ON" : "OFF")<<"\n";
}

// Setter for resolution - throws an error if not positive
void ECAL::set_resolution(double resolution)
{
  if(resolution>0.0)
  {
    m_resolution = resolution;
  }
  else
  {
    throw std::invalid_argument("ECAL resolution must be positive");
  }
}

// Detection function for particles
bool ECAL::detect_particle(const Particle &particle)
{
  // Checks ON/OFF status
  if(!m_status)
  {
    std::cout<<"ECAL '"<<m_name<<"' is OFF. Cannot detect particles."<<std::endl;
    return false;
  }

  // Only detects electrons and photons
  if(dynamic_cast<const Electron*>(&particle)==nullptr &&
     dynamic_cast<const Photon*>(&particle)==nullptr)
  {
    std::cout<<"No EM particle detected by ECAL."<<std::endl;
    return false;
  }

  // Makes material input case insensitive
  std::string lowercase_material = m_material;
  std::transform(lowercase_material.begin(), lowercase_material.end(), lowercase_material.begin(),
               [] (unsigned char c) {return std::tolower(c);});

  // Material‑dependent efficiency modifier
  double material_factor = (lowercase_material == "lead tungstate"?1.0:0.9);
  double effective_efficiency = m_detection_efficiency*material_factor;

  // Simulates inefficiency and probability of missing particle
  static std::mt19937 random(std::random_device{}());
  std::uniform_real_distribution<double> uniform_distribution(0.0,1.0);
  if(uniform_distribution(random) > effective_efficiency)
  {
    std::cout<<"Particle missed by ECAL inefficiency."<<std::endl;
    return false;
  }

  // Detected
  ++s_detection_count;
  std::cout<<"Particle detected by ECAL!"<<std::endl;
  double true_energy = particle.get_momentum().get_energy();

  // Effective resolution scales with 1/sqrt(Ncells)
  double effective_resolution = m_resolution/std::sqrt(static_cast<double>(m_number_of_cells));
  std::normal_distribution<double> smear_distribution(true_energy,true_energy*effective_resolution);
  double measured_energy = smear_distribution(random);
  if(measured_energy<0.0)
  {
    measured_energy = 0.0;
  }
  
  // Prints true and measured energy

  std::cout<<std::fixed<<std::setprecision(2)<<"  True Energy="<<true_energy
           <<" MeV, Measured Energy="<<measured_energy<<" MeV"<<std::endl;

  return true;
}