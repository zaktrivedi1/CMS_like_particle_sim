// PHYS30762 Programming in C++
// Project - Particle Detector 24/04/2025
// Zak Trivedi 10841354
// Implementation of member functions for HCAL derived class

#include "hcal.h"
#include "hadron.h"
#include <random>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <stdexcept>

// Definition of the static detection count.
int HCAL::s_detection_count = 0;

// Parameterised constructor using a setter for input validation
HCAL::HCAL(const std::string &name, const std::string &material, int number_of_cells, double sampling_fraction, double detection_efficiency, bool status)
  : Calorimeter(name, material, number_of_cells, detection_efficiency, status)
{
  set_sampling_fraction(sampling_fraction);
}

// Print function
void HCAL::print_info() const
{
  std::cout<<"HCAL: Name = "<<m_name
           <<", Material = "<<m_material
           <<", Number of Cells = "<<m_number_of_cells
           <<", Sampling Fraction = "<<m_sampling_fraction
           <<", Efficiency = "<<m_detection_efficiency
           <<", Status = "<<(m_status ? "ON" : "OFF")<<"\n";
}

// Setter for sampling fraction - throws an error if not between 0 and 1
void HCAL::set_sampling_fraction(double fraction) 
{
  if(m_sampling_fraction < 0.0 || m_sampling_fraction > 1.0)
  {
    throw std::invalid_argument("Sampling fraction must be between 0 and 1");
  }
  else 
  {
    m_sampling_fraction = fraction;
  }
}

// Function to detect particle
bool HCAL::detect_particle(const Particle &particle)
{
  // Must be turned on
  if(!m_status)
  {
    std::cout<<"HCAL '"<<m_name<<"' is OFF. Cannot detect particles."<<std::endl;
    return false;
  }

  // Only detects hadrons
  if(dynamic_cast<const Hadron*>(&particle)==nullptr)
  {
    std::cout<<"No hadron detected by HCAL."<<std::endl;
    return false;
  }

  // Makes material input case insensitive 
  std::string lowercase_material = m_material;
  std::transform(lowercase_material.begin(), lowercase_material.end(), lowercase_material.begin(),
               [] (unsigned char c) {return std::tolower(c);});

  // Material‑dependent efficiency modifier
  double material_factor = (lowercase_material=="steel scintillator"?0.9:0.8);
  double effective_efficiency = m_detection_efficiency*material_factor;

  // Simulate inefficiency
  static std::mt19937 random(std::random_device{}());
  std::uniform_real_distribution<double> uniform_distribution(0.0,1.0);
  if(uniform_distribution(random) > effective_efficiency)
  {
    std::cout<<"Hadron missed due to HCAL inefficiency."<<std::endl;
    return false;
  }

  // Detected
  ++s_detection_count;
  std::cout<<"Hadron detected by HCAL!"<<std::endl;
  double true_energy = particle.get_momentum().get_energy();

  // Calculates visible energy based on sampling fraction
  double visible_energy = true_energy*m_sampling_fraction;

  // Resolution of 1/sqrt(Ncells)
  double effective_resolution = 1.0/std::sqrt(static_cast<double>(m_number_of_cells));
  std::normal_distribution<double> smear_distribution(visible_energy, visible_energy*effective_resolution);
  double measured_energy = smear_distribution(random);
  if(measured_energy<0.0)
  {
    measured_energy = 0.0;
  }

  // Prints true and measured energies
  std::cout<<std::fixed<<std::setprecision(2)<<"  True Energy="<<true_energy
           <<" MeV, Measured Energy="<<measured_energy<<" MeV"<<std::endl;

  return true;
}