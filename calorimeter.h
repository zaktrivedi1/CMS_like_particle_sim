// PHYS30762 Programming in C++
// Project - Particle Detector 24/04/2025
// Zak Trivedi 10841354
// Class header for calorimeter derived abstract base class

#ifndef CALORIMETER_H
#define CALORIMETER_H

#include "sub_detector.h"
#include <string>

class Calorimeter : public Sub_Detector
{
protected:
  std::string m_material;
  int m_number_of_cells;

  // Setter for material with basic validation.
  void set_material(const std::string &material);
  
  // Setter for number of cells with validation.
  void set_number_of_cells(int number_of_cells);

public:
  // Parameterized constructor
  Calorimeter(const std::string &name, const std::string &material, int number_of_cells, double detection_efficiency = 1.0, bool status = false);
  virtual ~Calorimeter() = default;

  // Pure virtual function for printing calorimeter information
  virtual void print_info() const = 0;

  // Pure virtual function to simulate particle detection
  virtual bool detect_particle(const Particle &particle) = 0;

  // Getters.
  std::string get_material() const {return m_material;}
  int get_number_of_cells() const {return m_number_of_cells;}
};

#endif 
