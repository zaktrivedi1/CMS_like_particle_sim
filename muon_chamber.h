// PHYS30762 Programming in C++
// Project - Particle Detector 24/04/2025
// Zak Trivedi 10841354
// Class header for muon chamber derived abstract base class

#ifndef MUON_CHAMBER_H
#define MUON_CHAMBER_H

#include "sub_detector.h"
#include <string>
#include "particle.h"

class Muon_Chamber : public Sub_Detector
{
protected:
  int m_component_count;
  
  // Function for detection simulation logic common to DT and CSC detectors
  bool detect_common(const Particle &particle) const;

  // Parameterised constructor
  Muon_Chamber(const std::string &name, int component_count, double detection_efficiency = 1.0, bool status = false);
public:
  // Virtual destructor
  virtual ~Muon_Chamber() = default;
  
  // Pure virtual print function
  virtual void print_info() const = 0;

  // Pure virtual function to simulate particle detection
  virtual bool detect_particle(const Particle &particle) = 0;

  // Getter for the number of components.
  int get_component_count() const {return m_component_count;}

  // Setter for component count
  void set_component_count(int component_count);
};

#endif 
