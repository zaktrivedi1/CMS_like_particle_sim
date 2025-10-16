// PHYS30762 Programming in C++
// Project - Particle Detector 24/04/2025
// Zak Trivedi 10841354
// Class header for drift tube (DT) muon chamber derived class

#ifndef MUON_CHAMBER_DT_H
#define MUON_CHAMBER_DT_H

#include "muon_chamber.h"
#include <string>

class Muon_Chamber_DT : public Muon_Chamber
{
private:
  static int s_dt_detection_count;

public:
  // Prameterised constructor
  Muon_Chamber_DT(const std::string &name, int component_count, double detection_efficiency = 1.0,bool status = false);

  // Destructor
  ~Muon_Chamber_DT() = default;

  // Overriding print function
  void print_info() const override;

  // Function to simulate particle detection 
  bool detect_particle(const Particle & particle) override;

  // Getter for detection count
  static int get_dt_count(){return s_dt_detection_count;}
};

#endif 
