## About

This project was developed as part of my C++ final project, which I completed during third year of my BSc(Hons) Physics Degree. 

## Features

- Constructs a CMS-like detector, adds sub-detectors, modifies it, creates sample particles and passes them through each sub-detector to test detection functionality.
- Sub-detectors include trackers, calorimeters (2 types) and muon chambers (2 types).
- Particles include neutrinos, photons, hadrons and electrons.
- Factors like detection efficiency, resolution and sampling fraction are used to make the detectors more realistic.
- Particle type is inferred due to what it has been detected by and compared to its actual type to see if detector inefficiencies caused an inaccurate inferred type.
- Also calculates missing transverse energy for neutrinos
- Written in modern C++17

## Report
A detailed write-up of the simulation methodology, detector modelling and analysis results:  
[Read the full technical report (PDF)](finished_zak_trivedi_code_report.pdf)


## Building

From the project root, run (left in one line for copy and paste friendliness):

```bash
g++ -std=c++17 -Wall -Wextra four_momentum.cpp particle.cpp electron.cpp muon.cpp photon.cpp neutrino.cpp hadron.cpp sub_detector.cpp tracker.cpp calorimeter.cpp ecal.cpp hcal.cpp muon_chamber.cpp muon_chamber_dt.cpp muon_chamber_csc.cpp generic_detector.cpp project.cpp -o detector_sim


Once built simply execute: ./detector_sim

