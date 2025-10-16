// PHYS30762 Programming in C++
// Project - Particle Detector 24/04/2025
// Zak Trivedi 10841354
// Class header for 4 momentum class

#ifndef FOUR_MOMENTUM_H
#define FOUR_MOMENTUM_H

#include <iostream>

class Four_Momentum
{
private:
  double m_energy;
  double m_px;
  double m_py;
  double m_pz;

public:

  // Parameterised Constructor 
  Four_Momentum(double energy=0.0,double px=0.0,double py=0.0,double pz=0.0);

  // Destructor
  ~Four_Momentum() = default;

  // Getters.
  double get_energy() const {return m_energy;}
  double get_px() const {return m_px;}
  double get_py() const {return m_py;}
  double get_pz() const {return m_pz;}

  // Setters.
  void set_energy(double energy);
  void set_px(double px) {m_px=px;}
  void set_py(double py) {m_py=py;}
  void set_pz(double pz) {m_pz=pz;}
};

#endif 
