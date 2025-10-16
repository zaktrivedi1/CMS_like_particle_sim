// PHYS30762 Programming in C++
// Project - Particle Detector 24/04/2025
// Zak Trivedi 10841354
// Implementation of member functions for generic detector class

#include "generic_detector.h"
#include <iostream>
#include <algorithm>

// Setter for name - defaults to "Generic Detector" if none set
void Generic_Detector::set_detector_name(const std::string &name)
{
  if(name.empty())
  {
    m_detector_name = "Generic Detector";
  }
  else
  {
    m_detector_name = name;
  }
}

// Parameterised constructor using setter
Generic_Detector::Generic_Detector(const std::string &name)
{
  set_detector_name(name);
}

// Function to add sub detector
void Generic_Detector::add_sub_detector(std::unique_ptr<Sub_Detector> sub_detector)
{
  if(sub_detector)
  {
    m_sub_detectors.push_back(std::move(sub_detector));
  }
}

// Print entire detector configuration
void Generic_Detector::print_configuration() const
{
  std::cout<<"Detector Name="<<m_detector_name<<"\n";
  std::cout<<"Sub-detector configuration:\n";

  // Iterates through sub-detector print functions
  for(const auto &sub_detector : m_sub_detectors)
  {
    sub_detector->print_info();
  }
}

// Find a sub-detector by its name.
Sub_Detector *Generic_Detector::find_sub_detector(const std::string &name) const
{
  auto it = std::find_if(m_sub_detectors.begin(), m_sub_detectors.end(),
    [&name](const std::unique_ptr<Sub_Detector> &ptr)
    {
      return ptr->get_name() == name;
    }
  );

  return (it != m_sub_detectors.end()) ? it->get() : nullptr;
}

// Remove a sub-detector by its name.
bool Generic_Detector::remove_sub_detector(const std::string &name)
{
  // Find the sub-detector with matching name using a lambda function.
  auto it = std::find_if(
    m_sub_detectors.begin(), m_sub_detectors.end(),
    [&name](const std::unique_ptr<Sub_Detector> &ptr)
    {
      return ptr->get_name() == name; // Compare each sub-detector's name
    }
  );

  // Detector was not found in the list, cannot remove
  if(it == m_sub_detectors.end())
  {
    return false;
  }
  
  // Erase the sub-detector from the vector, automatically freeing memory due to unique_ptr.
  m_sub_detectors.erase(it);
  return true;
}