// PHYS30762 Programming in C++
// Project - Particle Detector 24/04/2025
// Zak Trivedi 10841354
// Class header for ECAL derived class

#ifndef ECAL_H
#define ECAL_H

#include "calorimeter.h"
#include "particle.h"
#include <stdexcept>

class ECAL : public Calorimeter
{
protected:
  static int s_detection_count;
  double m_resolution; 

  // Setter for resolution 
  void set_resolution(double resolution); 

public:
  // Parameterized constructor
  ECAL(const std::string &name, const std::string &material, int number_of_cells, double resolution, 
        double detection_efficiency = 1.0, bool status = false);

  // Destructor
  ~ECAL() = default;

  // Overriding print function
  void print_info() const override;

  // Getter for resolution
  double get_resolution() const {return m_resolution;}

  // Function to simulate a detection event.
  bool detect_particle(const Particle &particle) override;

  // Static getter for detection count.
  static int get_detection_count() {return s_detection_count;}
};

#endif 
