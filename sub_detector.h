// PHYS30762 Programming in C++
// Project - Particle Detector 24/04/2025
// Zak Trivedi 10841354
// Sub detector abstract base class header

#ifndef SUB_DETECTOR_H
#define SUB_DETECTOR_H

#include <string>
#include <iostream>

// Forward declaration of particle class
class Particle;

class Sub_Detector
{
protected:
  bool m_status;         
  std::string m_name;    
  double m_detection_efficiency;

public:
  // Parameterized constructor.
  Sub_Detector(const std::string &name, double detection_efficiency=1.0, bool status = false);

  // Destructor
  virtual ~Sub_Detector() = default;

  // Functions to turn detector on and off.
  void turn_on() {m_status = true;}
  void turn_off() {m_status = false;}

  // Getters.
  bool get_status() const {return m_status;}
  std::string get_name() const {return m_name;}
  double get_detection_efficiency() const {return m_detection_efficiency;}

  // Setters
  void set_name(const std::string name) {m_name = name;}
  void set_detection_efficiency(double detection_efficiency);

  // Pure virtual print function
  virtual void print_info() const = 0;
  
  // Pure virtual detect function
  virtual bool detect_particle(const Particle &particle) = 0;
};

#endif 
