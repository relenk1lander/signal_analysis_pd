Signal analysis for strip detectors

Overview

This script, DATA_CALIBRATION.C, processes ADC (Analog-to-Digital Converter) values from a ROOT file containing particle detector data. It performs pedestal subtraction, common noise subtraction, and identifies valid signal clusters to analyze event data.

Requirements

ROOT framework installed (https://root.cern/)

A valid ROOT file containing event data

Basic knowledge of C++ and ROOT libraries

Input Files

cleaned_data.root: The ROOT file containing the event tree.

Tree name: cleanedEventTRB

Pre-processing Steps

Pedestal Subtraction: The pedestal value of each channel is determined and subtracted from the ADC values.

Common Noise Subtraction: The common mode noise (CN) is calculated and removed from each event.

Bad Channel Removal: Channels identified as bad are set to zero to exclude them from clustering.

Processing Steps

The script loads the ROOT file and accesses the cleanedEventTRB tree.

It iterates over the ADC values for multiple events, computing the pedestal and common noise.

It applies signal thresholding (e.g., values above 18 are considered significant).

It finds the maximum ADC values per event and sums the adjacent channels.

It creates a histogram of valid signal sums.

How to Run the Script

Open a terminal and launch ROOT:

root -l

Load and execute the script:

.x DATA_CALIBRATION.C

Enter the event number when prompted.

The script will output key statistics and generate a histogram visualization.

Output

A histogram displaying valid signal sums.

Statistics including the percentage of events containing valid signals and the number of distinct valid sums.

Notes

Ensure that the ROOT file is in the same directory as the script.

The number of channels is set to 383.

The script assumes a structured naming convention for tree branches (e.g., t_Ch0, t_Ch1, ...).

Future Improvements

Dynamic determination of the number of channels.

More robust handling of bad channels.

Adjustable thresholds for signal detection.

Additional visualization enhancements.

