// PHYS30762 Programming in C++
// Project - Particle Detector 24/04/2025
// Zak Trivedi 10841354
// Class header for derived tracker class

#ifndef TRACKER_H
#define TRACKER_H

#include "sub_detector.h"
#include <string>
#include <memory>
#include "particle.h"

class Tracker : public Sub_Detector
{
private:
  static int s_detection_count;

  std::string m_material;
  int m_layers;

public:
  // Parameterised constructor
  Tracker(const std::string &name, const std::string &material, int layers, double detection_efficiency = 1.0, bool status = false);

  // Destructor
  ~Tracker() = default;

  // Overriding print function
  void print_info() const override;

  // Getters
  std::string get_material() const {return m_material;}
  int get_layers() const {return m_layers;}

  // Setters
  void set_material(std::string material);
  void set_layers(int layers);

  // Function to simulate a detection event.
  bool detect_particle(const Particle &particle) override;

  // Static getter for detection count.
  static int get_detection_count() {return s_detection_count;}
};

#endif 
