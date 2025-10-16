[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/jNsaiKCH)

## Building

From the project root, run (left in one line for copy and paste friendliness):

```bash
g++ -std=c++17 -Wall -Wextra four_momentum.cpp particle.cpp electron.cpp muon.cpp photon.cpp neutrino.cpp hadron.cpp sub_detector.cpp tracker.cpp calorimeter.cpp ecal.cpp hcal.cpp muon_chamber.cpp muon_chamber_dt.cpp muon_chamber_csc.cpp generic_detector.cpp project.cpp -o detector_sim


Once built simply execute: ./detector_sim
