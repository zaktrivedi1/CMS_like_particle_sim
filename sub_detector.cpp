// PHYS30762 Programming in C++
// Project - Particle Detector 24/04/2025
// Zak Trivedi 10841354
// Implementation of member functions for sub detector abstract base class

#include "sub_detector.h"
#include <stdexcept>

// Parameterized constructor using setters for input validation
Sub_Detector::Sub_Detector(const std::string &name, double detection_efficiency, bool status)
  : m_status(status)
{
  set_name(name);
  set_detection_efficiency(detection_efficiency); 
}

// Setter for detection efficiency - throws an error if not within 0 - 1
void Sub_Detector::set_detection_efficiency(double detection_efficiency)
{
  if(detection_efficiency < 0.0 || detection_efficiency > 1.0)
  {
    throw std::invalid_argument("Detection efficiency out of range (must be 0.0 - 1.0)");
  }
  m_detection_efficiency = detection_efficiency;
}