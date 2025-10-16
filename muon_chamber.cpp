// PHYS30762 Programming in C++
// Project - Particle Detector 24/04/2025
// Zak Trivedi 10841354
// Implementation of member functions for calorimeter derived abstract class

#include "muon_chamber.h"
#include "muon.h"
#include <random>
#include <iostream>
#include <stdexcept>

// Parameterised constructor using setter for input validation
Muon_Chamber::Muon_Chamber(const std::string &name, int component_count, double detection_efficiency, bool status)
  : Sub_Detector(name, detection_efficiency, status)
{
  set_component_count(component_count);
}

// Setter for component count - throws an error if count is not > 0
void Muon_Chamber::set_component_count(int component_count)
{
  if(component_count>0)
  {
    m_component_count = component_count;
  }
  else
  {
    throw std::invalid_argument("Component count must be a an integer > 0.");
  }
}

// Helper detection function with logic common to both DT and CSC detection functions
bool Muon_Chamber::detect_common(const Particle &particle) const
{
  // Only detects if detector is ON
  if(!m_status)
  {
    std::cout<<m_name<<" is OFF. Cannot detect particles."<<std::endl;
    return false;
  }

  // Only detects muons
  if(dynamic_cast<const Muon*>(&particle)==nullptr)
  {
    std::cout<<"No muon detected by "<<m_name<<"."<<std::endl;
    return false;
  }

  // Simulates probability of particles being missed due to detector inefficiency
  static std::mt19937 random(std::random_device{}());
  std::uniform_real_distribution<double> uniform_distribution(0.0,1.0);
  if(uniform_distribution(random) > m_detection_efficiency)
  {
    std::cout<<"Muon missed by "<<m_name<<" inefficiency."<<std::endl;
    return false;
  }

  return true;
}