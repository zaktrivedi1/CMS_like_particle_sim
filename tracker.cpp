// PHYS30762 Programming in C++
// Project - Particle Detector 24/04/2025
// Zak Trivedi 10841354
// Implementation of member functions for tracker derived class

#include "tracker.h"
#include <iostream>
#include <random>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <stdexcept>

// Definition of the static detection count.
int Tracker::s_detection_count = 0;

// Parameterised constructor using setters for validation
Tracker::Tracker(const std::string &name, const std::string &material, int layers, double detection_efficiency, bool status)
: Sub_Detector(name, detection_efficiency, status)
{
  set_layers(layers);
  set_material(material);
}

// Setter for layers - throwsan error if layers aren't >= 1  
void Tracker::set_layers(int layers)
{
  if(layers >=1)
  {
    m_layers = layers;
  }
  else
  {
    throw std::invalid_argument("Tracker layers must be >= 1");
  }
}

// Setter for material
void Tracker::set_material(std::string material)
{
  m_material = material;
}

// Function to simulate particle detection
bool Tracker::detect_particle(const Particle &particle)
{
  // Must be turned on
  if(!m_status)
  {
    std::cout<<"Tracker '"<<m_name<<"' is OFF. Cannot detect particles."<<std::endl;
    return false;
  }

  // Only detects charged particles.
  if(particle.get_charge() == 0)
  {
    std::cout<<"No particle detected by tracker (particle is neutral)."<<std::endl;
    return false;
  }

  // Make input material case insensitive
  std::string lowercase_material = m_material;
  std::transform(lowercase_material.begin(), lowercase_material.end(), lowercase_material.begin(),
               [] (unsigned char c) {return std::tolower(c);});

  // Apply material-dependent efficiency modifier.
  double material_factor = 1.0;
  if(lowercase_material == "silicon")
  {
    material_factor = 1.0;
  }
  else
  {
    // Assume other materials are slightly less efficient
    material_factor = 0.8;
  }
  double effective_efficiency = m_detection_efficiency * material_factor;

  // Simulate detection inefficiency using a uniform distribution.
  static std::mt19937 random(std::random_device{}());
  std::uniform_real_distribution<double> uniform_distribution(0.0,1.0);
  if(uniform_distribution(random) > effective_efficiency)
  {
    std::cout<<"Particle missed by tracker due to detector inefficiency."<<std::endl;
    return false;
  }

  // Detected
  ++s_detection_count;
  std::cout<<"Particle detected by tracker!"<<std::endl;
  double true_energy = particle.get_momentum().get_energy();

  // Smear the energy assuming tracker resolution is 1/sqrt(layers)
  double resolution = 1.0 / std::sqrt(static_cast<double>(m_layers));
  std::normal_distribution<double> smear_distribution(true_energy, true_energy * resolution);
  double measured_energy = smear_distribution(random);
  if(measured_energy < 0.0)
  {
    measured_energy = 0.0;
  }

  // Print measured and true energies
  std::cout<<std::fixed<<std::setprecision(2)<<"  True Energy="<<true_energy
           <<" MeV, Measured Energy="<<measured_energy<<" MeV"<<std::endl;

  return true;
}

// Print function
void Tracker::print_info() const
{
  std::cout<<"Tracker: Name = "<<m_name<<", Material = "<<m_material<<", Layers = "<<m_layers<<", Efficiency = "
  <<m_detection_efficiency<<", Status = "<<(m_status ? "ON" : "OFF")<<"\n";
}

