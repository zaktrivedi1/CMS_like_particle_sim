// PHYS30762 Programming in C++
// Project - Particle Detector 24/04/2025
// Zak Trivedi 10841354
// Main program to simulate particle detections through a CMS-like detector. Constructs a CMS-like detector, 
// adds sub-detectors, modifies it, creates sample particles and passes them through each sub-detector to test detection 
// functionality. Factors like detection efficiency, resolution and sampling fraction are used to make the 
// detectors more realistic. Particle type is inferred due to what it has been detected by and compared to 
// its actual type to see if detector inefficiencies caused an inaccurate inferred type. Also calculates 
// missing transverse energy for neutrinos

#include "four_momentum.h"
#include "particle.h"
#include "electron.h"
#include "muon.h"
#include "photon.h"
#include "neutrino.h"
#include "hadron.h"

#include "sub_detector.h"
#include "tracker.h"
#include "calorimeter.h"
#include "ecal.h"
#include "hcal.h"
#include "muon_chamber_dt.h"
#include "muon_chamber_csc.h"
#include "generic_detector.h"

#include <memory>
#include <vector>
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

// Helper function to infer particle type from detectors its has been detected by
static std::string infer_particle(bool tracker_detection, bool ecal_detection, bool hcal_detection, bool dt_detection, bool csc_detection)
{
  // Grouping DT and CSC muon chamber detections
  bool muon_chamber_detection = dt_detection || csc_detection;

  // Photon: only ECAL 
  if(!tracker_detection && ecal_detection && !hcal_detection && !muon_chamber_detection)
  {
    return "Photon";
  }

  // Electron: tracker + ECAL
  if(tracker_detection && ecal_detection && !hcal_detection && !muon_chamber_detection)
  {
    return "Electron";
  }

  // Muon: tracker + any muon chamber
  if(tracker_detection && !ecal_detection && !hcal_detection && muon_chamber_detection)
  {
    return "Muon";
  }

  // Hadron: tracker + HCAL (could also go into HCAL without tracker, but here it requires tracker)
  if(tracker_detection && !ecal_detection && hcal_detection && !muon_chamber_detection)
  {
    return "Hadron";
  }

  // Neutrino: no detections
  if(!tracker_detection && !ecal_detection && !hcal_detection && !muon_chamber_detection)
  {
    return "Neutrino";
  }

  // Fallback
  return "Unknown";
}

// Function to return the actual particle type as a string.
static std::string get_actual_type(const Particle &p)
{
  if(dynamic_cast<const Electron*>(&p)!=nullptr)
  {
    return "Electron";
  }
  else if(dynamic_cast<const Photon*>(&p)!=nullptr)
  {
    return "Photon";
  }
  else if(dynamic_cast<const Muon*>(&p)!=nullptr)
  {
    return "Muon";
  }
  else if(dynamic_cast<const Hadron*>(&p)!=nullptr)
  {
    return "Hadron";
  }
  else if(dynamic_cast<const Neutrino*>(&p)!=nullptr)
  {
    return "Neutrino";
  }
  return "Unknown";
}

int main()
{
  std::cout<<"==== STARTING SIMULATION ===="<<std::endl;

  // Construct detector
  Generic_Detector cms("Simple-CMS");

  // Add sub-detectors
  cms.add_sub_detector(std::make_unique<Tracker>("Tracker","Silicon",5,0.95,true));
  cms.add_sub_detector(std::make_unique<ECAL>("ECAL","Lead Tungstate",7500,0.4,0.90,true));
  cms.add_sub_detector(std::make_unique<HCAL>("HCAL","Steel Scintillator",40000,0.10,0.85,true));
  cms.add_sub_detector(std::make_unique<Muon_Chamber_DT>("DT Chambers",250,0.9,true));
  cms.add_sub_detector(std::make_unique<Muon_Chamber_CSC>("CSC Chambers",540,0.85,true));
  cms.add_sub_detector(std::make_unique<HCAL>("HCAL extra","Steel scintillator",3000,0.15,0.85,true));
  cms.add_sub_detector(std::make_unique<Muon_Chamber_CSC>("CSC Chambers extra",1040,0.9,true));

  // Print configuration
  cms.print_configuration();

  // Modifies detector configuration to demostrate functionality
  std::cout<<"\n=== Modifying detector configuration ===\n";

  // Finds the extra HCAL and turn it off 
  if(auto *hcal = dynamic_cast<Sub_Detector*>(cms.find_sub_detector("HCAL extra")))
  {
    hcal->turn_off();
    std::cout<<"A HCAL has been turned OFF.\n";
  }

  // Removes the extra CSC muon chamber entirely
  if(cms.remove_sub_detector("CSC Chambers extra"))
  {
    std::cout<<"A CSC Chamber removed from detector.\n";
  }
  else
  {
    std::cout<<"Failed to remove CSC Chambers (not found).\n";
  }

  // Print updated configuration
  std::cout<<"\n=== Updated Configuration ===\n";
  cms.print_configuration();

  // Create sample particles
  std::vector<std::unique_ptr<Particle>> particles;
  particles.emplace_back(std::make_unique<Electron>(Four_Momentum(50.0, 10.0, 15.0, 5.0)));
  particles.emplace_back(std::make_unique<Photon>(Four_Momentum(60.0, -10.0, 5.0, 2.0)));
  particles.emplace_back(std::make_unique<Muon>(Four_Momentum(80.0, 0.0, -20.0, 1.0)));
  particles.emplace_back(std::make_unique<Hadron>(Four_Momentum(100.0, 5.0, 0.0, -3.0),"proton", 938, 1.0));
  particles.emplace_back(std::make_unique<Neutrino>(Four_Momentum(30.0, -5.0, 0.0, -4.0),"muon"));

  // Running sums of detected transverse momentum
  double sum_px_detected = 0.0;
  double sum_py_detected = 0.0;

  // Loop over particles and test each sub-detector
  for(const auto &p : particles)
  {
    std::cout<<"\n--- New Particle ---"<<std::endl;
    p->print_data();

    bool hit_tracker = false;
    bool hit_ecal = false;
    bool hit_hcal = false;
    bool hit_muon_chamber_dt   = false;
    bool hit_muon_chamber_csc  = false;

    if(auto *tracker = cms.find_sub_detector("Tracker"))
    {
      hit_tracker = tracker->detect_particle(*p);
    }
    if(auto *ecal = cms.find_sub_detector("ECAL"))
    {
      hit_ecal = ecal->detect_particle(*p);
    }
    if(auto *hcal = cms.find_sub_detector("HCAL"))
    {
      hit_hcal = hcal->detect_particle(*p);
    }
    if(auto *muon_chamber_dt = cms.find_sub_detector("DT Chambers"))
    {
      hit_muon_chamber_dt = muon_chamber_dt->detect_particle(*p);
    }
    if(auto *muon_chamber_csc = cms.find_sub_detector("CSC Chambers"))
    {
      hit_muon_chamber_csc = muon_chamber_csc->detect_particle(*p);
    }

    // Infers particle type from what it'been detected by
    std::string inferred = infer_particle(hit_tracker, hit_ecal, hit_hcal, hit_muon_chamber_dt, hit_muon_chamber_csc);
    std::cout<<"Inferred particle type: "<<inferred<<std::endl;

    // If any detector saw it, accumulate its px and py
    if(hit_tracker || hit_ecal || hit_hcal || hit_muon_chamber_dt || hit_muon_chamber_csc)
    {
      sum_px_detected += p->get_momentum().get_px();
      sum_py_detected += p->get_momentum().get_py();
    }

    // Compares inferred type to actual type to check if detector inefficiencies led to an inaccurate result
    std::string actual = get_actual_type(*p);
    if(actual == inferred)
    {
      std::cout<<"Correctly detected "<<actual<<"."<<std::endl;
    }
    else
    {
      std::cout<<"ERROR: actual particle was "<<actual
               <<" but inferred as "<<inferred<<"."<<std::endl;
      std::cout<<"Likely cause: detector inefficiency (missing hits in required sub-detectors)."<<std::endl;
    }
  }

  // Finds the difference between the sum of the transverse momentum and 0 to find the missing transverse 
  // energy that corresponds to the neutrino energy
  std::cout<<"\n=== Missing Transverse Energy (Neutrinos) ==="<<std::endl;
  double missing_transverse_energy = std::sqrt(sum_px_detected * sum_px_detected + sum_py_detected * sum_py_detected);
  if(missing_transverse_energy!=0)
  {
    std::cout<<"Neutrino presence implied by a non-zero missing transverse energy (MTE) = "
              <<missing_transverse_energy<<" MeV"<<std::endl;
  }
  else
  {
    std::cout<<"Missing transverse energy (MTE) = 0 MeV, implying that no neutrinos are present."<<std::endl;
  }

  std::cout<<"\n==== END OF SIMULATION ===="<<std::endl;
  return 0;
}
