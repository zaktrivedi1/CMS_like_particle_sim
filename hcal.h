// PHYS30762 Programming in C++
// Project - Particle Detector 24/04/2025
// Zak Trivedi 10841354
// Class header for derived HCAL class

#ifndef HCAL_H
#define HCAL_H

#include "calorimeter.h"
#include "particle.h"

class HCAL : public Calorimeter
{
protected:
  static int s_detection_count;
  double m_sampling_fraction; 

  // Setter for sampling fraction 
  void set_sampling_fraction(double fraction);

public:
  // Parameterized constructor
  HCAL(const std::string &name, const std::string &material, int number_of_cells, 
    double sampling_fraction, double detection_efficiency = 1.0, bool status = false);

  // Destructor
  ~HCAL() = default;

  // Overriding print function
  void print_info() const override;

  // Getter for sampling fraction.
  double get_sampling_fraction() const {return m_sampling_fraction;}

  // Function to simulate a detection event.
  bool detect_particle(const Particle &particle) override;

  // Static getter for detection count.
  static int get_detection_count() {return s_detection_count;}
};

#endif 
