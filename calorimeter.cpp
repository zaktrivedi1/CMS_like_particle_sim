// PHYS30762 Programming in C++
// Project - Particle Detector 24/04/2025
// Zak Trivedi 10841354
// Implementation of member functions for calorimeter derived abstract class

#include "calorimeter.h"
#include <stdexcept>

// Paramaterised constructor using setters for input validation
Calorimeter::Calorimeter(const std::string &name, const std::string &material, int number_of_cells, double detection_efficiency, bool status)
  : Sub_Detector(name, detection_efficiency ,status)
{
  set_material(material);
  set_number_of_cells(number_of_cells);
}

// Setter for material - defaults to "unknown" if empty
void Calorimeter::set_material(const std::string &material) 
{
    if(material.empty()) 
    {
      m_material = "Unknown";
    }
    else 
    {
      m_material = material;
    }
}

// Setter for number of cells - throws an error if not >= 1
void Calorimeter::set_number_of_cells(int number_of_cells) 
{
    if(number_of_cells < 1) 
    {
      throw std::invalid_argument("Number of calorimeter cells must be >= 1");;
    }
    else 
    {
      m_number_of_cells = number_of_cells;
    }
  }