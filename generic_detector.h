// PHYS30762 Programming in C++
// Project - Particle Detector 24/04/2025
// Zak Trivedi 10841354
// Class header for generic detector function

#ifndef GENERIC_DETECTOR_H
#define GENERIC_DETECTOR_H

#include <vector>
#include <memory>
#include <string>
#include "sub_detector.h"

class Generic_Detector
{
private:
  std::vector<std::unique_ptr<Sub_Detector>> m_sub_detectors;
  std::string m_detector_name;

protected:
  // Protected setter for the detector name
  void set_detector_name(const std::string &name);

public:
  // Parameterized constructor.
  Generic_Detector(const std::string &name = "Generic Detector");

  // Rule of 3 (copy constuctor and copy assignment deleted as you can't copy unique pointers)
  Generic_Detector(const Generic_Detector&) = delete;
  Generic_Detector& operator=(const Generic_Detector&) = delete;
  Generic_Detector(Generic_Detector&&) noexcept = default;
  Generic_Detector& operator=(Generic_Detector&&) noexcept = default;

  // Destructor
  ~Generic_Detector() = default;

  // Function to add a sub-detector 
  void add_sub_detector(std::unique_ptr<Sub_Detector> sub_detector);

  // Function to print the entire configuration of the detector.
  void print_configuration() const;

  // Function to find a sub-detector by name.
  Sub_Detector *find_sub_detector(const std::string &name) const;

  // Function to remove a sub-detector by name.
  bool remove_sub_detector(const std::string &name);

  // Getter for the detector name.
  std::string get_detector_name() const {return m_detector_name;}
};

#endif 
